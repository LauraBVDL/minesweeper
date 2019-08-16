#pragma once
#include "Box.h"
class Gameboard
{
public:
	Box* game;
	short wnumber, hnumber, mineNumber;

	Gameboard();
	Gameboard(short, short, short);
	~Gameboard();
	void display();
	unsigned char threat(short, short);
	void showMines();
	bool win();
};

