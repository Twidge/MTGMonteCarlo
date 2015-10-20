#ifndef LANDTYPES_H
#define LANDTYPES_H

#include "Card.h"

class Land : public Card
{
protected :

	bool canGen[6];

public :

	Land(const std::string*, const Mana*, const bool[6]);
	Land();
	bool CanGen(ManaTypes) const;

	Land operator= (const Land& source);
};

class Fetchland : public Land
{
private :

	bool hasChosen = false;

public :

	Fetchland(const std::string*, const Mana*, const bool[6]);
	Fetchland();

	bool HasChosen() const;

	Fetchland operator= (const Fetchland& source);
};

class Scryland : public Land
{
private :
	
	bool isTapped = true;

public :

	Scryland(const std::string*, const Mana*, const bool[6]);
	Scryland();

	bool IsTapped() const;

	Scryland operator= (const Scryland& source);
};

class Tapland : public Land
{
private :

	bool isTapped = true;

public :

	Tapland(const std::string*, const Mana*, const bool[6]);
	Tapland();

	bool IsTapped() const;

	Tapland operator= (const Tapland& source);
};

#endif