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

void Bishop::UpdateValidMoves(int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddDiagonalMoves(oldPos, a_pieces, a_size);
}

void Bishop::AddDiagonalMoves(std::string a_oldPos, Piece* a_pieces[], int a_size)
{
    std::string newPos = "";
    bool stop = false;
    int k = 1;

    //up-right
    while (!stop) {
        newPos += char(a_oldPos[0] + k);
        newPos += char(a_oldPos[1] + k);

        if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);
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
        newPos += char(a_oldPos[0] - k);
        newPos += char(a_oldPos[1] + k);

        if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);
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
        newPos += char(a_oldPos[0] + k);
        newPos += char(a_oldPos[1] - k);

        if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);
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
        newPos += char(a_oldPos[0] - k);
        newPos += char(a_oldPos[1] - k);

        if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
            m_moves.push_back(newPos);
            k++;
        }
        else {
            stop = true;
            k = 1;
        }

        newPos = "";
    }
}
