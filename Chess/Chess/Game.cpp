#include "Game.h"

Game::Game()
{
	SetGridSize(56);
	SetScale(2);
	if (!m_pieceTexture.loadFromFile("images/figures.png")) {
		perror("failed to load texture");
	}
	if (!m_boardTexture.loadFromFile("images/board0.png")) {
		perror("failed to load texture");
	}
	m_board.setTexture(m_boardTexture);
	m_board.setScale(m_scale, m_scale);
	SetTurn(true);
}

Game::Game(const int a_gridSize, const double a_scale)
{
	SetGridSize(a_gridSize);
	SetScale(a_scale);
	if (!m_pieceTexture.loadFromFile("images/figures.png")) {
		perror("failed to load texture");
	}
	if (!m_boardTexture.loadFromFile("images/board0.png")) {
		perror("failed to load texture");
	}
	m_board.setTexture(m_boardTexture);
	m_board.setScale(m_scale, m_scale);
	SetTurn(true);
}

Texture Game::GetBoardTexture()
{
	return m_boardTexture;
}

Texture Game::GetPieceTexture()
{
	return m_pieceTexture;
}

Sprite Game::GetBoardSprite()
{
	return m_board;
}

void Game::DrawBoard(RenderWindow& a_win)
{
	a_win.draw(m_board);
}

void Game::DrawPieces(RenderWindow& a_win)
{
	for (int i = 0; i < 32; i++) {
		a_win.draw(m_pieces[i]->GetSprite());
	}
}

/**/
/*
Game::GeneratePieces()

NAME

		Game::GeneratePieces - sets up all the game pieces

SYNOPSIS

		void Game::GeneratePieces();

DESCRIPTION

		This function will construct and set all the necessary data for all 
		of the pieces in the game.

RETURNS

		void

*/
/**/
void Game::GeneratePieces()
{
	int k = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int n = m_setup[i][j];

			//skip blank spaces
			if (n == 0) {
				continue;
			}

			//for positioning pieces on the board
			int x = abs(n) - 1;
			int  y;

			//set the piece's typing
			switch (abs(n)) {
			case 1:
				m_pieces[k] = new Rook;
				m_pieces[k]->SetType("rook");
				break;
			case 2:
				m_pieces[k] = new Knight;
				m_pieces[k]->SetType("knight");
				break;
			case 3:
				m_pieces[k] = new Bishop;
				m_pieces[k]->SetType("bishop");
				break;
			case 4:
				m_pieces[k] = new Queen;
				m_pieces[k]->SetType("queen");
				break;
			case 5:
				m_pieces[k] = new King;
				m_pieces[k]->SetType("king");
				break;
			case 6:
				m_pieces[k] = new Pawn;
				m_pieces[k]->SetType("pawn");
				break;
			default:
				m_pieces[k] = new Piece;
				m_pieces[k]->SetType("piece");
			}

			//check which side of the board the piece is on
			if (n > 0) {
				m_pieces[k]->SetColor("white");
				y = 1;
			}
			else {
				m_pieces[k]->SetColor("black");
				y = 0;
			}

			//set the piece texture
			m_pieces[k]->SetSpriteTexture(m_pieceTexture);
			m_pieces[k]->SetSpriteScale(m_scale);
			m_pieces[k]->SetSpriteTextureRect(m_gridSize * x, m_gridSize * y, m_gridSize, m_gridSize);

			//set the sprite's position on the board
			m_pieces[k]->SetSpritePosition(m_gridSize * j * m_scale, m_gridSize * i * m_scale);
			m_pieces[k]->SetOldPosition(m_pieces[k]->GetSpritePosition());

			k++;
		}
	}

	//generate the pieces' first set of valid moves
	for (int i = 0; i < k; i++) {
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}
}
/*void Game::GeneratePieces();*/

/**/
/*
Game::ResetPieces()

NAME

		Game::ResetPieces - returns all pieces to their original states from the
		start of the game

SYNOPSIS

		void Game::ResetPieces();

DESCRIPTION

		This function will move all pieces back to their initial positions and reset
		all of their data affected by gameplay

RETURNS

		void

*/
/**/
void Game::ResetPieces()
{
	int k = 0;

	for (int i = 0; i < 32; i++) {
		m_pieces[i]->SetCapture(false);
		m_pieces[i]->SetMoved(false);
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int n = m_setup[i][j];

			//skip blank spaces
			if (n == 0) {
				continue;
			}

			//move back to original position
			m_pieces[k]->SetSpritePosition(m_gridSize * j * m_scale, m_gridSize * i * m_scale);
			//new position
			m_pieces[k]->SetOldPosition(m_pieces[k]->GetSpritePosition());

			k++;
		}
	}

	SetTurn(true);
}
/*void Game::ResetPieces();*/

/**/
/*
Game::CheckHeld()

NAME

		Game::CheckHeld - checks if any of the pieces are being held by the mouse

SYNOPSIS

		void Game::CheckHeld(const int a_x, const int a_y, float& a_dx, float& a_dy);
			a_x  --> the x coordinate of the mouse's position
			a_y --> the y coordinate of the mouse's position
			a_dx  --> updated x coordinate for the piece's position to follow
			a_dy  --> updated y coordinate for the piece's position to follow

DESCRIPTION

		This function will check if any of the pieces are being held and log their
		original positions and update their current positions if so.

RETURNS

		void

*/
/**/
void Game::CheckHeld(const int a_x, const int a_y, float& a_dx, float& a_dy)
{
	//check for pieces being held by the mouse
	for (int i = 0; i < 32; i++) {
		//check if the player is holding the piece
		if (m_pieces[i]->IsCurrentlyHeld(a_x, a_y) && m_pieces[i]->GetColor() == "white") {
			//select the piece
			m_pieces[i]->SetHeld(true);

			//Save the current position for updating
			a_dx = a_x - m_pieces[i]->GetSpriteX();
			a_dy = a_y - m_pieces[i]->GetSpriteY();

			//update the piece's old position
			m_pieces[i]->SetOldPosition(m_pieces[i]->GetSpritePosition());
		}
	}
}
/*void Game::CheckHeld(const int a_x, const int a_y, float& a_dx, float& a_dy);*/

/**/
/*
Game::DropPiece()

NAME

		Game::DropPiece - updates the states of all pieces after a piece is moved

SYNOPSIS

		void Game::DropPiece();

DESCRIPTION

		This function will check if any pieces were moved. If a piece was moved, it will
		update the piece's positions, check move validation, check for captures, and update 
		the valid move sets of all pieces

RETURNS

		void

*/
/**/
void Game::DropPiece()
{
	//inspect all pieces
	for (int i = 0; i < 32; i++) {
		if (m_pieces[i]->IsHeld()) {
			//snap the moved piece to the grid
			Vector2f pos = m_pieces[i]->GetSpritePosition() + Vector2f((m_gridSize * m_scale) / 2 , (m_gridSize * m_scale) / 2);
			Vector2f newPos = Vector2f((m_gridSize  * m_scale) * int(pos.x / (m_gridSize * m_scale)), (m_gridSize * m_scale) * int(pos.y / (m_gridSize * m_scale)));
			m_pieces[i]->SetSpritePosition(newPos.x, newPos.y);
			//m_pieces[i]->SetNewPosition(newPos);

			//deselect
			m_pieces[i]->SetHeld(false);

			//move validation
			if (!m_pieces[i]->IsValidMove(m_pieces[i]->ToChessNote(m_pieces[i]->GetSpritePosition(), m_gridSize * m_scale)))
			{
				//move the piece back to its old position if the move is invalid
				m_pieces[i]->SetSpritePosition(m_pieces[i]->GetOldPosition().x, m_pieces[i]->GetOldPosition().y);
			}
			else {
				//output the move in chess notation
				std::cout << m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale) << m_pieces[i]->ToChessNote(m_pieces[i]->GetSpritePosition(), m_gridSize * m_scale) << std::endl;
				
				//mark that the piece has been moved
				if (!m_pieces[i]->WasMoved()) {
					m_pieces[i]->SetMoved(true);
				}

				//capture overlapping pieces
				CheckCapture(m_pieces[i]);

				SetTurn(false);
			}
		}
		//update all pieces' valid moves
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}
	
	//computer's turn
	if (!HasTurn() && !HasWinner()) {
		ComputerTurn();
	}
}
/*void Game::DropPiece();*/

/**/
/*
Game::UpdatePiecePositions()

NAME

		Game::UpdatePiecePositions - updates the positions of pieces being dragged by the mouse

SYNOPSIS

		void Game::UpdatePiecePositions(const int a_x, const int a_y, float& a_dx, float& a_dy);
			a_x  --> the x coordinate of the mouse's position
			a_y --> the y coordinate of the mouse's position
			a_dx  --> updated x coordinate for the piece's position to follow
			a_dy  --> updated y coordinate for the piece's position to follow

DESCRIPTION

		This function will check if any of the pieces are being held and update their
		positions based on the mouse movement

RETURNS

		void

*/
/**/
void Game::UpdatePiecePositions(const int a_x, const int a_y, const float a_dx, const float a_dy)
{
	//inspect all pieces
	for (int i = 0; i < 32; i++) {
		//update the position of held pieces
		if (m_pieces[i]->IsHeld()) {
			m_pieces[i]->SetSpritePosition(a_x - a_dx, a_y - a_dy);
		}
	}
}
/*void Game::UpdatePiecePositions(const int a_x, const int a_y, const float a_dx, const float a_dy);*/

/**/
/*
Game::CheckCapture()

NAME

		Game::CheckCapture - checks for overlapping pieces attempting to capture

SYNOPSIS

		void Game::CheckCapture(Piece* a_piece);
			a_piece  --> the piece attemting to capture

DESCRIPTION

		This function will check if the specified piece is overlapping a piece of the
		opposite color and capture the piece it's overlapping if so.

RETURNS

		void

*/
/**/
void Game::CheckCapture(Piece* a_piece)
{
	for (int i = 0; i < 32; i++) {
		//check if the pieces are overlapping and opposite colors
		if (a_piece->GetSpritePosition() == m_pieces[i]->GetSpritePosition() && a_piece->GetColor() != m_pieces[i]->GetColor()) {
			//mark and move the captured piece off the screen
			m_pieces[i]->SetCapture(true);
			m_pieces[i]->SetSpritePosition(-200, -200);
			std::cout << a_piece->GetColor() << " " << a_piece->GetType() << " capped " << m_pieces[i]->GetColor() << " " << m_pieces[i]->GetType() << std::endl;
		}
	}
}
/*void Game::CheckCapture(Piece* a_piece);*/

void Game::ComputerTurn()
{
	//update valid movesets
	for (int i = 0; i < 32; i++) {
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}

	m_ai.TakeTurn(m_pieces, m_gridSize * m_scale);

	for (int i = 0; i < 32; i++) {
		if (m_pieces[i]->IsHeld()) {
			//capture overlapping pieces
			CheckCapture(m_pieces[i]);
			m_pieces[i]->SetHeld(false);
		}
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}

	SetTurn(true);
}

/**/
/*
Game::HasWinner()

NAME

		Game::HasWinner - checks if a player won the game

SYNOPSIS

		bool Game::HasWinner();

DESCRIPTION

		This function will check if the game's win condition was met (ie. a king
		was captured).

RETURNS

		Returns true if a captured king piece was found, false if neither of the
		king pieces are captured.

*/
/**/
bool Game::HasWinner()
{
	for (int i = 0; i < 32; i++) {
		if (m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
			return true;
		}
	}
	return false;
}
/*bool Game::HasWinner();*/

/**/
/*
Game::GetWinner()

NAME

		Game::GetWinner - determines the winner of the game when the game ends

SYNOPSIS

		std::string Game::GetWinner();

DESCRIPTION

		This function will check if the game is over and return the name of the 
		side that won.

RETURNS

		Returns the color of the side that won in a string. Returns "none" if the game
		hasn't ended yet.

*/
/**/
std::string Game::GetWinner()
{
	if (HasWinner()) {
		for (int i = 0; i < 32; i++) {
			if (m_pieces[i]->GetColor() == "white" && m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
				return "black";
			}
			else if (m_pieces[i]->GetColor() == "black" && m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
				return "white";
			}
		}
	}
	return "none";
}
/*std::string Game::GetWinner();*/

Piece** Game::GetPieces()
{
	return m_pieces;
}

double Game::GetScale()
{
	return m_scale;
}

int Game::GetGridSize()
{
	return m_gridSize;
}

bool Game::HasTurn()
{
	return m_turn;
}

void Game::SetBoardTexture(const Texture& a_texture)
{
	m_boardTexture = a_texture;
}

void Game::SetPieceTexture(const Texture& a_texture)
{
	m_pieceTexture = a_texture;
}

void Game::SetBoardSprite(const Sprite& a_sprite)
{
	m_board = a_sprite;
}

void Game::SetScale(const int a_scale)
{
	m_scale = a_scale;
}

void Game::SetGridSize(const int a_size)
{
	m_gridSize = a_size;
}

void Game::SetTurn(bool a_turn)
{
	m_turn = a_turn;
}
