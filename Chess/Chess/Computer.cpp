#include "Computer.h"

Computer::Computer()
{
}

void Computer::TakeTurn(Piece* a_pieces[], const int a_size)
{
	//generate random see for the random shuffle
	std::srand(std::time(0));

	//retrieve and shuffle all available moves
	std::vector<std::string> allMoves = GetMoves(a_pieces, a_size);
	std::random_shuffle(allMoves.begin(), allMoves.end());

	//score the moves
	std::vector<int> scores = ScoreMoves(a_pieces, a_size, allMoves);

	//complete the binary treee
	Resize(scores);

	//for the index of the best move
	int best = -1;
	
	//check if the king is threatened
	if (IsInCheck(a_pieces, a_size)) {
		best = FindDefense(a_pieces, a_size, allMoves);
	}

	//find the best move if the king isn't in check or defense can't be found
	if (best == -1) {
		auto it = std::find(scores.begin(), scores.end(), MiniMax(0, 0, true, scores, -1000, 1000));
		best = it - scores.begin();
	}

	//if the player's king is exposed, choose the move that will capture it
	for (int i = 0; i < scores.size(); i++) {
		if (scores[i] > 800) {
			best = i;
		}
	}

	//to prevent a potentially rare case where a null value makes it past minimax
	if (best > allMoves.size()) {
		best = 0;
	}

	std::cout << "Cpu: " << allMoves[best] << std::endl;

	//separate the original position and the new position from the move
	std::string at = "";
	std::string to = "";
	at += allMoves[best][0];
	at += allMoves[best][1];
	to += allMoves[best][2];
	to += allMoves[best][3];
	
	//find the piece that contains the best move
	int index = 0;
	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == at) {
			index = i;
			break;
		}
	}

	//check if the move exists
	std::vector<std::string> moves = a_pieces[index]->GetValidMoves();
	Vector2f newPos = a_pieces[index]->GetOldPosition();
	for (int j = 0; j < moves.size(); j++) {
		if (to == moves[j]) {
			newPos = a_pieces[index]->ToCoord(moves[j], a_size);
			break;
		}
	}

	//update positions
	a_pieces[index]->SetOldPosition(a_pieces[index]->GetSpritePosition());
	a_pieces[index]->SetSpritePosition(newPos.x, newPos.y);

	//update tags
	if (!a_pieces[index]->WasMoved()) {
		a_pieces[index]->SetMoved(true);
	}
	a_pieces[index]->SetHeld(true);
}

int Computer::MiniMax(int a_depth, int a_index, bool a_maxPlayer, std::vector<int> a_values, int a_alpha, int a_beta)
{
	if (a_depth == TreeDepth(a_values)) {
		return a_values[a_index];
	}

	if (a_maxPlayer) {
		int best = -1000;

		for (int i = 0; i < 2; i++) {
			int val = MiniMax(a_depth + 1, a_index * 2 + i, false, a_values, a_alpha, a_beta);

			best = std::max(best, val);
			a_alpha = std::max(a_alpha, best);

			//alpha beta pruning
			if (a_beta <= a_alpha) {
				break;
			}
		}

		return best;
	}
	else {
		int best = 1000;

		for (int i = 0; i < 2; i++) {
			int val = MiniMax(a_depth + 1, a_index * 2 + i, true, a_values, a_alpha, a_beta);
			
			best = std::min(best, val);
			a_beta = std::min(a_beta, best);

			//alpha beta pruning
			if (a_beta <= a_alpha) {
				break;
			}
		}

		return best;
	}
}

int Computer::FindDefense(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
	int kingIndex;
	int threatIndex;
	int best = -1;

	//find the king
	for (int i = 0; i < 16; i++) {
		if (a_pieces[i]->GetType() == "king") {
			kingIndex = i;
		}
	}

	std::vector<std::string> pieceMoves;

	//find the piece that can capture the king
	for (int i = 16; i < 32; i++) {
		pieceMoves.clear();
		pieceMoves = a_pieces[i]->GetValidMoves();

		//check all moves
		for (int j = 0; j < pieceMoves.size(); j++) {
			//check if a move can capture the king
			if (pieceMoves[j] == a_pieces[kingIndex]->ToChessNote(a_pieces[kingIndex]->GetOldPosition(), a_size)) {
				threatIndex = i;
			}
		}
	}

	std::string to;
	std::string from;
	int bestScore = -10000;
	int score;

	//check if any pieces can capture the piece threatening the king
	for (int i = 0; i < a_moves.size(); i++) {
		to = "";
		to += a_moves[i][2];
		to += a_moves[i][3];
		
		if (a_pieces[threatIndex]->ToChessNote(a_pieces[threatIndex]->GetOldPosition(), a_size) == to) {
			score = GetScore(a_pieces, a_size, a_moves[i]);
			if (score > bestScore) {
				bestScore = score;
				best = i;
			}
		}
	}

	//check if a piece can block the threat
	if (best == -1) {
		best = ProtectKing(a_pieces, a_size, a_moves, threatIndex, kingIndex);
	}
	
	return best;
}

int Computer::ProtectKing(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, int a_threat, int a_king)
{
	int best = -1;
	int bestScore = -10000;
	int score;
	std::string to;
	std::string from;
	std::string threatPos = a_pieces[a_threat]->ToChessNote(a_pieces[a_threat]->GetOldPosition(), a_size);
	std::string kingPos = a_pieces[a_king]->ToChessNote(a_pieces[a_king]->GetOldPosition(), a_size);

	//check if a piece can block the threat
	if (a_pieces[a_threat]->GetType() != "knight") {
		std::vector<std::string> threatPath;

		//get the threat's path to the king
		threatPath = GetThreatPath(kingPos, threatPos);

		//find a move that will block the threat's path
		for (int i = 0; i < a_moves.size(); i++) {
			to = "";
			to += a_moves[i][2];
			to += a_moves[i][3];
			from = "";
			from += a_moves[i][0];
			from += a_moves[i][1];

			//search through the threat's path
			for (int j = 0; j < threatPath.size(); j++) {
				if (to == threatPath[j] && from != kingPos) {
					score = GetScore(a_pieces, a_size, a_moves[i]);

					//score the options to make the best decision
					if (score > bestScore) {
						bestScore = score;
						best = i;
					}
				}
			}
		}

		//if no pieces can block the threat, move away from it
		if (best == -1) {
			bool safe;
			for (int i = 0; i < a_moves.size(); i++) {
				safe = true;
				to = "";
				to += a_moves[i][2];
				to += a_moves[i][3];
				from = "";
				from += a_moves[i][0];
				from += a_moves[i][1];

				//only inspect the king's moves
				if (from == kingPos) {
					//check if the move is in the threat's path
					for (int j = 0; j < threatPath.size(); j++) {
						if (to == threatPath[j]) {
							safe = false;
						}
					}
				}
				else {
					safe = false;
				}

				//check if the move is out of the threat's path
				if (safe) {
					//score the moves to get the best one
					score = GetScore(a_pieces, a_size, a_moves[i]);
					if (score > bestScore) {
						bestScore = score;
						best = i;
					}
				}
			}
		}
	}
	//if the threat is a knight, move the king out of the way
	else if (a_pieces[a_threat]->GetType() == "knight") {
		for (int i = 0; i < a_moves.size(); i++) {
			from = "";
			from += a_moves[i][0];
			from += a_moves[i][1];

			if (from == kingPos) {
				score = GetScore(a_pieces, a_size, a_moves[i]);
				if (score > bestScore) {
					bestScore = score;
					best = i;
				}
			}
		}
	}

	return best;
}

std::vector<std::string> Computer::GetMoves(Piece* a_pieces[], const int a_size)
{
	std::vector<std::string> allMoves;
	std::vector<std::string> moves;
	std::string m;


	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured()) {
			moves = a_pieces[i]->GetValidMoves();

			for (int j = 0; j < moves.size(); j++) {
				m = "";
				m += a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size);
				m += moves[j];

				allMoves.push_back(m);
			}
		}
	}

	return allMoves;
}

std::vector<std::string> Computer::GetThreatPath(std::string a_pos1, std::string a_pos2)
{
	std::vector<std::string> path;

	//threat from the right
	if (a_pos1[0] < a_pos2[0] && a_pos1[1] == a_pos2[1]) {
		path = StraightThreatPath(a_pos1, a_pos2, 1);
	}
	//threat from the bottom right
	else if (a_pos1[0] < a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		path = DiagonalThreatPath(a_pos1, a_pos2, 1);
	}
	//threat from below
	else if (a_pos1[0] == a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		path = StraightThreatPath(a_pos1, a_pos2, 2);
	}
	//threat from the bottom left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		path = DiagonalThreatPath(a_pos1, a_pos2, 2);
	}
	//threat from the left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] == a_pos2[1]) {
		path = StraightThreatPath(a_pos1, a_pos2, 3);
	}
	//threat from the top left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		path = DiagonalThreatPath(a_pos1, a_pos2, 3);
	}
	//threat from above
	else if (a_pos1[0] == a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		path = StraightThreatPath(a_pos1, a_pos2, 4);
	}
	//threat from the top right
	else if (a_pos1[0] < a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		path = DiagonalThreatPath(a_pos1, a_pos2, 4);
	}

	return path;
}

std::vector<std::string> Computer::StraightThreatPath(std::string a_pos1, std::string a_pos2, int a_direction)
{
	std::vector<std::string> path;
	std::string newPos = "";
	bool stop = false;
	int k = 1;

	switch (a_direction) {
	//right
	case 1:
		while (!stop) {
			newPos += char(a_pos1[0] + k);
			newPos += a_pos1[1];

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//down
	case 2:
		while (!stop) {
			newPos += a_pos1[0];
			newPos += char(a_pos1[1] - k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//left
	case 3:
		while (!stop) {
			newPos += char(a_pos1[0] - k);
			newPos += a_pos1[1];

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//up
	case 4:
		while (!stop) {
			newPos += a_pos1[0];
			newPos += char(a_pos1[1] + k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	}

	return path;
}

std::vector<std::string> Computer::DiagonalThreatPath(std::string a_pos1, std::string a_pos2, int a_direction)
{
	std::vector<std::string> path;
	std::string newPos = "";
	bool stop = false;
	int k = 1;

	switch (a_direction) {
	//bottom-right
	case 1:
		while (!stop) {
			newPos += char(a_pos1[0] + k);
			newPos += char(a_pos1[1] - k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//bottom-left
	case 2:
		while (!stop) {
			newPos += char(a_pos1[0] - k);
			newPos += char(a_pos1[1] - k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//up-left
	case 3:
		while (!stop) {
			newPos += char(a_pos1[0] - k);
			newPos += char(a_pos1[1] + k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	//up-right
	case 4:
		while (!stop) {
			newPos += char(a_pos1[0] + k);
			newPos += char(a_pos1[1] + k);

			if (newPos == a_pos2) {
				stop = true;
			}
			else {
				path.push_back(newPos);
				k++;
				newPos = "";
			}
		}
		break;
	}

	return path;
}

std::vector<int> Computer::ScoreMoves(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)
{
	std::vector<int> scores;
	std::string to;

	for (int i = 0; i < a_moves.size(); i++) {
		scores.push_back(GetScore(a_pieces, a_size, a_moves[i]));
	}

	return scores;
}

bool Computer::IsInCheck(Piece* a_pieces[], const int a_size)
{
	int kingIndex;

	//find the king
	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->GetType() == "king") {
			kingIndex = i;
		}
	}

	std::vector<std::string> moves;

	//check if any pieces can capture the king
	for (int i = 16; i < 32; i++) {
		//skip captured pieces
		if (a_pieces[i]->IsCaptured()) {
			continue;
		}

		//get the next set of moves
		moves.clear();
		moves = a_pieces[i]->GetValidMoves();

		//check all moves
		for (int j = 0; j < moves.size(); j++) {
			//check if a move can capture the king
			if (moves[j] == a_pieces[kingIndex]->ToChessNote(a_pieces[kingIndex]->GetOldPosition(), a_size)) {
				return true;
			}
		}
	}

	return false;
}

int Computer::GetScore(Piece* a_pieces[], const int a_size, const std::string a_move)
{
	int score = 0;
	int n = 0;
	std::string from = "";
	std::string to = "";

	from += a_move[0];
	from += a_move[1];
	to += a_move[2];
	to += a_move[3];

	//find the piece making the move
	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == from) {
			n = i;
		}
	}

	//check if the move can capture a piece
	for (int i = 16; i < 32; i++) {
		//find the typing of the piece that can be captured
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == to) {
			score += GetPieceValue(a_pieces[i]->GetTypeNum());
		}
	}

	std::vector<std::string> opMoves;

	//check for disadvantages
	for (int i = 16; i < 32; i++) {
		//skip captured pieces
		if (a_pieces[i]->IsCaptured()) {
			continue;
		}

		opMoves.clear();
		opMoves = a_pieces[i]->GetValidMoves();

		//check if a move will leave the peace open for capture
		for (int j = 0; j < opMoves.size(); j++) {
			if (to == opMoves[j]) {
				score -= GetPieceValue(a_pieces[n]->GetTypeNum());
			}
		}
	}

	//no need to look into moves that will win the game
	if (score < 800 && score > -800) {
		score += ScorePotential(a_pieces, a_size, from, to);
	}

	//moves that will lose the game should be equally bad
	if (score < -800) {
		score = -800;
	}

	return score;
}

int Computer::GetPieceValue(const int a_typeNum)
{
	switch (a_typeNum) {
	case 1:
		return 50;
	case 2:
		return 30;
	case 3:
		return 30;
	case 4:
		return 90;
	case 5:
		return 900;
	case 6:
		return 10;
	}

	return 0;
}

int Computer::ScorePotential(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to)
{
	int score = 0;
	int n = 0;
	std::vector<std::string> moves;

	//find the piece making the move
	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == a_from) {
			//get the moves that could be mad at the position of the move
			n = i;
			a_pieces[i]->ValidMovesAt(a_to, a_pieces, a_size, moves);
		}
	}
	
	//check for pieces that could be captured from the future moves
	for (int i = 16; i < 32; i++) {
		for (int j = 0; j < moves.size(); j++) {
			if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == moves[j]) {
				score += GetPieceValue(a_pieces[i]->GetTypeNum());
			}
		}
	}

	std::vector<std::string> opMoves;

	//check for moves that could set the piece up for capture
	for (int i = 16; i < 32; i++) {
		//skip captured pieces
		if (a_pieces[i]->IsCaptured()) {
			continue;
		}

		//get the valid moves of opposing pieces
		opMoves.clear();
		opMoves = a_pieces[i]->GetValidMoves();

		//check for capture situations
		for (int j = 0; j < opMoves.size(); j++) {
			for (int k = 0; k < moves.size(); k++) {
				if (opMoves[j] == moves[k]) {
					score -= GetPieceValue(a_pieces[n]->GetTypeNum());
				}
			}
		}
	}

	return score / 2;
}

void Computer::Resize(std::vector<int>& a_values)
{
	int x = 0;
	while (a_values.size() / (int)std::pow(2, x) >= 1) {
		x++;
	}

	while (a_values.size() < (int)std::pow(2, x)) {
		a_values.push_back(-10000);
	}
}

int Computer::TreeDepth(std::vector<int>& a_values)
{
	int depth = 0;

	while (a_values.size() / (int)std::pow(2, depth) > 1) {
		depth++;
	}

	return depth;
}
