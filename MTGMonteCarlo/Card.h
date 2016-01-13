#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include <memory>
#include "Mana.h"

enum CardType
{
	Creature,
	Planeswalker,
	Instant,
	Sorcery,
	Enchantment,
	Artifact,
	LandCard
};

enum LandType
{
	Basic,
	Fetch,
	LifeTap,
	Tap
};

class Card
{
protected :

	std::string m_cardName;
	CardType m_cardType;
	Mana m_manaCost;
	bool m_isTapped = false;

public :

	// CONSTRUCTORS

	Card();
	Card(Card const&);
	Card(CardType const);
	Card(std::string const&, CardType const);
	Card(std::string const&, CardType const, Mana const&);

	// GETTERS

	virtual bool CanGen(ManaType) const;
	std::string GetCardName() const;
	CardType GetCardType() const;
	virtual LandType GetLandType() const;
	Mana GetManaCost() const;
	bool IsTapped() const;

	// METHODS

	void Tap();

	// OPERATOR OVERLOADS

	void operator= (Card const&);
};

// Check a vector for a land that comes in untapped

bool VectorContainsLandETBUntapped(std::vector<std::shared_ptr<Card>> const&);

#endif