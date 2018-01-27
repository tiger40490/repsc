//v0.95
#ifndef BOARD_H_
#define BOARD_H_
#include "ValueObj.h"

//Entire class is defined in a header!
class Board{
	//for each id of a Piece, we can look up the Shape
	//This is a nice little feature to show Q vs q in the visualization.
	//It's hard to visualize the shapes if all shape letters are capital!
	//std::vector<char> pieceId;

	std::map<char, Shape const *> All7Shapes; //lookup cache
	Cell grid[100][BOARD_WIDTH]; //matrix

	std::set<int> markedRows;//complete rows and marked as removed/dead/completed
	size_t fullHeight; //how many non-empty rows so far, including the dead

	size_t nextId; //for the next piece

	std::shared_ptr<Piece> newPiece; 
	std::pair<int,int> anchor; //anchor position (x,y) of the new piece

	//disable copy operations:
	Board(Board const &);
	Board & operator=(Board const &);

	void cleanUp(){ //Invoked after a piece has dropped into place
		for(int i=0;i<4;++i){//the 4 Squares of teh new piece
			Square sq = newPiece->shape->xy[i];
			int x = sq.x + anchor.first; //calc x-coordinate (on the Board) of this Square
			int y = sq.y + anchor.second;

			//-- fill the four Cells on the board for visualization --
			grid[x][y].hostObjId = newPiece->id;
			grid[x][y].hostShape = newPiece->shape->name;
			grid[x][y].hostBoard = this;
			//cout<<x<<y<<" cell filled"<<std::endl;

			//-- now mark completed rows --
			int v=0;
			for (; v<BOARD_WIDTH; ++v){
				if (grid[v][y].hostObjId == UNOCCUPIED) break;// confirmed not full
			}
			if (v==BOARD_WIDTH){//a comleted row
				this->markedRows.insert(y);
			}

			// -- now update height --
			if (/*(unsigned)*/ y+1 > fullHeight) fullHeight = y+1;

			// -- now freeze all shadowed empty cells -- see documentation
			// Rather tricky even if you can visualize the board
			if (!sq.isBottom) continue;
			while(true){
				  if (--y<0) break;
				  //DC<<"freezing "<<x<<y<<std::endl;
				  assert(grid[x][y].hostShape!= ICE);
				  if (grid[x][y].isOccupiedOrFrozen()){
				  	 break; // hit a cell that's occupied or Forzen
					        // so no need to scan further down
				  }
				  grid[x][y].hostShape=ICE; //freeze this Cell
			}
		}
		this->drawRotated();
	}

	//This function doesn't position the new piece
	std::shared_ptr<Piece> make_piece(char shapeName){
		if (!All7Shapes.size()){//lazy initialization
			All7Shapes['I'] = &I;
			All7Shapes['J'] = &J;
			All7Shapes['L'] = &L;
			All7Shapes['Q'] = &Q;
			All7Shapes['S'] = &S;
			All7Shapes['T'] = &T;
			All7Shapes['Z'] = &Z;
			assert (All7Shapes.size() == 7);
		}
		assert (nextId >= 0);
		assert (nextId < 999); //there won't be 1000 pieces in one test
		Shape const * ptr2Shape = All7Shapes[shapeName];
		assert (ptr2Shape != NULL);
		//pieceId.push_back(shapeName);
		//assert(pieceId.size() == nextId+1);
		return std::make_shared<Piece>(ptr2Shape, ++nextId); // no need to free the memory, given the small # of pieces
	}

public:
	Board():fullHeight(0), nextId(0){}

	const int strictHeight() const{ return this->fullHeight - this->markedRows.size(); }

	/** Visualization
	 * turn 90 degrees clockwise and draw the board
	 */
	int drawRotated() const{
		const int ret = strictHeight();
		std::cout<<ret<<" <-- is the height after removals."<<std::endl;

		if (markedRows.size()){
			std::copy(markedRows.begin(), markedRows.end(),
				std::ostream_iterator<int> (std::cout, " "));
			std::cout<<" <- are the completed row names marked for removal."<<std::endl;
		}else{
			std::cout<<"No completed rows marked for removal."<<std::endl;
		}
		std::cout<<"___________________________________________\n";
		std::cout<<"  y = 0   1   2   3   4   5   6   7   8   9\n";
		std::cout<<"      v   v   v   v   v   v   v   v   v   v\n";
		std::cout<<"    _______________________________________";
		std::cout<<"(High hostId are shown in metachars ^=6 *=8 (=9 )=10 !=11 @=12 #=13"<<std::endl;
		for(int i=0;i<BOARD_WIDTH;++i){
			printf("x=%d|", i);
			//cout<<"x="<<i<<"|";
			for(int j=0;grid[i][j].isOccupiedOrFrozen();++j){
				std::cout<<grid[i][j];
			}
			std::cout<<std::endl;
		}
		std::cout<<"===========================================\n\n";;
		return ret;
	}

  /** This is arguably the main algorithm of entire codebase.
  * This algorithm drops a given piece step by step until no further.
  */
  void dropPiece(char shapeName, int column){
	newPiece = this->make_piece(shapeName);
	//MM(*newPiece);
	//first anchor the new piece on a "safe" position 
	anchor = std::make_pair(column, this->fullHeight);
	while(true){ //the algorithm
	  //MM(anchor);
	  for(int i=0;i<4;++i){
		Square const & sq = newPiece->shape->xy[i];
		if (!sq.isBottom) 
		  continue; //No need to check this Square since there's another Square beneath
		int y = sq.y + anchor.second - 1;
		int x = sq.x + anchor.first;
		if (y<0 || this->grid[x][y].isOccupiedOrFrozen()) {
		     //printf("Cell (%d,%d) is unusable.. best anchor is (%d,%d)\n", x,y, anchor.first,anchor.second);
		     this->cleanUp();
		     return;
		}
	  }//all 4 Squares are able to move down, so now drop the anchor position
	  anchor.second--;
	} //while
  } //function


  /** Part of visualization support
  */
  friend std::ostream & operator<<(std::ostream &os, Cell const& s) {
	if (s.hostShape==ICE ){
		os<<"  ..";
	}else{
		if (s.hostObjId%2==0) 
			//helps visual inspection - avoid showing a lot of Q's in a row
			os<<std::setw(3)<<s.hostObj()<<(char)tolower(s.hostShape);
		else    os<<std::setw(3)<<s.hostObj()<<(char)toupper(s.hostShape);
	}
	return os;
  } //friend
}; //class
#endif /* BOARD_H_ */
