#include "stdafx.h"
#include "Box.h"
#include "String.h"

Box::Box()
{
	this->miner = false;
	this->aspect = 32;
}

void Box::display(){
	char resultat[4];
	char* r;
	r = resultat;
	*(r++) = 91;
	*(r++) = this->aspect;
	*(r++) = 93;
	*(r++) = 0;
	printf("%s", resultat);
}
