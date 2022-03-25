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

void Pawn::UpdateValidMoves(int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());
    
    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddMoves(oldPos, a_pieces, a_size);
}

void Pawn::AddMoves(std::string a_oldPos, Piece* a_pieces[], int a_size)
{
    std::string newPos = "";

    //white pawns move up
    if (GetColor() == "white") {
        newPos += a_oldPos[0];
        newPos += char(a_oldPos[1] + 1);

        //prevent the pawn from moving off the screen
        if (!IsOutOfBounds(newPos) && !PawnObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);

            //if the pawn hasn't been moved before, it can move 2 spaces
            if (!WasMoved()) {
                newPos = "";
                newPos += a_oldPos[0];
                newPos += char(a_oldPos[1] + 2);

                if (!PawnObstructed(newPos, a_pieces, a_size)) {
                    m_moves.push_back(newPos);
                }
            }
        }

        //check if the pawn can capture
        newPos = "";
        newPos += char(a_oldPos[0] + 1);
        newPos += char(a_oldPos[1] + 1);

        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size);
        }

        newPos = "";
        newPos += char(a_oldPos[0] - 1);
        newPos += char(a_oldPos[1] + 1);

        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size);
        }
    }
    //black pawns move down
    else if (GetColor() == "black") {
        newPos += a_oldPos[0];
        newPos += char(a_oldPos[1] - 1);

        //prevent the pawn from moving off the screen
        if (!IsOutOfBounds(newPos) && !PawnObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);

            //if the pawn hasn't been moved before, it can move 2 spaces
            if (!WasMoved()) {
                newPos = "";
                newPos += a_oldPos[0];
                newPos += char(a_oldPos[1] - 2);

                if (!PawnObstructed(newPos, a_pieces, a_size)) {
                    m_moves.push_back(newPos);
                }
            }
        }

        //check if the pawn can capture
        newPos = "";
        newPos += char(a_oldPos[0] - 1);
        newPos += char(a_oldPos[1] - 1);

        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size);
        }

        newPos = "";
        newPos += char(a_oldPos[0] + 1);
        newPos += char(a_oldPos[1] - 1);

        if (!IsOutOfBounds(newPos)) {
            IsObstructed(newPos, a_pieces, a_size);
        }
    }
}

//special obstruction check for pawns because they can't capture directly in front of them
bool Pawn::PawnObstructed(std::string a_move, Piece* a_pieces[], int a_size)
{
    for (int i = 0; i < 32; i++) {
        //check if another uncaptured piece shares the location with the square the piece wants to move to
        if (!a_pieces[i]->IsCaptured() && a_pieces[i]->GetOldPosition() != this->GetOldPosition() && a_move == ToChessNote(a_pieces[i]->GetOldPosition(), a_size)) {
            return true;
        }
    }
    return false;
}
