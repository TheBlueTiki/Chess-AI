//
//	Bishop - handles move generation for the bishop piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class Bishop : public Piece {
private:

public:
	//constructors
	Bishop();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddDiagonalMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);
};