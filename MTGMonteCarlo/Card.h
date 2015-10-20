#ifndef CARD_H
#define CARD_H

#include <string>
#include "Mana.h"

class Card
{
	friend class Fetchland;
	friend class Scryland;
	friend class Tapland;

protected :

	std::string cardName;
	std::string cardType;
	Mana manaCost;

public :

	Card(const std::string*, const std::string*, const Mana*);
	Card();

	std::string GetCardName() const;
	std::string GetCardType() const;
	Mana GetManaCost() const;
};

#endif