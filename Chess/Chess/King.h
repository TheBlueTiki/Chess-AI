//
//	King - handles move generation for the king piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class King : public Piece {
private:

public:
	//constructors
	King();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddDiagonalMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
	void AddStraightMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
};