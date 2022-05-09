#include "Bishop.h"

Bishop::Bishop()
{
    SetType("bishop");
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

/**/
/*
Bishop::UpdateValidMoves()

NAME

        Bishop::UpdateValidMoves - updates the bishop's valid move set based on the current board conditions

SYNOPSIS

        void Bishop::UpdateValidMoves(const int a_size, Piece* a_pieces[]);
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will create a valid moveset for the bishop based on its current position and the
        positions of the other pieces on the board

RETURNS

        void

*/
/**/
void Bishop::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddDiagonalMoves(oldPos, a_pieces, a_size, m_moves);
}
/*void Bishop::UpdateValidMoves(const int a_size, Piece* a_pieces[])*/

/**/
/*
Bishop::ValidMovesAt()

NAME

        Bishop::ValidMovesAt - generates valid moves at a given position

SYNOPSIS

        void Bishop::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the bishop to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Bishop::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddDiagonalMoves(a_pos, a_pieces, a_size, a_moves);
}
/*void Bishop::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Bishop::AddDiagonalMoves()

NAME

        Bishop::AddDiagonalMoves - generates diagonal moves at a given position

SYNOPSIS

        void Bishop::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate diagonal moves for the bishop to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Bishop::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";
    bool stop = false;
    int k = 1;

    //up-right
    while (!stop) {
        newPos += char(a_pos[0] + k);
        newPos += char(a_pos[1] + k);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
            a_moves.push_back(newPos);
            k++;
        }
        else {
            stop = true;
            k = 1;
        }

        newPos = "";
    }

    //up-left
    stop = false;
    while (!stop) {
        newPos += char(a_pos[0] - k);
        newPos += char(a_pos[1] + k);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
            a_moves.push_back(newPos);
            k++;
        }
        else {
            stop = true;
            k = 1;
        }

        newPos = "";
    }

    //bottom-right
    stop = false;
    while (!stop) {
        newPos += char(a_pos[0] + k);
        newPos += char(a_pos[1] - k);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
            a_moves.push_back(newPos);
            k++;
        }
        else {
            stop = true;
            k = 1;
        }

        newPos = "";
    }

    //bottom-left
    stop = false;
    while (!stop) {
        newPos += char(a_pos[0] - k);
        newPos += char(a_pos[1] - k);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
            a_moves.push_back(newPos);
            k++;
        }
        else {
            stop = true;
            k = 1;
        }

        newPos = "";
    }
}
/*void Bishop::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/
