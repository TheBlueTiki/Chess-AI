#include "Pawn.h"

Pawn::Pawn()
{
    SetType("pawn");
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

/**/
/*
Pawn::UpdateValidMoves()

NAME

        Pawn::UpdateValidMoves - updates the pawn's valid move set based on the current board conditions

SYNOPSIS

        void Pawn::UpdateValidMoves(const int a_size, Piece* a_pieces[]);
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will create a valid moveset for the pawn based on its current position and the
        positions of the other pieces on the board

RETURNS

        void

*/
/**/
void Pawn::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());
    
    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddMoves(oldPos, a_pieces, a_size, m_moves);
}
/*void Pawn::UpdateValidMoves(const int a_size, Piece* a_pieces[])*/

/**/
/*
Pawn::ValidMovesAt()

NAME

        Pawn::ValidMovesAt - generates valid moves at a given position

SYNOPSIS

        void Pawn::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the pawn to a specified list based on the given position and the
        positions of the other pieces on the board.

RETURNS

        void

*/
/**/
void Pawn::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddMoves(a_pos, a_pieces, a_size, a_moves);
}
/*void Pawn::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Pawn::AddMoves()

NAME

        Pawn::AddMoves - generates moves at a given position

SYNOPSIS

        void Pawn::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_pos  --> the starting position to generate the moves from
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will generate moves for the pawn to a specified list based on the given position, the positions 
        of the other pieces on the board, and other special conditions that affect its movement.

RETURNS

        void

*/
/**/
void Pawn::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //white pawns move up
    if (GetColor() == "white") {
        newPos += a_pos[0];
        newPos += char(a_pos[1] + 1);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && !PawnObstructed(newPos, a_pieces, a_size)) {
            a_moves.push_back(newPos);

            //if the pawn hasn't been moved before, it can move 2 spaces
            if (!WasMoved()) {
                newPos = "";
                newPos += a_pos[0];
                newPos += char(a_pos[1] + 2);

                //check if the move is obstructed
                if (!PawnObstructed(newPos, a_pieces, a_size)) {
                    a_moves.push_back(newPos);
                }
            }
        }

        //check if the pawn can capture
        newPos = "";
        newPos += char(a_pos[0] + 1);
        newPos += char(a_pos[1] + 1);

        //check if the move is out of bounds
        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size, a_moves);
        }

        newPos = "";
        newPos += char(a_pos[0] - 1);
        newPos += char(a_pos[1] + 1);

        //check if the move is out of bounds
        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size, a_moves);
        }
    }
    //black pawns move down
    else if (GetColor() == "black") {
        newPos += a_pos[0];
        newPos += char(a_pos[1] - 1);

        //check if the move is out of bounds or obstructed
        if (!IsOutOfBounds(newPos) && !PawnObstructed(newPos, a_pieces, a_size)) {
            a_moves.push_back(newPos);

            //if the pawn hasn't been moved before, it can move 2 spaces
            if (!WasMoved()) {
                newPos = "";
                newPos += a_pos[0];
                newPos += char(a_pos[1] - 2);

                //check if the move is obstructed
                if (!PawnObstructed(newPos, a_pieces, a_size)) {
                    a_moves.push_back(newPos);
                }
            }
        }

        //check if the pawn can capture
        newPos = "";
        newPos += char(a_pos[0] - 1);
        newPos += char(a_pos[1] - 1);

        //check if the move is out of bounds
        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size, a_moves);
        }

        newPos = "";
        newPos += char(a_pos[0] + 1);
        newPos += char(a_pos[1] - 1);

        //check if the move is out of bounds
        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size, a_moves);
        }
    }
}
/*void Pawn::AddMoves(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Pawn::PawnObstructed()

NAME

        Pawn::PawnObstructed - checks if a specified move is blocked by a piece

SYNOPSIS

        bool Pawn::PawnObstructed(const std::string a_move, Piece* a_pieces[], const int a_size);
            a_move  --> the move to be validated
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will check if a piece is in the same location of the move, making the move obstructed.
        This function is special to the pawn because it can't capture directly in front of it.

RETURNS

        Returns true if a piece is found at the same location, false if none is found
        at the location.

*/
/**/
bool Pawn::PawnObstructed(std::string a_move, Piece* a_pieces[], const int a_size)
{
    for (int i = 0; i < 32; i++) {
        //check if another uncaptured piece shares the location with the square the piece wants to move to
        if (!a_pieces[i]->IsCaptured() && a_pieces[i]->GetOldPosition() != this->GetOldPosition() && a_move == ToChessNote(a_pieces[i]->GetOldPosition(), a_size)) {
            return true;
        }
    }
    return false;
}
/*bool Pawn::PawnObstructed(std::string a_move, Piece* a_pieces[], const int a_size)*/
