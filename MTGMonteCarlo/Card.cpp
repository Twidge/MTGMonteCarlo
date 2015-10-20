#ifndef CARD_CPP
#define CARD_CPP

#include "Card.h"
#include <string>
#include <iostream>

Card::Card(const std::string* name, const std::string* type, const Mana* mana)
{
	cardName = *name;
	cardType = *type;
	manaCost = *mana;
}

Card::Card()
{
	cardName = "";
	cardType = "";
	manaCost = Mana();
}

std::string Card::GetCardName() const
{
	return cardName;
}

std::string Card::GetCardType() const
{
	return cardType;
}

Mana Card::GetManaCost() const
{
	return manaCost;
}

#endif