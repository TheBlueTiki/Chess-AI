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

void King::UpdateValidMoves(int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddDiagonalMoves(oldPos, a_pieces, a_size);
    AddStraightMoves(oldPos, a_pieces, a_size);
}

void King::AddDiagonalMoves(std::string a_oldPos, Piece* a_pieces[], int a_size)
{
    std::string newPos = "";

    //up-right
    newPos += char(a_oldPos[0] + 1);
    newPos += char(a_oldPos[1] + 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //up-left
    newPos = "";
    newPos += char(a_oldPos[0] - 1);
    newPos += char(a_oldPos[1] + 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //bottom-right
    newPos = "";
    newPos += char(a_oldPos[0] + 1);
    newPos += char(a_oldPos[1] - 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //bottom-left
    newPos = "";
    newPos += char(a_oldPos[0] - 1);
    newPos += char(a_oldPos[1] - 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }
}

void King::AddStraightMoves(std::string a_oldPos, Piece* a_pieces[], int a_size)
{
    std::string newPos = "";

    //right
    newPos += char(a_oldPos[0] + 1);
    newPos += a_oldPos[1];
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //left
    newPos = "";
    newPos += char(a_oldPos[0] - 1);
    newPos += a_oldPos[1];
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //up
    newPos = "";
    newPos += a_oldPos[0];
    newPos += char(a_oldPos[1] + 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }

    //down
    newPos = "";
    newPos += a_oldPos[0];
    newPos += char(a_oldPos[1] - 1);
    if (!IsOutOfBounds(newPos) && !IsObstructed(newPos, a_pieces, a_size)) {
        m_moves.push_back(newPos);
    }
}

