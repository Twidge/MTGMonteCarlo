#include "Card.h"
#include <string>
#include <iostream>
#include <vector>

// CONSTRUCTORS

Card::Card()
{
	m_cardName = "";
	m_cardType = Creature;
	m_manaCost = Mana();
	m_isTapped = false;
}

Card::Card(Card const& card)
{
	m_cardName = card.m_cardName;
	m_cardType = card.m_cardType;
	m_manaCost = card.m_manaCost;
	m_isTapped = card.m_isTapped;
}

Card::Card(CardType const cardType)
{
	m_cardName = "";
	m_cardType = cardType;
	m_manaCost = Mana();
	m_isTapped = false;
}

Card::Card(std::string const& cardName, CardType const cardType)
{
	m_cardName = cardName;
	m_cardType = cardType;
	m_manaCost = Mana();
	m_isTapped = false;
}

Card::Card(std::string const& cardName, CardType const cardType, Mana const& manaCost)
{
	m_cardName = cardName;
	m_cardType = cardType;
	m_manaCost = manaCost;
}

// GETTERS

bool Card::CanGen(ManaType targetType) const
{
	std::cout << "Error: virtual method Card::CanGen() is being called. This should not happen.\n";

	return false;
}

std::string Card::GetCardName() const
{
	return m_cardName;
}

CardType Card::GetCardType() const
{
	return m_cardType;
}

LandType Card::GetLandType() const
{
	std::cout << "Error: virtual method Card::GetLandType() is being called. This should not happen.\n";

	return Basic;
}

Mana Card::GetManaCost() const
{
	return m_manaCost;
}

bool Card::IsTapped() const
{
	return m_isTapped;
}

// METHODS

void Card::Tap()
{
	if (!m_isTapped)
	{
		m_isTapped = true;
	}

	else
	{
		std::cout << "Error in Card::Tap(): card is already tapped.\n";
	}
}

// OPERATOR OVERLOADS

void Card::operator=(Card const& card)
{
	m_cardName = card.m_cardName;
	m_cardType = card.m_cardType;
	m_manaCost = card.m_manaCost;
	m_isTapped = card.m_isTapped;
}

// OTHER FUNCTIONS

bool VectorContainsLandETBUntapped(std::vector<std::shared_ptr<Card>> const& landVector)
{
	bool t_containsGoodLand = false;

	for (unsigned int l_landInVector = 0; l_landInVector < landVector.size(); l_landInVector++)
	{
		if (landVector[l_landInVector]->GetLandType() == Basic || landVector[l_landInVector]->GetLandType() == Fetch)
		{
			t_containsGoodLand = true;
		}
	}

	return t_containsGoodLand;
}