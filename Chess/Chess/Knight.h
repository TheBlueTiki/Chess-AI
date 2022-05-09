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
	void UpdateValidMoves(const int a_size, Piece* a_pieces[]);
	void ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
	void AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
};