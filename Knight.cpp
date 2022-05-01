#include "Knight.h"

Knight::Knight()
{
    SetType("knight");
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

/**/
/*
Knight::UpdateValidMoves()

NAME

        Knight::UpdateValidMoves - updates the knight's valid move set based on the current board conditions

SYNOPSIS

        void Knight::UpdateValidMoves(const int a_size, Piece* a_pieces[]);
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will create a valid moveset for the knight based on its current position and the
        positions of the other pieces on the board

RETURNS

        void

*/
/**/
void Knight::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddMoves(oldPos, a_pieces, a_size, m_moves);
}
/*void Knight::UpdateValidMoves(const int a_size, Piece* a_pieces[])*/

/**/
/*
Knight::ValidMovesAt()

NAME

        Knight::ValidMovesAt - generates valid moves at a given position

SYNOPSIS

        void Knight::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the knight to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Knight::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddMoves(a_pos, a_pieces, a_size, a_moves);
}
/*void Knight::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Knight::AddMoves()

NAME

        Knight::AddMoves - generates moves at a given position

SYNOPSIS

        void Knight::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the knight to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Knight::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //tall 'L' formations
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] + 2);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] - 2);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] + 2);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] - 2);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //short 'L' formations
    newPos = "";
    newPos += char(a_pos[0] + 2);
    newPos += char(a_pos[1] + 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] + 2);
    newPos += char(a_pos[1] - 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 2);
    newPos += char(a_pos[1] + 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
    newPos = "";
    newPos += char(a_pos[0] - 2);
    newPos += char(a_pos[1] - 1);

    //check if the move is out of bounds or obstructed
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}
/*void Knight::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/
