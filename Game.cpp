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
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			case 2:
				m_pieces[k] = new Knight;
				m_pieces[k]->SetType("knight");
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			case 3:
				m_pieces[k] = new Bishop;
				m_pieces[k]->SetType("bishop");
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			case 4:
				m_pieces[k] = new Queen;
				m_pieces[k]->SetType("queen");
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			case 5:
				m_pieces[k] = new King;
				m_pieces[k]->SetType("king");
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			case 6:
				m_pieces[k] = new Pawn;
				m_pieces[k]->SetType("pawn");
				m_pieces[k]->SetTypeNum(abs(n));
				break;
			default:
				m_pieces[k] = new Piece;
				m_pieces[k]->SetType("piece");
				m_pieces[k]->SetTypeNum(0);
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

	//reset tags
	for (int i = 0; i < 32; i++) {
		m_pieces[i]->SetCapture(false);
		m_pieces[i]->SetMoved(false);
	}

	//return all pieces to their original positions
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
	
	std::cout << "-=New Round=-" << std::endl;

	//enable the player's turn
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
	for (int i = 16; i < 32; i++) {
		//check if the player is holding the piece
		if (m_pieces[i]->IsCurrentlyHeld(a_x, a_y)) {
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
	for (int i = 16; i < 32; i++) {
		if (m_pieces[i]->IsHeld()) {
			//snap the moved piece to the grid
			Vector2f pos = m_pieces[i]->GetSpritePosition() + Vector2f((m_gridSize * m_scale) / 2 , (m_gridSize * m_scale) / 2);
			Vector2f newPos = Vector2f((m_gridSize  * m_scale) * int(pos.x / (m_gridSize * m_scale)), (m_gridSize * m_scale) * int(pos.y / (m_gridSize * m_scale)));
			m_pieces[i]->SetSpritePosition(newPos.x, newPos.y);

			//deselect
			m_pieces[i]->SetHeld(false);

			//move validation
			if (!m_pieces[i]->IsValidMove(m_pieces[i]->ToChessNote(m_pieces[i]->GetSpritePosition(), m_gridSize * m_scale)))
			{
				//check for castling
				if (IsCastling(m_pieces[i], newPos) && CanCastle(m_pieces[i], newPos)) {
					Castle(m_pieces[i], newPos);
				}
				else {
					//move the piece back to its old position if the move is invalid
					m_pieces[i]->SetSpritePosition(m_pieces[i]->GetOldPosition().x, m_pieces[i]->GetOldPosition().y);
				}
			}
			else {
				//output the move in chess notation
				std::cout << "Player: " << m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale) << m_pieces[i]->ToChessNote(m_pieces[i]->GetSpritePosition(), m_gridSize * m_scale) << std::endl;
				
				//mark that the piece has been moved
				if (!m_pieces[i]->WasMoved()) {
					m_pieces[i]->SetMoved(true);
				}

				//capture overlapping pieces
				CheckCapture(m_pieces[i]);

				//disable the player's turn
				SetTurn(false);
			}
		}
		//update all pieces' valid moves
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
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
	for (int i = 16; i < 32; i++) {
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
		if (!a_piece->IsCaptured() && a_piece->GetSpritePosition() == m_pieces[i]->GetSpritePosition() && a_piece->GetColor() != m_pieces[i]->GetColor()) {
			//mark and move the captured piece off the screen
			m_pieces[i]->SetCapture(true);
			m_pieces[i]->SetSpritePosition(-200, -200);
			m_pieces[i]->SetOldPosition(Vector2f(-200, -200));
			std::cout << a_piece->GetColor() << " " << a_piece->GetType() << " --> " << m_pieces[i]->GetColor() << " " << m_pieces[i]->GetType() << std::endl;
		}
	}
}
/*void Game::CheckCapture(Piece* a_piece);*/

/**/
/*
Game::ComputerTurn()

NAME

		Game::ComputerTurn - allows the computer to take its turn

SYNOPSIS

		void Game::ComputerTurn();

DESCRIPTION

		This function will let the computer player take its turn, then update the board and 
		reenable the human player's turn after it's done

RETURNS

		void

*/
/**/
void Game::ComputerTurn()
{
	//update valid movesets
	for (int i = 0; i < 32; i++) {
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}

	//let the computer take its turn
	m_comp.TakeTurn(m_pieces, m_gridSize * m_scale);

	//chesk for captures
	for (int i = 0; i < 16; i++) {
		if (m_pieces[i]->IsHeld()) {
			//capture overlapping pieces
			CheckCapture(m_pieces[i]);
			m_pieces[i]->SetHeld(false);
		}

		//update valid move sets
		m_pieces[i]->UpdateValidMoves(m_gridSize * m_scale, m_pieces);
	}

	//enable the player's turn
	SetTurn(true);
}
/*void Game::ComputerTurn()*/

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
		//check if a king was captured
		if (m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
			return true;
		}
	}
	return false;
}
/*bool Game::HasWinner();*/

/**/
/*
Game::IsInCheck()

NAME

		Game::IsInCheck - checks if the human player's king is in check

SYNOPSIS

		bool Game::IsInCheck();

DESCRIPTION

		This function will check if the king is in danger of being captured next turn.

RETURNS

		Returns true if an opposing piece has a move that can capture the king, false if
		no threats were found.

*/
/**/
bool Game::IsInCheck()
{
	int kingIndex;

	//find the king
	for (int i = 16; i < 32; i++) {
		if (!m_pieces[i]->IsCaptured() && m_pieces[i]->GetType() == "king") {
			kingIndex = i;
		}
	}

	std::vector<std::string> moves;

	//check if any pieces can capture the king
	for (int i = 0; i < 16; i++) {
		//skip captured pieces
		if (m_pieces[i]->IsCaptured()) {
			continue;
		}

		//get the next set of moves
		moves.clear();
		moves = m_pieces[i]->GetValidMoves();

		//check all moves
		for (int j = 0; j < moves.size(); j++) {
			//check if a move can capture the king
			if (moves[j] == m_pieces[kingIndex]->ToChessNote(m_pieces[kingIndex]->GetOldPosition(), m_gridSize * m_scale)) {
				return true;
			}
		}
	}

	return false;
}
/*bool Game::IsInCheck()*/

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
			//check if the white king was captured
			if (m_pieces[i]->GetColor() == "white" && m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
				return "black";
			}
			//check if the black king was captured
			else if (m_pieces[i]->GetColor() == "black" && m_pieces[i]->GetType() == "king" && m_pieces[i]->IsCaptured()) {
				return "white";
			}
		}
	}
	return "none";
}
/*std::string Game::GetWinner();*/

/**/
/*
Game::IsCastling()

NAME

		Game::IsCastling - checks if the player is trying to castle

SYNOPSIS

		bool Game::IsCastling(Piece* a_piece, const Vector2f a_intent);
			a_piece  --> the piece attemting to castle
			a_intent  --> the position that the piece is attempting to move to

DESCRIPTION

		This function will check if the specified piece is a king in the bottom row overlapping
		a rook in a corner with the intention of castling.

RETURNS

		Returns true if the player is attempting to castle with the king, false if the conditions
		do not imply an attempt to castle.

*/
/**/
bool Game::IsCastling(Piece* a_piece, const Vector2f a_intent)
{
	//convert the intended move and the original position to chess notation
	std::string move = a_piece->ToChessNote(a_intent, m_gridSize * m_scale);
	std::string oldPos = a_piece->ToChessNote(a_piece->GetOldPosition(), m_gridSize * m_scale);

	//check if the intended move is a corner, the piece making the move is a king, and the piece was already in the bottom row
	if ((move == "a1" || move == "h1") && a_piece->GetType() == "king" && oldPos[1] == '1') {
		for (int i = 16; i < 32; i++) {
			//check if the piece is overlapping a rook of the same color that hasn't been moved
			if (m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale) == move && m_pieces[i]->GetType() == "rook" && !m_pieces[i]->WasMoved() && m_pieces[i]->GetColor() == a_piece->GetColor()) {
				return true;
			}
		}
	}

	return false;
}
/*bool Game::IsCastling(Piece* a_piece, const Vector2f a_intent)*/

/**/
/*
Game::CanCastle()

NAME

		Game::CanCastle - checks if game conditions allow for castling

SYNOPSIS

		bool Game::CanCastle(Piece* a_piece, const Vector2f a_intent);
			a_piece  --> the piece attemting to castle
			a_intent  --> the position that the piece is attempting to move to

DESCRIPTION

		This function will check if the king hasn't met any conditions preventing it from castling,
		and it will check if there are open spaces between it and the rook.

RETURNS

		Returns true if the king is eligible for castling and there are open spaces to allow for it,
		returns false if it runs into any conditions that prevent castling.

*/
/**/
bool Game::CanCastle(Piece* a_piece, const Vector2f a_intent)
{
	//convert the intended move and the original position to chess notation
	std::string move = a_piece->ToChessNote(a_intent, m_gridSize * m_scale);
	std::string oldPos = a_piece->ToChessNote(a_piece->GetOldPosition(), m_gridSize * m_scale);

	std::string piecePos = "";
	std::string inspect = "";
	int k = 1;

	//if it is not the king's first move or if the king is in check, castling isn't allowed
	if (a_piece->WasMoved() || IsInCheck()) {
		return false;
	}

	//check for left castling
	if (move == "a1") {
		while (inspect != oldPos) {
			//check the spaces between the king and rook
			inspect = "";
			inspect += char(move[0] + k);
			inspect += move[1];

			//check if a piece is in the way
			for (int i = 0; i < 32; i++) {
				//skip captured pieces
				if (m_pieces[i]->IsCaptured()) {
					continue;
				}

				piecePos = m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale);
				if (piecePos != oldPos && piecePos == inspect) {
					return false;
				}
			}

			k++;
		}
	}
	//check for right castling
	else if (move == "h1") {
		while (inspect != oldPos) {
			//check the spaces between the king and rook
			inspect = "";
			inspect += char(move[0] - k);
			inspect += move[1];

			//check if a piece is in the way
			for (int i = 0; i < 32; i++) {
				//skip captured pieces
				if (m_pieces[i]->IsCaptured()) {
					continue;
				}

				piecePos = m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale);
				if (piecePos != oldPos && piecePos == inspect) {
					return false;
				}
			}

			k++;
		}
	}
	//if castling isn't intended
	else {
		return false;
	}

	return true;
}
/*bool Game::CanCastle(Piece* a_piece, const Vector2f a_intent)*/


/**/
/*
Game::Castle()

NAME

		Game::Castle - moves the king and rook into castling formation

SYNOPSIS

		void Game::Castle(Piece* a_piece, const Vector2f a_intent);
			a_piece  --> the piece attemting to castle
			a_intent  --> the position that the piece is attempting to move to

DESCRIPTION

		This function will move the king two spaces to the left or right, then move the rook on the 
		other side of the king to put them in castling formation.

RETURNS

		void

*/
/**/
void Game::Castle(Piece* a_piece, const Vector2f a_intent)
{
	//convert the intended move and the original position to chess notation
	std::string move = a_piece->ToChessNote(a_intent, m_gridSize * m_scale);
	std::string oldPos = a_piece->ToChessNote(a_piece->GetOldPosition(), m_gridSize * m_scale);

	std::string newPos1 = "";
	std::string newPos2 = "";
	int rookIndex, kingIndex;

	//find the rook and king's indices
	for (int i = 16; i < 32; i++) {
		//skip captured pieces
		if (m_pieces[i]->IsCaptured()) {
			continue;
		}

		//save the rook's index
		if (m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale) == move) {
			rookIndex = i;
		}
		//save the king's index
		else if (m_pieces[i]->ToChessNote(m_pieces[i]->GetOldPosition(), m_gridSize * m_scale) == oldPos) {
			kingIndex = i;
		}
	}

	//check for left castling
	if (move == "a1") {	
		newPos1 += char(oldPos[0] - 2);
		newPos1 += oldPos[1];
		Vector2f kingMove = m_pieces[kingIndex]->ToCoord(newPos1, m_gridSize * m_scale);

		oldPos = m_pieces[kingIndex]->ToChessNote(kingMove, m_gridSize * m_scale);
		newPos2 += char(oldPos[0] + 1);
		newPos2 += oldPos[1];
		Vector2f rookMove = m_pieces[rookIndex]->ToCoord(newPos2, m_gridSize * m_scale);

		//update positions
		m_pieces[kingIndex]->SetSpritePosition(kingMove.x, kingMove.y);
		m_pieces[rookIndex]->SetSpritePosition(rookMove.x, rookMove.y);
	}
	//check for right castling
	else if (move == "h1") {
		newPos1 += char(oldPos[0] + 2);
		newPos1 += oldPos[1];
		Vector2f kingMove = m_pieces[kingIndex]->ToCoord(newPos1, m_gridSize * m_scale);

		oldPos = m_pieces[kingIndex]->ToChessNote(kingMove, m_gridSize * m_scale);
		newPos2 += char(oldPos[0] - 1);
		newPos2 += oldPos[1];
		Vector2f rookMove = m_pieces[rookIndex]->ToCoord(newPos2, m_gridSize * m_scale);

		//update positions
		m_pieces[kingIndex]->SetSpritePosition(kingMove.x, kingMove.y);
		m_pieces[rookIndex]->SetSpritePosition(rookMove.x, rookMove.y);
	}

	//output the moves in chess notation
	std::cout << "Player: " << m_pieces[kingIndex]->ToChessNote(m_pieces[kingIndex]->GetOldPosition(), m_gridSize * m_scale) << newPos1 << std::endl;
	std::cout << "Player: " << m_pieces[rookIndex]->ToChessNote(m_pieces[rookIndex]->GetOldPosition(), m_gridSize * m_scale) << newPos2 << std::endl;

	//update tags
	m_pieces[rookIndex]->SetMoved(true);
	m_pieces[kingIndex]->SetMoved(true);

	//disable the player's turn
	SetTurn(false);
}
/*void Game::Castle(Piece* a_piece, const Vector2f a_intent)*/

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
