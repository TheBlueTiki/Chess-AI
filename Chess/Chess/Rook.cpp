#include "Rook.h"

Rook::Rook()
{
    SetType("rook");
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

/**/
/*
Rook::UpdateValidMoves()

NAME

        Rook::UpdateValidMoves - updates the rook's valid move set based on the current board conditions

SYNOPSIS

        void Rook::UpdateValidMoves(const int a_size, Piece* a_pieces[]);
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will create a valid moveset for the rook based on its current position and the
        positions of the other pieces on the board

RETURNS

        void

*/
/**/
void Rook::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddStraightMoves(oldPos, a_pieces, a_size, m_moves);
}
/*void Rook::UpdateValidMoves(const int a_size, Piece* a_pieces[])*/

/**/
/*
Rook::ValidMovesAt()

NAME

        Rook::ValidMovesAt - generates valid moves at a given position

SYNOPSIS

        void Rook::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the rook to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Rook::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddStraightMoves(a_pos, a_pieces, a_size, a_moves);
}
/*void Rook::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Rook::AddStraightMoves()

NAME

        Rook::AddStraightMoves - generates straight moves at a given position

SYNOPSIS

        void Rook::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate straight moves for the rook to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Rook::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";
    bool stop = false;
    int k = 1;

    //right
    while (!stop) {
        newPos += char(a_pos[0] + k);
        newPos += a_pos[1];

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

    //left
    stop = false;
    while (!stop) {
        newPos += char(a_pos[0] - k);
        newPos += a_pos[1];

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

    //up
    stop = false;
    while (!stop) {
        newPos += a_pos[0];
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

    //down
    stop = false;
    while (!stop) {
        newPos += a_pos[0];
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
/*void Rook::AddStraightMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/
