#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;
//float const island[] = { 50, 50, 54, 54, 55, 55, 59, 59, 56, 56, 52, 50 }; //pyramid!
float const island[] = { 54, 50, 54, 54, 52, 55, 51, 59, 50, 56, 52, 50 };
///////////////     Pos # 0   1   2   3   4   5   6   7   8   9  10  11
int const size = sizeof(island) / sizeof(int);
float accu = 0;
//adapted from STL, only needed in the twoPassAlgo
template<class ForwardIterator>
ForwardIterator max_element_last(ForwardIterator scanner, ForwardIterator const end) {
	ForwardIterator ret = scanner;
	if (scanner == end)
		return ret;//empty range, with zero element!
	while (++scanner != end)
		if (*ret <= *scanner) //"=" means find LAST
			ret = scanner;
	return ret;
}
//print height and address of a column
void print1(float const* const pos, char const * const label) {
	//int const height = *pos;
	printf("%s=%.0f/%d ", label, *pos, pos - island);
}
//print the current 2 walls and 2 moving pointers. All 4 "markers" keep moving inward
void printAll(float const* const L, float const* const loPtr, float const* const hiPtr,
		float const* const H) {
	static bool is1stCall = true;
	if (is1stCall){
		is1stCall = false;
		printf("wH means high Wall; m means moving marker inside this wall\n......\n");
	}
	if (loPtr < hiPtr) { // loPtr is on the left side
		print1(L, "wL"); // pointer to lower wall
		print1(loPtr, "m"); // the moving marker on the side of the lower wall
		printf("  ");
		print1(hiPtr, "m");
		print1(H, "wH");
	} else { // hiPtr is on the left side, so we print high side first
		print1(H, "wH");
		print1(hiPtr, "m");
		printf("  ");
		print1(loPtr, "m");
		print1(L, "wL");
	}
	printf("%.0f=Accu\n", accu);
}
//Rule: move the lo-side pointer only
void onePassAlgo(){
	float*wallLo, *wallHi; //moving walls
	float*loPtr, *hiPtr; //moving pointer, moving-inward.
	// loPtr is the moving pointer on the side of the lower wall

	//1st we ASSUME the first left side wall will be lower than the first right side wall
	wallLo = loPtr = const_cast<float*> (island);
	wallHi = hiPtr = const_cast<float*> (island) + size - 1;
	//2nd, we validate that assumption
	if (*wallLo > *wallHi) {
		std::swap(wallLo, wallHi);
		std::swap(loPtr, hiPtr);
	}
	// now wallLo is confirmed lower than the wallHi
	printAll(wallLo,loPtr,hiPtr,wallHi);
	printf("All pointers initialized (incl. 2 walls\n");
	while (loPtr != hiPtr) {
		if (*loPtr > *wallHi) {
			wallLo = wallHi;
			wallHi = loPtr;
			std::swap(loPtr, hiPtr);
			//printf("new wallHi:");
		} else if (*loPtr >= *wallLo) {//see the >=
			wallLo = loPtr;
			//printf("wallLo updated:");
		} else {
			assert (*loPtr < *wallLo);
			accu += (*wallLo - *loPtr);
			printf("adding %.0f liter of water at Pos_%d (%.0f=A\n", *wallLo - *loPtr,
					loPtr - island, accu);
		}
		printAll(wallLo,loPtr,hiPtr,wallHi);
		// only by moving the loptr (not h) can we confidently accumulate water
		if (loPtr < hiPtr)
			++loPtr; //lo side is on the left, move loptr right
		else
			--loPtr; //lo side is on the right, move loptr left
	}
}
void twoPassAlgo() {//less convoluted
	float const* const peak = max_element_last(island, island + size);
	printf("highest peak (last if multiple) is %.0f, at Pos %d\n", *peak, peak
			- island);

	//forward scan towards peak
	float* pos = const_cast<float*> (island); //left edge of island
	float* wall = pos;
	for (++pos; pos < peak; ++pos) {
		if (*wall > *pos) {
			accu += *wall - *pos; // accumulate water
			printf("adding %.0f liter of water at Pos#%d (T=%.0f)\n", *wall - *pos,
					pos - island, accu);
			continue;
		}
		//ALL new walls must match or exceed previous wall.
		printf("found new wall of %.0f^ at Pos#%d\n", *pos, pos - island);
		wall = pos;
	}
	cout << "^^^ end of fwd scan ; beginning backward scan vvv\n";
	//backward scan
	pos = const_cast<float*> (island) + size - 1;
	wall = pos;
	for (--pos; pos > peak; --pos) {
		if (*wall > *pos) {
			accu += *wall - *pos; // accumulate water
			printf("adding %.0f liter of water at Pos#%d (T=%.0f)\n", *wall - *pos,
					pos - island, accu);
			continue;
		}
		//Note all new walls must match or exceed previous wall.
		printf("found new wall of %.0f^ at Pos#%d\n", *pos, pos - island);
		wall = pos;
	}
	printf("T=%.0f\n", accu);
}
int main() {
	twoPassAlgo();
	accu = 0;
	cout<<"-----------------------------\n";
	onePassAlgo();
}/* Requirement -- a one-dimentional island is completely covered with columns of bricks.
 If  between Column
 A(height 9) and Column B(10) all columns are lower, then we get a basin to
 collect rainfall. Watermark height (absolute) will be 9.  We can easily calculate the
 amount of water. If I give you all the column heights, give me total rainfall collected.
 Code showcasing
 - stl algo over raw array
 - array/pointer manipulation
 - array initialization
 - array size detection
 - std::max_element modified
 - std::swap
 */
