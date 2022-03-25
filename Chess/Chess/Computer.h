#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include "Piece.h"

using namespace sf;

class Computer {
private:

public:
	//constructors
	Computer();
	
	//functions for taking turns
	void TakeTurn(Piece* a_pieces[], const int a_size);

	//functions for making decisions
};