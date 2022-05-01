//
//	Piece - handles all the basic functionality for game pieces
//

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Piece {
protected:
	Sprite m_sprite;
	std::string m_type;
	int m_typeNum;
	std::string m_color;
	bool m_isCaptured;
	bool m_wasMoved;
	bool m_isHeld;
	Vector2f m_oldPosition;
	Vector2f m_newPosition;
	std::vector<std::string> m_moves;
public:
	//constructors
	Piece();

	//selectors
	Sprite GetSprite();
	std::string GetType();
	int GetTypeNum();
	std::string GetColor();
	bool IsCaptured();
	bool WasMoved();
	bool IsHeld();
	Vector2f GetOldPosition();
	Vector2f GetSpritePosition();
	int GetSpriteX();
	int GetSpriteY();
	std::vector<std::string> GetValidMoves();

	//mutators
	void SetSpriteTexture(const Texture& a_tex);
	void SetSpritePosition(const int a_x, const int a_y);
	void SetSpriteTextureRect(const int a_left, const int a_top, const int a_width, const int a_height);
	void SetSpriteScale(const double a_scale);
	void SetType(const std::string a_type);
	void SetTypeNum(const int a_type);
	void SetColor(const std::string a_color);
	void SetCapture(const bool a_isCaptured);
	void SetMoved(const bool a_wasMoved);
	void SetHeld(const bool a_held);
	void SetOldPosition(const Vector2f a_position);
	void SetNewPosition(const Vector2f a_position);

	//utility functions
	bool IsCurrentlyHeld(const int a_x, const int a_y);
	virtual void UpdateValidMoves(const int a_size, Piece* a_pieces[]);
	virtual void ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
	void ClearValidMoves();
	bool IsValidMove(const std::string a_move);
	bool IsOutOfBounds(const std::string a_move);
	bool IsObstructed(const std::string a_move, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
	std::string ToChessNote(const Vector2f a_position, const int a_size);
	Vector2f ToCoord(const std::string a_position, const int a_size);
};