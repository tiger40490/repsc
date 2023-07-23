/** v0.9
 * simple value object structs
 */
#ifndef VALUEOBJ_H_
#define VALUEOBJ_H_

#include "Util.h"
#include <iomanip>

extern const char ICE;  //needed
struct Board;

class Cell { // a unit on the board.
	/**
	 * Each cell is either empty (the default), filled with ice ('-')
	 * or occupied by a piece , which we call the "host piece".
	 *
	 * There are exactly 4 cells occupied by each host piece.
	 *
	 * There are two mutable fields:
	 */
	char hostShape;
	unsigned int hostObjId;
	Board * hostBoard;
public:
	Cell():	hostShape(' '), hostObjId(UNOCCUPIED){} //default dummy values

	bool isOccupiedOrFrozen() const{ //returns true if the cell is Filled Or Frozen
		return hostShape != ' ';
	}
	char hostObj() const{
	  assert(this->hostObjId <=13 && "13-piece game is the max for now, due to board size.");
	  switch (this->hostObjId){
		case 6: return '^';
		case 8: return '*';
		case 9: return '(';
		case 10: return ')';
		case 11: return '!';
		case 12: return '@';
		case 13: return '#';
		default: return '0'+hostObjId;
	  }
        }
	friend std::ostream & operator<<(std::ostream &os, Cell const& s) ;
	friend class Board;
};

struct Square{//a unit in a Shape
	int const x,y;//the coordiates of this Square within the host Shape

	/** This is a flag to indicate if this Square is at bottom of the host Shape.
 	 * For a T piece, only the central Square is NOT at bottom.
	 *
	 * if a square is at the bottom of the shape, then
	 * only we will scan the shadow below it.
	 */
	bool const isBottom;

	Square(int _x, int _y, bool _b): x(_x), y(_y), isBottom(_b){}
};

struct Shape {
	char const name;

	/** The 4 Squares in the shape each has an x/y coordinate relative
	 * to the left-bottom "anchor" of the shape.
	 *
	 * The anchor is at (0,0) but may NOT be one of the 4 squares!
	 */
	Square const xy[4];

	/** When we construct a Shape, we already have the 4 Squares. Each
	* Square object knows its position within this shape.
	*/
	Shape(char _name,Square const & a, Square const & b,
			 Square const & c, Square const & d)
	: name(_name), xy( (Square []){a,b,c,d} ){}
private: 
	Shape(Shape const &);
	Shape & operator=(Shape const&);
};
extern Shape I,Q,S,Z,L,J,T; 

struct Piece{
	Shape const * const shape; //each Piece has a pointer to one of the 7 Shapes
	int const id; //each Piece has a unique id

	Piece(Shape const * const _shape, int const _id) : shape(_shape), id(_id){}
};

//without "inline" we break ODR!
inline std::ostream & operator<<(std::ostream &os, std::pair<int,int> const& p) {
	os<<" "<<p.first<<","<<p.second<<" ";
	return os;
}
inline std::ostream & operator<<(std::ostream &os, Square const& p) {
	os<<" "<<p.x<<","<<p.y<<" ";
	return os;
}
inline std::ostream & operator<<(std::ostream &os, Shape const& s) {
	os<<s.name<<s.xy[0]<<s.xy[1]<<s.xy[2]<<s.xy[3]<<std::endl;
	return os;
}
inline std::ostream & operator<<(std::ostream &os, Piece const& p) {
	os<<p.id<<"=id "<<*(p.shape)<<std::endl;
	return os;
}

#endif /* VALUEOBJ_H_ */
