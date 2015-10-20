#ifndef MANA_CPP
#define MANA_CPP

#include "Mana.h"

Mana::Mana(int a, int b, int c, int d, int e, int f)
{
	mana[colourless] = a;
	mana[white] = b;
	mana[blue] = c;
	mana[black] = d;
	mana[red] = e;
	mana[green] = f;
}

Mana::Mana()
{
	for (int i = 0; i < 6; i++)
	{
		mana[i] = 0;
	}
}

void Mana::AddMana(int amount, char colour)
{
	switch (colour)
	{
	case 'C' :
		mana[colourless] += amount;
		break;

	case 'W' :
		mana[white] += amount;
		break;

	case 'U' :
		mana[blue] += amount;
		break;

	case 'B' :
		mana[black] += amount;
		break;

	case 'R' :
		mana[red] += amount;
		break;

	case 'G' :
		mana[green] += amount;
		break;
	}
}

int Mana::GetMana(int x) const
{
	return mana[x];
}

int Mana::GetMana(ManaTypes name) const
{
	return mana[name];
}

#endif