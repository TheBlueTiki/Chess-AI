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
    AddDiagonalMoves(oldPos, a_pieces, a_size, m_moves);
    AddStraightMoves(oldPos, a_pieces, a_size, m_moves);
}

void King::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddDiagonalMoves(a_pos, a_pieces, a_size, a_moves);
    AddStraightMoves(a_pos, a_pieces, a_size, a_moves);
}

void King::AddDiagonalMoves(std::string a_pos, Piece* a_pieces[], int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //up-right
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] + 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //up-left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] + 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //bottom-right
    newPos = "";
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] - 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //bottom-left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] - 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}

void King::AddStraightMoves(std::string a_pos, Piece* a_pieces[], int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //right
    newPos += char(a_pos[0] + 1);
    newPos += a_pos[1];
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //left
    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += a_pos[1];
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //up
    newPos = "";
    newPos += a_pos[0];
    newPos += char(a_pos[1] + 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //down
    newPos = "";
    newPos += a_pos[0];
    newPos += char(a_pos[1] - 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}

