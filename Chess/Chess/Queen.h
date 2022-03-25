//
//	Queen - handles move generation for the queen piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class Queen : public Piece {
private:

public:
	//constructors
	Queen();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddDiagonalMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
	void AddStraightMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
};