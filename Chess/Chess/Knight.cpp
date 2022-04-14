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

void Knight::UpdateValidMoves(int a_size, Piece* a_pieces[])
{
    //update the old position
    SetOldPosition(GetSpritePosition());

    //clear the list of valid moves
    ClearValidMoves();

    //find valid moves
    std::string oldPos = ToChessNote(GetOldPosition(), a_size);
    AddMoves(oldPos, a_pieces, a_size, m_moves);
}

void Knight::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    AddMoves(a_pos, a_pieces, a_size, a_moves);
}

void Knight::AddMoves(std::string a_pos, Piece* a_pieces[], int a_size, std::vector<std::string>& a_moves)
{
    std::string newPos = "";

    //tall 'L' formations
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] + 2);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] + 1);
    newPos += char(a_pos[1] - 2);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] + 2);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 1);
    newPos += char(a_pos[1] - 2);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    //short 'L' formations
    newPos = "";
    newPos += char(a_pos[0] + 2);
    newPos += char(a_pos[1] + 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] + 2);
    newPos += char(a_pos[1] - 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }

    newPos = "";
    newPos += char(a_pos[0] - 2);
    newPos += char(a_pos[1] + 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
    newPos = "";
    newPos += char(a_pos[0] - 2);
    newPos += char(a_pos[1] - 1);
    if (!IsOutOfBounds(newPos) && (!IsObstructed(newPos, a_pieces, a_size, a_moves) || newPos == ToChessNote(GetOldPosition(), a_size))) {
        a_moves.push_back(newPos);
    }
}
