#include "Computer.h"

Computer::Computer()
{
}

/**/
/*
Computer::TakeTurn()

NAME

		Computer::TakeTurn - lets the computer make a move

SYNOPSIS

		void Computer::TakeTurn(Piece* a_pieces[], const int a_size);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares

DESCRIPTION

		This function will gather every move that can be made in the current turn, score each option, then choose 
		the best move.

RETURNS

		void

*/
/**/
void Computer::TakeTurn(Piece* a_pieces[], const int a_size)
{
	//generate random see for the random shuffle
	std::srand(std::time(0));

	//retrieve and shuffle all available moves
	std::vector<std::string> allMoves = GetMoves(a_pieces, a_size);
	std::random_shuffle(allMoves.begin(), allMoves.end());

	//score the moves
	std::vector<int> scores = ScoreMoves(a_pieces, a_size, allMoves, true);

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
/*void Computer::TakeTurn(Piece* a_pieces[], const int a_size)*/

/**/
/*
Computer::MiniMax()

NAME

		Computer::MiniMax - chooses the best score in a list, taking competition into account

SYNOPSIS

		int Computer::MiniMax(int a_depth, int a_index, bool a_maxPlayer, std::vector<int> a_values, int a_alpha, int a_beta);
			a_depth  --> the depth level of the tree the algorithm is on
			a_index  --> the index of the best value in the list
			a_maxPlayer	 --> represents whether the algorithm was called by a maximizing player or minimizing player
			a_values  --> the set of integers that holds all the move scores
			a_alpha  --> best high-level decision used for pruning
			a_beta --> best low-level decision used for pruning

DESCRIPTION

		This function will look through every move's score and chose the best move to make assuming 
		the human player is playing optimally.

RETURNS

		An integer representing the best move to make based on the score.

*/
/**/
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
/*int Computer::MiniMax(int a_depth, int a_index, bool a_maxPlayer, std::vector<int> a_values, int a_alpha, int a_beta)*/

/**/
/*
Computer::FindDefense()

NAME

		Computer::FindDefense - chooses the best move to defend the king

SYNOPSIS

		int Computer::FindDefense(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_moves	 --> the set of all available moves

DESCRIPTION

		This function will look through every move and try to find a way to protect the king in a check 
		situation.

RETURNS

		An integer representing the position of the best move in the list

*/
/**/
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
			score = GetScore(a_pieces, a_size, a_moves[i], false);
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
/*int Computer::FindDefense(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves)*/

/**/
/*
Computer::ProtectKing()

NAME

		Computer::ProtectKing - chooses the best move for the king to avoid capture

SYNOPSIS

		int Computer::ProtectKing(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, int a_threat, int a_king);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_moves	 --> the set of all available moves
			a_threat  --> the position of the threatening piece in the list of pieces
			a_king  --> the position of the king in the list of pieces

DESCRIPTION

		This function will look through every move and try to find pieces to block the threat or 
		find an escape route for the king to get out of a check situation.

RETURNS

		An integer representing the position of the best move in the list

*/
/**/
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
		threatPath = GetThreatPath(kingPos, threatPos, false);

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
					score = GetScore(a_pieces, a_size, a_moves[i], false);

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

			//regenerate the threat's path to go past the king 
			threatPath.clear();
			threatPath = GetThreatPath(kingPos, threatPos, true);

			//inspect all moves
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
					score = GetCaptureScore(a_pieces, a_size, from, to, a_king);
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
			to = "";
			to += a_moves[i][2];
			to += a_moves[i][3];

			if (from == kingPos) {
				score = GetCaptureScore(a_pieces, a_size, from, to, a_king);
				if (score > bestScore) {
					bestScore = score;
					best = i;
				}
			}
		}
	}

	return best;
}
/*int Computer::ProtectKing(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, int a_threat, int a_king)*/

/**/
/*
Computer::GetMoves()

NAME

		Computer::GetMoves - finds all available moves that can be made in the current turn

SYNOPSIS

		std::vector<std::string> Computer::GetMoves(Piece* a_pieces[], const int a_size);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares

DESCRIPTION

		This function will gather all of the black pieces' valid moves into a single list.

RETURNS

		A string list representing all the moves that can be made in the current turn

*/
/**/
std::vector<std::string> Computer::GetMoves(Piece* a_pieces[], const int a_size)
{
	std::vector<std::string> allMoves;
	std::vector<std::string> moves;
	std::string m;

	//inspect eveery black piece
	for (int i = 0; i < 16; i++) {
		if (!a_pieces[i]->IsCaptured()) {
			//get the piece's valid moves
			moves = a_pieces[i]->GetValidMoves();

			//combine the piece's old position with the valid move and add it to the list
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
/*std::vector<std::string> Computer::GetMoves(Piece* a_pieces[], const int a_size)*/

/**/
/*
Computer::GetThreatPath()

NAME

		Computer::GetThreatPath - generates the path a threatening piece would take to capture another piece

SYNOPSIS

		std::vector<std::string> Computer::GetThreatPath(std::string a_pos1, std::string a_pos2, bool a_ignore);
			a_pos1  --> the position in chess notation of the piece in danger
			a_pos2  --> the position in chess notation of the threatening piece
			a_ignore  --> whether or not the position of the piece in danger needs to be ignored when generating 
						  the path

DESCRIPTION

		This function will generate all the spaces in a path that a threatening piece would have to take to
		capture the other piece.

RETURNS

		A string list representing the path of the threatening piece.

*/
/**/
std::vector<std::string> Computer::GetThreatPath(std::string a_pos1, std::string a_pos2, bool a_ignore)
{
	std::vector<std::string> path;

	//threat from the right
	if (a_pos1[0] < a_pos2[0] && a_pos1[1] == a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = StraightThreatPathIgnore(a_pos1, a_pos2, 1);
		}
		else {
			path = StraightThreatPath(a_pos1, a_pos2, 1);
		}
	}
	//threat from the bottom right
	else if (a_pos1[0] < a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = DiagonalThreatPathIgnore(a_pos1, a_pos2, 1);
		}
		else {
			path = DiagonalThreatPath(a_pos1, a_pos2, 1);
		}
	}
	//threat from below
	else if (a_pos1[0] == a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = StraightThreatPathIgnore(a_pos1, a_pos2, 2);
		}
		else {
			path = StraightThreatPath(a_pos1, a_pos2, 2);
		}
	}
	//threat from the bottom left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] > a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = DiagonalThreatPathIgnore(a_pos1, a_pos2, 2);
		}
		else {
			path = DiagonalThreatPath(a_pos1, a_pos2, 2);
		}
	}
	//threat from the left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] == a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = StraightThreatPathIgnore(a_pos1, a_pos2, 3);
		}
		else {
			path = StraightThreatPath(a_pos1, a_pos2, 3);
		}
	}
	//threat from the top left
	else if (a_pos1[0] > a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = DiagonalThreatPathIgnore(a_pos1, a_pos2, 3);
		}
		else {
			path = DiagonalThreatPath(a_pos1, a_pos2, 3);
		}
	}
	//threat from above
	else if (a_pos1[0] == a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = StraightThreatPathIgnore(a_pos1, a_pos2, 4);
		}
		else {
			path = StraightThreatPath(a_pos1, a_pos2, 4);
		}
	}
	//threat from the top right
	else if (a_pos1[0] < a_pos2[0] && a_pos1[1] < a_pos2[1]) {
		//check if the endangered piece is to be ignored in generating
		if (a_ignore) {
			path = DiagonalThreatPathIgnore(a_pos1, a_pos2, 4);
		}
		else {
			path = DiagonalThreatPath(a_pos1, a_pos2, 4);
		}
	}

	return path;
}

/**/
/*
Computer::StraightThreatPath()

NAME

		Computer::StraightThreatPath - generates the path a threatening piece in a straight direction

SYNOPSIS

		std::vector<std::string> Computer::StraightThreatPath(std::string a_pos1, std::string a_pos2, int a_direction);
			a_pos1  --> the position in chess notation of the piece in danger
			a_pos2  --> the position in chess notation of the threatening piece
			a_direction  --> the number of the direction of where the threat is at

DESCRIPTION

		This function will generate all the spaces in a path that a threatening piece in a straight direction would 
		have to take to capture the other piece.

RETURNS

		A string list representing the path of the threatening piece.

*/
/**/
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
/*std::vector<std::string> Computer::StraightThreatPath(std::string a_pos1, std::string a_pos2, int a_direction)*/

/**/
/*
Computer::DiagonalThreatPath()

NAME

		Computer::DiagonalThreatPath - generates the path a threatening piece in a diagonal direction

SYNOPSIS

		std::vector<std::string> Computer::DiagonalThreatPath(std::string a_pos1, std::string a_pos2, int a_direction);
			a_pos1  --> the position in chess notation of the piece in danger
			a_pos2  --> the position in chess notation of the threatening piece
			a_direction  --> the number of the direction of where the threat is at

DESCRIPTION

		This function will generate all the spaces in a path that a threatening piece in a diagonal direction would
		have to take to capture the other piece.

RETURNS

		A string list representing the path of the threatening piece.

*/
/**/
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
/*std::vector<std::string> Computer::DiagonalThreatPath(std::string a_pos1, std::string a_pos2, int a_direction)*/

/**/
/*
Computer::StraightThreatPathIgnore()

NAME

		Computer::StraightThreatPathIgnore - generates the path a threatening piece in a straight direction ignoring the threatened piece

SYNOPSIS

		std::vector<std::string> Computer::StraightThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction);
			a_pos1  --> the position in chess notation of the piece in danger
			a_pos2  --> the position in chess notation of the threatening piece
			a_direction  --> the number of the direction of where the threat is at

DESCRIPTION

		This function will generate all the spaces in a path that a threatening piece in a straight direction would
		have to take to capture the other piece, and the spaces beyond the threatened piece.

RETURNS

		A string list representing the path of the threatening piece.

*/
/**/
std::vector<std::string> Computer::StraightThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction)
{
	std::vector<std::string> path;
	std::string newPos = "";
	bool stop = false;
	int k = 1;

	switch (a_direction) {
		//right
	case 1:
		while (!stop) {
			newPos += char(a_pos2[0] - k);
			newPos += a_pos2[1];

			if (IsOutOfBounds(newPos)) {
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
			newPos += a_pos2[0];
			newPos += char(a_pos2[1] + k);

			if (IsOutOfBounds(newPos)) {
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
			newPos += char(a_pos2[0] + k);
			newPos += a_pos2[1];

			if (IsOutOfBounds(newPos)) {
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
			newPos += a_pos2[0];
			newPos += char(a_pos2[1] - k);

			if (IsOutOfBounds(newPos)) {
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
/*std::vector<std::string> Computer::StraightThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction)*/

/**/
/*
Computer::DiagonalThreatPathIgnore()

NAME

		Computer::DiagonalThreatPathIgnore - generates the path a threatening piece in a diagonal direction ignoring the threatened piece

SYNOPSIS

		std::vector<std::string> Computer::DiagonalThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction);
			a_pos1  --> the position in chess notation of the piece in danger
			a_pos2  --> the position in chess notation of the threatening piece
			a_direction  --> the number of the direction of where the threat is at

DESCRIPTION

		This function will generate all the spaces in a path that a threatening piece in a diagonal direction would
		have to take to capture the other piece, and the spaces beyond the threatened piece.

RETURNS

		A string list representing the path of the threatening piece.

*/
/**/
std::vector<std::string> Computer::DiagonalThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction)
{
	std::vector<std::string> path;
	std::string newPos = "";
	bool stop = false;
	int k = 1;

	switch (a_direction) {
		//bottom-right
	case 1:
		while (!stop) {
			newPos += char(a_pos2[0] - k);
			newPos += char(a_pos2[1] + k);

			if (IsOutOfBounds(newPos)) {
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
			newPos += char(a_pos2[0] + k);
			newPos += char(a_pos2[1] + k);

			if (IsOutOfBounds(newPos)) {
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
			newPos += char(a_pos2[0] + k);
			newPos += char(a_pos2[1] - k);

			if (IsOutOfBounds(newPos)) {
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
			newPos += char(a_pos2[0] - k);
			newPos += char(a_pos2[1] - k);

			if (IsOutOfBounds(newPos)) {
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
/*std::vector<std::string> Computer::DiagonalThreatPathIgnore(std::string a_pos1, std::string a_pos2, int a_direction)*/

/**/
/*
Computer::ScoreMoves()

NAME

		Computer::ScoreMoves - assigns a score to every move in the list

SYNOPSIS

		std::vector<int> Computer::ScoreMoves(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, bool a_lookAhead);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_moves	 --> the set of all available moves
			a_lookAhead  --> whether or not to look one move ahead

DESCRIPTION

		This function will look through all moves and score them based on different factors that would affect how
		beneficial a move is.

RETURNS

		An integer list representing the scores of all of the moves

*/
/**/
std::vector<int> Computer::ScoreMoves(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, bool a_lookAhead)
{
	std::vector<int> scores;
	std::string to;

	for (int i = 0; i < a_moves.size(); i++) {
		scores.push_back(GetScore(a_pieces, a_size, a_moves[i], a_lookAhead));
	}

	return scores;
}
/*std::vector<int> Computer::ScoreMoves(Piece* a_pieces[], const int a_size, std::vector<std::string>& a_moves, int a_level)*/

/**/
/*
Computer::GetScore()

NAME

		Computer::GetScore - assigns a score to a move

SYNOPSIS

		int Computer::GetScore(Piece* a_pieces[], const int a_size, const std::string a_move, bool a_lookAhead);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_move	 --> the move in chess notation being scored
			a_lookAhead  --> whether or not to look one move ahead

DESCRIPTION

		This function will inspect a moves and score it based on different factors that would affect how
		beneficial it is. It first evaluates immediate advantages and disadvantages like captures and trades,
		and then it evaluates how good the move is defensively, and last it scores it's potential to set up
		for something next turn.

RETURNS

		An integer representing the score of the move.

*/
/**/
int Computer::GetScore(Piece* a_pieces[], const int a_size, const std::string a_move, bool a_lookAhead)
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
	
	//check if the move has any immediate advantages or disadvantages
	score += GetCaptureScore(a_pieces, a_size, from, to, n);

	//if the move will win or lose the game, no need to score farther
	if (score < 800 || score < -800) {
		//check if the move will leave any pieces unprotected
		score += GetDefenseScore(a_pieces, a_size, from, to);

		//check if looking a move ahead is necessary
		if (a_lookAhead) {
			score += ScorePotential(a_pieces, a_size, from, to);
		}
	}
	
	//moves that will lose the game should be equally bad
	if (score < -800) {
		score = -900;
	}

	return score;
}
/*int Computer::GetScore(Piece* a_pieces[], const int a_size, const std::string a_move, int a_level)*/

/**/
/*
Computer::GetCaptureScore()

NAME

		Computer::GetCaptureScore - calculates the score of a move based on what it can do this turn

SYNOPSIS

		int Computer::GetCaptureScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to, int a_piecePos);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_from	 --> the starting position of the move
			a_to  --> the ending position of the move
			a_piecePos  --> the position of the moving piece in the list of pieces

DESCRIPTION

		This function will assign a score to a move based on what it can capture and if it opens up the piece to be captured.

RETURNS

		An integer representing the score of the move.

*/
/**/
int Computer::GetCaptureScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to, int a_piecePos)
{
	int score = 0;

	//check if the move can capture a piece
	for (int i = 16; i < 32; i++) {
		//find the typing of the piece that can be captured
		if (!a_pieces[i]->IsCaptured() && a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size) == a_to) {
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
			if (a_to == opMoves[j]) {
				score -= GetPieceValue(a_pieces[a_piecePos]->GetTypeNum());
			}
		}
	}

	return score;
}
/*int Computer::GetImmediateScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to)*/

/**/
/*
Computer::ScorePotential()

NAME

		Computer::ScorePotential - calculates the score of a move based on what it can do next turn

SYNOPSIS

		int Computer::ScorePotential(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_from	 --> the starting position of the move
			a_to  --> the ending position of the move

DESCRIPTION

		This function will assign a score to a move based on that advantages and disadvantages it will have after the move.

RETURNS

		An integer representing the score of the move.

*/
/**/
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

	return score;
}
/*int Computer::ScorePotential(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to)*/

/**/
/*
Computer::GetDefenseScore()

NAME

		Computer::GetDefenseScore - calculates the score of a move based on what it exposes for capture

SYNOPSIS

		int Computer::GetDefenseScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares
			a_from	 --> the starting position of the move
			a_to  --> the ending position of the move

DESCRIPTION

		This function will assign a score to a move based on what pieces it leave open for capture after moving .

RETURNS

		An integer representing the score of the move.

*/
/**/
int Computer::GetDefenseScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to)
{
	int score = 0;
	std::vector<std::string> opMoves, threatPath;

	for (int i = 16; i < 32; i++) {
		//skip captured pieces, knights, and pawns; knights and pawns can't be blocked like other pieces
		if (a_pieces[i]->IsCaptured() || a_pieces[i]->GetType() == "knight" || a_pieces[i]->GetType() == "pawn") {
			continue;
		}

		opMoves.clear();
		threatPath.clear();

		//get the opposing piece's moves
		opMoves = a_pieces[i]->GetValidMoves();

		//check if a piece is threatening the moving piece
		for (int j = 0; j < opMoves.size(); j++) {
			//get the threat's path
			if (opMoves[j] == a_from) {
				threatPath = GetThreatPath(a_from, a_pieces[i]->ToChessNote(a_pieces[i]->GetOldPosition(), a_size), true);
			}
		}

		//if a threat was found, check for pieces being protected by the moving piece
		if (!threatPath.empty()) {

			for (int j = 0; j < threatPath.size(); j++) {
				//if the intended move is in the threat's path, it's safe to assume it will still be defending when the move is made
				if (threatPath[j] == a_to) {
					j = threatPath.size();
				}
				//skip the position of the piece making the move
				else if (threatPath[j] != a_from) {
					//check for pieces that will be threatened without the moving piece's defense
					for (int k = 0; k < 16; k++) {
						//deduct points from the score for how much threatened pieces are worth
						if (!a_pieces[k]->IsCaptured() && a_pieces[k]->ToChessNote(a_pieces[k]->GetOldPosition(), a_size) == threatPath[j]) {
							score -= GetPieceValue(a_pieces[k]->GetTypeNum());

							//break out of the loops
							k = 16;
							j = threatPath.size();
						}
					}
				}
			}
		}
	}

	return score;
}
/*int Computer::GetDefenseScore(Piece* a_pieces[], const int a_size, const std::string a_from, const std::string a_to)*/

/**/
/*
Computer::IsInCheck()

NAME

		Computer::IsInCheck - checks if the king is in a check situation

SYNOPSIS

		bool Computer::IsInCheck(Piece* a_pieces[], const int a_size);
			a_pieces  --> the set of all pieces on the board
			a_size  --> the size of the grid squares

DESCRIPTION

		This function will look through all opposing pieces and check if any of them have the king in check.

RETURNS

		Returns true if a piece was found threatening the king, false if no pieces are threatening the king.

*/
/**/
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
/*bool Computer::IsInCheck(Piece* a_pieces[], const int a_size)*/

/**/
/*
Computer::IsOutOfBounds()

NAME

		Computer::IsOutOfBounds - checks if a specified move is out of bounds

SYNOPSIS

		bool Computer::IsOutOfBounds(const std::string a_move);
			a_move  --> the move to be validated

DESCRIPTION

		This function will check if a specified move is outside of the bounds
		of the main grid.

RETURNS

		Returns true if the move goes beyond the bounds of any side, returns
		false if the move is within the bounds

*/
/**/
bool Computer::IsOutOfBounds(const std::string a_move)
{
	//check if the move goes off the grid on any side
	if (a_move[0] < 'a' || a_move[0] > 'h' || a_move[1] < '1' || a_move[1] > '8') {
		return true;
	}

	return false;
}
/*bool Computer::IsOutOfBounds(const std::string a_move)*/

/**/
/*
Computer::GetPieceValue()

NAME

		Computer::GetPieceValue - assigns a value to a piece

SYNOPSIS

		int Computer::GetPieceValue(const int a_typeNum);
			a_typeNum  --> the numerical type label of a piece

DESCRIPTION

		This function will assign value to a piece based on what type it is.

RETURNS

		An integer representing the value of the piece.

*/
/**/
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
/*int Computer::GetPieceValue(const int a_typeNum)*/

/**/
/*
Computer::Resize()

NAME

		Computer::Resize - completes incomplete binary trees

SYNOPSIS

		void Computer::Resize(std::vector<int>& a_values);
			a_values  --> the list of scores being inspected

DESCRIPTION

		This function will fill in incomplete binary trees with null values to complete it.

RETURNS

		void

*/
/**/
void Computer::Resize(std::vector<int>& a_values)
{
	int depth = 0;

	//find the number of complete levels
	while (a_values.size() / (int)std::pow(2, depth) >= 1) {
		depth++;
	}

	//finish the incomplete level with very low values
	while (a_values.size() < (int)std::pow(2, depth)) {
		a_values.push_back(-10000);
	}
}
/*void Computer::Resize(std::vector<int>& a_values)*/

/**/
/*
Computer::TreeDepth()

NAME

		Computer::TreeDepth - calculates the depth of a binary tree

SYNOPSIS

		int Computer::TreeDepth(std::vector<int>& a_values);
			a_values  --> the list of scores being inspected

DESCRIPTION

		This function will calculate the depth of a list if it was put into a binary tree.

RETURNS

		An integer representing the depth of the tree.

*/
/**/
int Computer::TreeDepth(std::vector<int>& a_values)
{
	int depth = 0;

	//find how deep the tree goes
	while (a_values.size() / (int)std::pow(2, depth) > 1) {
		depth++;
	}

	return depth;
}
/*int Computer::TreeDepth(std::vector<int>& a_values)*/
