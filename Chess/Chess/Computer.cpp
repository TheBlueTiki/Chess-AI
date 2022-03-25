#include "Computer.h"

Computer::Computer()
{
}

void Computer::TakeTurn(Piece* a_pieces[], const int a_size)
{
	srand(time(NULL));
	int i = rand() % 16;
	std::vector<std::string> moves = a_pieces[i]->GetValidMoves();

	//look for an uncaptured black piece with movement options
	while (a_pieces[i]->IsCaptured() || a_pieces[i]->GetColor() != "black" || moves.empty()) {
		i = rand() % 16;
		moves = a_pieces[i]->GetValidMoves();
	}

	int j = rand() % moves.size();
	Vector2f pos = a_pieces[i]->ToCoord(moves[j], a_size);

	//update positions
	a_pieces[i]->SetOldPosition(a_pieces[i]->GetSpritePosition());
	a_pieces[i]->SetSpritePosition(pos.x, pos.y);
	//a_pieces[i]->SetNewPosition(a_pieces[i]->GetSpritePosition());

	//update tags
	if (!a_pieces[i]->WasMoved()) {
		a_pieces[i]->SetMoved(true);
	}
	a_pieces[i]->SetHeld(true);
}
