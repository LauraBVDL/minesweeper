// Minesweeper.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "stdio.h"
#include "Box.h"
#include "Gameboard.h"
#include "conio.h"
#include "iostream"

short width, height, column, line, numberMines;

int main()
{
	short  c, i, j;
	Gameboard* actualGame;
	Box* box;
	bool goon, replay = false;
	char response[10];

	puts("Welcome in Minesweeper");

	do {
		wquestion:
		puts("How many boxes in width ?");
		scanf_s("%d", &width);
		if (width <= 0 || width > 20) goto wquestion;

		hquestion:
		puts("How many boxes in height ?");
		scanf_s("%d", &height);
		if (height <= 0 || height > 20) goto hquestion;

		c = (width * height) / 2;
		mquestion:
		puts("How many mines ?");
		scanf_s("%d", &numberMines);
		if (numberMines <= 0 || numberMines > c) goto mquestion;

		//box représentées comme un tableau
		actualGame = new Gameboard(width, height, numberMines);
		actualGame->display();

		goon = true;
		do {
			cquestion:
			puts("\nWhich column ?");
			scanf_s("%d", &column);
			if (column < 0 || column >= width) goto cquestion;

			lquestion:
			puts("Which line ?");
			scanf_s("%d", &line);
			if (line < 0 || line >= height) goto lquestion;

			box = actualGame->game + (line * width + column);
			if (box->miner) {
				goon = false;
				actualGame->showMines();
				actualGame->display();
				puts("\nYou lost !");
			}

			else {
				box->aspect = actualGame->threat(column, line);
				actualGame->display();
				if (actualGame->win()) {
					goon = false;
					puts("\nYou win !");
				}
			}
		} while (goon);
		play:
		puts("Play again ? (Y/N)");
		scanf("%s", response);
		if (response[0] == 'Y' || response[0] == 'y') replay = true;
		else if (response[0] == 'N' || response[0] == 'n') exit(0);
		else goto play;
	} while (replay);

	getchar();
	getchar();
}
