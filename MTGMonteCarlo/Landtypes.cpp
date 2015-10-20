#ifndef LANDTYPES_CPP
#define LANDTYPES_CPP

#include "Landtypes.h"

/*

---------------------------------------------------------
Land Methods
---------------------------------------------------------

*/

Land::Land(const std::string *name, const Mana *mana, const bool names[6])
{
	cardName = *name;
	cardType = "Land";
	manaCost = *mana;

	for (int i = 0; i < 6; i++)
	{
		canGen[i] = names[i];
	}
}

Land::Land()
{
	for (int i = 0; i < 6; i++)
	{
		canGen[i] = false;
	}
}

bool Land::CanGen(ManaTypes name) const
{
	return canGen[name];
}

/*

---------------------------------------------------------
Fetchland Methods
---------------------------------------------------------

*/

Fetchland::Fetchland(const std::string *name, const Mana *mana, const bool names[6])
{
	cardName = *name;
	cardType = "Fetchland";
	manaCost = *mana;

	for (int i = 0; i < 6; i++)
	{
		canGen[i] = names[i];
	}
}

Fetchland::Fetchland()
{
	for (int i = 0; i < 6; i++)
	{
		canGen[i] = false;
	}
}

bool Fetchland::HasChosen() const
{
	return hasChosen;
}

/*

---------------------------------------------------------
Scryland Methods
---------------------------------------------------------

*/

Scryland::Scryland(const std::string *name, const Mana *mana, const bool names[6])
{
	cardName = *name;
	cardType = "Scryland";
	manaCost = *mana;

	for (int i = 0; i < 6; i++)
	{
		canGen[i] = names[i];
	}
}

Scryland::Scryland()
{
	for (int i = 0; i < 6; i++)
	{
		canGen[i] = false;
	}
}

bool Scryland::IsTapped() const
{
	return isTapped;
}

/*

---------------------------------------------------------
Tapland Methods
---------------------------------------------------------

*/

Tapland::Tapland(const std::string *name, const Mana *mana, const bool names[6])
{
	cardName = *name;
	cardType = "Tapland";
	manaCost = *mana;

	for (int i = 0; i < 6; i++)
	{
		canGen[i] = names[i];
	}
}

Tapland::Tapland()
{
	for (int i = 0; i < 6; i++)
	{
		canGen[i] = false;
	}
}

bool Tapland::IsTapped() const
{
	return isTapped;
}

#endif