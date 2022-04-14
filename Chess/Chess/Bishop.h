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
	void ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
	void AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], int a_size, std::vector<std::string>& a_moves);
};