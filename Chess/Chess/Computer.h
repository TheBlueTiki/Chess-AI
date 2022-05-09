//
//	Computer - contains all of decision-making processes for the computer to make a move
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include<algorithm>
#include <vector>
#include <time.h>
#include "Piece.h"

using namespace sf;

class Computer {
private:
	
public:
	//constructors
	Computer();
	
	//decision-making
	void TakeTurn(Piece* a_pieces[], const int a_size);
	int MiniMax(int a_depth, int a_index, bool a_maxPlayer, std::vector<int> a_values, int a_alpha, int a_beta);
	int FindDefense(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
	int ProtectKing(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, int a_threat, int a_king);

	//move collection
	std::vector<std::string> GetMoves(Piece* a_pieces[], const int a_size);
	std::vector<std::string> GetThreatPath(std::string a_pos1, std::string a_pos2, bool a_ignore);
	std::vector<std::string> StraightThreatPath(std::string a_pos1, std::string a_pos2, int a_direction);
	std::vector<std::string> DiagonalThreatPath(std::string a_pos1, std::string a_pos2, int a_direction);
	std::vector<std::string> StraightThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction);
	std::vector<std::string> DiagonalThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction);

	//scoring
	std::vector<int> ScoreMoves(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, bool a_lookAhead);
	int GetScore(Piece* a_pieces[], const int a_size, const std::string a_move, bool a_lookAhead);
	int GetCaptureScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to, int a_piecePos);
	int ScorePotential(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to);
	int GetDefenseScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to);
	
	//utility
	bool IsInCheck(Piece* a_pieces[], const int a_size);
	bool IsOutOfBounds(const std::string a_move);
	int GetPieceValue(const int a_typeNum);
	void Resize(std::vector<int>& a_values);
	int TreeDepth(std::vector<int>& a_values);
};