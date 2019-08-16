#include "stdafx.h"
#include "Gameboard.h"
#include "Box.h"
#include "stdlib.h"
#include "malloc.h"
#include "time.h"
#include "stdio.h"
#include "String.h"

Gameboard::Gameboard(short wnumber, short hnumber, short mineNumber)
{
	Box* q, *end;
	int n, content;
	//this->game = new Box[nbrClasses * nbrClasses];
	this->wnumber = wnumber;
	this->hnumber = hnumber;
	this->mineNumber = mineNumber;
	content = wnumber * hnumber;
	this->game = (Box *)malloc(sizeof(Box)*content);
	srand(time(NULL));
	end = this->game + content;
	for (q = this->game, end = q + content; q < end; q++) {
		memcpy(q, new Box(), sizeof(Box));
		n = rand();
		if (n % 2 > 0 && mineNumber > 0) {
			q->miner = true;
			mineNumber--;
		}
	}
}


Gameboard::~Gameboard()
{
	//delete[] this->game;
	free(this->game);
}

void Gameboard::display(){
	Box* p, *end;
	char compteur;
	end = this->game + (this->wnumber)*(this->hnumber);
	compteur = this->wnumber;
	for (p = this->game, compteur = this->wnumber; p < end; p++, compteur--) {
		if (compteur == 0) {
			printf("\n");
			compteur = this->wnumber;
		}
		p->display();
	}
}

unsigned char Gameboard::threat(short x, short y) {
	short i, j, ilast, jlast, ii, jj, xx, yy;
	volatile unsigned char n = 0;
	Box* q;
	j = (x > 0) ? x - 1 : 0;
	i = (y > 0) ? y - 1 : 0;
	jlast = this->wnumber - 1;
	ilast = this->hnumber - 1;
	jj = (x < jlast) ? x + 1 : jlast;
	ii = (y < ilast) ? y + 1 : ilast;
	for (xx = j; xx <= jj; xx++) {
		for (yy = i; yy <= ii; yy++) {
			if (xx != x || yy != y) {
				q = this->game + (yy*this->wnumber + xx);
				if (q->miner) n++;
			}
		}
	}
	return ((n > 0) ? n + 48 : '-');
}

void Gameboard::showMines() {
	Box* p, *q;
	for (p = this->game, q = p+(this->wnumber*this->hnumber); p < q; p++) if (p->miner) p->aspect = 'X';
}

bool Gameboard::win() {
	Box* p, *q;
	volatile short n = 0;
	for (p = this->game, q = p; p < q; p++) if (p->aspect == 32) n++;
	
	return (n == this->mineNumber);
}
