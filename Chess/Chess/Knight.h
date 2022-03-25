//
//	Knight - handles move generation for the knight piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class Knight : public Piece {
private:

public:
	//constructors
	Knight();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
};