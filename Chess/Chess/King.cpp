#include "King.h"

King::King()
{
    SetType("king");
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

/**/
/*
King::UpdateValidMoves()

NAME

        King::UpdateValidMoves - updates the king's valid move set based on the current board conditions

SYNOPSIS

        void King::UpdateValidMoves(const int a_size, Piece* a_pieces[]);
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will create a valid moveset for the king based on its current position and the
        positions of the other pieces on the board

RETURNS

        void

*/
/**/
void King::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddDiagonalMoves(oldPos, a_pieces, a_size, m_moves);
    AddStraightMoves(oldPos, a_pieces, a_size, m_moves);
}
/*void King::UpdateValidMoves(const int a_size, Piece* a_pieces[])*/

/**/
/*
King::ValidMovesAt()

NAME

        King::ValidMovesAt - generates valid moves at a given position

SYNOPSIS

        void King::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the king to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void King::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddDiagonalMoves(a_pos, a_pieces, a_size, a_moves);
    AddStraightMoves(a_pos, a_pieces, a_size, a_moves);
}
/*void King::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
King::AddDiagonalMoves()

NAME

        King::AddDiagonalMoves - generates diagonal moves at a given position

SYNOPSIS

        void King::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate diagonal moves for the king to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void King::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //up-right
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] + 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //up-left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] + 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //bottom-right
    newPos = "";
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] - 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //bottom-left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] - 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}
/*void King::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
King::AddStraightMoves()

NAME

        King::AddStraightMoves - generates straight moves at a given position

SYNOPSIS

        void King::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate straight moves for the king to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void King::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //right
    newPos += char(a_pos[0] + 1);
    newPos += a_pos[1];

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += a_pos[1];

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //up
    newPos = "";
    newPos += a_pos[0];
    newPos += char(a_pos[1] + 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //down
    newPos = "";
    newPos += a_pos[0];
    newPos += char(a_pos[1] - 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}
/*void King::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/
