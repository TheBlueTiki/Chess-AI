//
//	Game - contains all of the means to run a game of chess
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include"Menu.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Computer.h"

using namespace sf;

class Game {
private:
	Texture m_boardTexture, m_pieceTexture;
	Sprite m_board;
	Piece* m_pieces[32];
	double m_scale;
	int m_gridSize;
	int m_setup[8][8] = { -1, -2, -3, -4, -5, -3, -2, -1,
						-6 , -6, -6, -6, -6, -6, -6, -6,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						6, 6, 6, 6, 6, 6, 6, 6,
						1, 2, 3, 4, 5, 3, 2, 1 };
	Computer m_ai;
	bool m_turn;
public:
	//constructors
	Game();
	Game(const int a_gridSize, const double a_scale);

	//selectors
	Texture GetBoardTexture();
	Texture GetPieceTexture();
	Sprite GetBoardSprite();
	Piece** GetPieces();
	double GetScale();
	int GetGridSize();
	bool HasTurn();

	//mutators
	void SetBoardTexture(const Texture& a_texture);
	void SetPieceTexture(const Texture& a_texture);
	void SetBoardSprite(const Sprite& a_sprite);
	void SetScale(const int a_scale);
	void SetGridSize(const int a_size);
	void SetTurn(bool a_turn);

	//draw functions
	void DrawBoard(RenderWindow& a_win);
	void DrawPieces(RenderWindow& a_win);

	//utility/setup
	void GeneratePieces();
	void ResetPieces();
	void CheckHeld(const int a_x, const int a_y, float& a_dx, float& a_dy);
	void DropPiece();
	void UpdatePiecePositions(const int a_x, const int a_y, const float a_dx, const float a_dy);
	void CheckCapture(Piece* a_piece);
	void ComputerTurn();
	bool HasWinner();
	std::string GetWinner();
};