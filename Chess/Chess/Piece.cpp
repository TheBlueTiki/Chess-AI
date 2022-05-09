#include "Piece.h"

Piece::Piece()
{
    SetType("piece");
    SetTypeNum(0);
    SetColor("black");
    SetCapture(false);
    SetMoved(false);
    SetHeld(false);
    SetOldPosition(Vector2f(0, 0));
    SetNewPosition(GetSpritePosition());
}

Sprite Piece::GetSprite()
{
    return m_sprite;
}

std::string Piece::GetType()
{
    return m_type;
}

int Piece::GetTypeNum()
{
    return m_typeNum;
}

std::string Piece::GetColor()
{
    return m_color;
}

bool Piece::IsCaptured()
{
    return m_isCaptured;
}

bool Piece::WasMoved()
{
    return m_wasMoved;
}

bool Piece::IsHeld()
{
    return m_isHeld;
}

Vector2f Piece::GetOldPosition()
{
    return m_oldPosition;
}

Vector2f Piece::GetSpritePosition()
{
    return m_sprite.getPosition();
}

int Piece::GetSpriteX()
{
    return m_sprite.getPosition().x;
}

int Piece::GetSpriteY()
{
    return m_sprite.getPosition().y;
}

/**/
/*
Piece::IsCurrentlyHeld()

NAME

        Piece::IsCurrentlyHeld - checks if the piece is being held by the 
        mouse cursor

SYNOPSIS

        bool Piece::IsCurrentlyHeld(const int a_x, const int a_y);
            a_x  --> the x coordinate of the mouse's position
            a_y --> the y coordinate of the mouse's position

DESCRIPTION

        This function will check if the mouse cursor is located on the piece's
        sprite

RETURNS

        Returns true if the mouse's position is in the sprite, returns false if 
        it's not.

*/
/**/
bool Piece::IsCurrentlyHeld(const int a_x, const int a_y)
{
    if (m_sprite.getGlobalBounds().contains(a_x, a_y)) {
        return true;
    }

    return false;
}
/*bool Piece::IsCurrentlyHeld(const int a_x, const int a_y);*/

std::vector<std::string> Piece::GetValidMoves()
{
    return m_moves;
}

void Piece::SetSpriteTexture(const Texture& a_texture)
{
    m_sprite.setTexture(a_texture);
}

void Piece::SetSpritePosition(const int a_x, const int a_y)
{
    m_sprite.setPosition(a_x, a_y);
}

void Piece::SetSpriteTextureRect(const int a_left, const int a_top, const int a_width, const int a_height)
{
    m_sprite.setTextureRect(IntRect(a_left, a_top, a_width, a_height));
}

void Piece::SetSpriteScale(const double a_scale)
{
    m_sprite.setScale(a_scale, a_scale);
}

void Piece::SetType(const std::string a_type)
{
    m_type = a_type;
}

void Piece::SetTypeNum(const int a_type)
{
    m_typeNum = a_type;
}

void Piece::SetColor(const std::string a_color)
{
    m_color = a_color;
}

void Piece::SetCapture(const bool a_isCaptured)
{
    m_isCaptured = a_isCaptured;
}

void Piece::SetMoved(const bool a_wasMoved)
{
    m_wasMoved = a_wasMoved;
}

void Piece::SetHeld(const bool a_held)
{
    m_isHeld = a_held;
}

void Piece::SetOldPosition(const Vector2f a_position)
{
    m_oldPosition = a_position;
}

void Piece::SetNewPosition(const Vector2f a_position)
{
    m_newPosition = a_position;
}

void Piece::UpdateValidMoves(const int a_size, Piece* a_pieces[])
{
}

void Piece::ValidMovesAt(std::string a_pos, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
}

void Piece::ClearValidMoves()
{
    m_moves.clear();
}

/**/
/*
Piece::IsValidMove()

NAME

        Piece::IsValidMove - checks if a specified move is valid

SYNOPSIS

        bool Piece::IsValidMove(const std::string a_move);
            a_move  --> the move to be validated

DESCRIPTION

        This function will check if a specified move is valid by searching 
        through the valid move set until the end is reached or the move is
        found.

RETURNS

        Returns true if the move is found in the set of valid moves, false if
        it's not found.

*/
/**/
bool Piece::IsValidMove(const std::string a_move)
{
    if (m_moves.size() > 0) {
        for (int i = 0; i < m_moves.size(); i++) {
            if (a_move == m_moves[i]) {
                return true;
            }
        }
    }
    return false;
}
/*bool Piece::IsValidMove(const std::string a_move);*/

/**/
/*
Piece::IsOutOfBounds()

NAME

        Piece::IsOutOfBounds - checks if a specified move is out of bounds

SYNOPSIS

        bool Piece::IsOutOfBounds(const std::string a_move);
            a_move  --> the move to be validated

DESCRIPTION

        This function will check if a specified move is outside of the bounds
        of the main grid.

RETURNS

        Returns true if the move goes beyond the bounds of any side, returns
        false if the move is within the bounds

*/
/**/
bool Piece::IsOutOfBounds(const std::string a_move)
{
    //check if the move goes off the grid on any side
    if (a_move[0] < 'a' || a_move[0] > 'h' || a_move[1] < '1' || a_move[1] > '8') {
        return true;
    }

    return false;
}
/*bool Piece::IsOutOfBounds(const std::string a_move);*/

/**/
/*
Piece::IsObstructed()

NAME

        Piece::IsObstructed - checks if a specified move is blocked by a piece 

SYNOPSIS

        bool Piece::IsObstructed(const std::string a_move, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
            a_move  --> the move to be validated
            a_pieces  --> the set of all pieces on the board
            a_size  --> the size of the grid squares
            a_moves --> the list of moves being added to

DESCRIPTION

        This function will check if a piece is in the same location of the move. 
        If the move is obstructed by a piece of the opposite color, the location 
        will be added as a valid move to allow capturing.

RETURNS

        Returns true if a piece is found at the same location, false if none is found
        at the location.

*/
/**/
bool Piece::IsObstructed(const std::string a_move, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
    for (int i = 0; i < 32; i++) {
        if (!a_pieces[i]->IsCaptured() && a_pieces[i]->GetOldPosition() != this->GetOldPosition() && a_move == ToChessNote(a_pieces[i]->GetOldPosition(), a_size)) {
            //if the piece blocking the path is the opposite color, include the move to allow capturing
            if (a_pieces[i]->GetColor() != this->GetColor()) {
                a_moves.push_back(a_move);
                return true;
            }
            //if the piece blocking the path is the same color, don't include the move
            else if (a_pieces[i]->GetColor() == this->GetColor()) {
                return true;
            }
        }
    }
    return false;
}
/*bool Piece::IsObstructed(const std::string a_move, Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);*/

/**/
/*
Piece::ToChessNote()

NAME

        Piece::ToChessNote - converts position coordinates to chess notation

SYNOPSIS

        std::string Piece::ToChessNote(const Vector2f a_position, const int a_size);
            a_position  --> the position coordinates to be converted
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will accept position coordinates and turn them into their
        chess notation form through calculations

RETURNS

        Returns a string representing the specified coordinates in chess notation

*/
/**/
std::string Piece::ToChessNote(const Vector2f a_position, const int a_size)
{
    std::string s = "";

    //calculates the chess note characters based on coordinates
    s += char(a_position.x / a_size + 97);
    s += char(7 - a_position.y / a_size + 49);

    return s;
}
/*std::string Piece::ToChessNote(const Vector2f a_position, const int a_size);*/

/**/
/*
Piece::ToCoord()

NAME

        Piece::ToCoord - converts position in chess notation to coordinates

SYNOPSIS

        Vector2f Piece::ToCoord(const std::string a_position, const int a_size);
            a_position  --> the position in chess notation being converted
            a_size  --> the size of the grid squares

DESCRIPTION

        This function will accept a position in chess notation and turn them
        into coordinate form through calculations

RETURNS

        Returns the coordinates in the form of a 2d vector

*/
/**/
Vector2f Piece::ToCoord(const std::string a_position, const int a_size)
{
    int x = int(a_position[0]) - 97;
    int y = 7 - int(a_position[1]) + 49;

    return Vector2f(x * a_size, y * a_size);
}
/*Vector2f Piece::ToCoord(const std::string a_position, const int a_size);*/