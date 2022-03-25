//
//	Rook - handles move generation for the rook piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class Rook : public Piece {
private:

public:
	//constructors
	Rook();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddStraightMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
};