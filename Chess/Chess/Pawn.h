//
//	Pawn - handles move generation for the pawn piece
//

#pragma once
#include "Piece.h"
#include <iostream>

class Pawn : public Piece {
private:

public:
	//constructors
	Pawn();

	//movement functions
	void UpdateValidMoves(int a_size, Piece* a_pieces[]);
	void AddMoves(std::string a_oldPos, Piece* a_pieces[], int a_size);

	//utility
	bool PawnObstructed(std::string a_move, Piece* a_pieces[], int a_size);
};