#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>

class Card;

const unsigned int G_DECK_SIZE = 60;
const unsigned int G_MAX_OF_ONE_NONLAND_CARD = 4;

class Deck
{
public :

	// CONSTRUCTORS

	Deck();
	Deck(Deck const&);
	Deck(std::vector<std::shared_ptr<Card>>* const);

	// DESTRUCTOR

	~Deck();
	
	// GETTERS

	std::shared_ptr<Card> GetCard(unsigned int) const;
	std::vector<std::shared_ptr<Card>>* GetCards() const;

	// METHODS

	void AddCard(std::shared_ptr<Card> const&);

	// OPERATOR OVERLOADS

	void operator= (Deck const&);

private :

	std::vector<std::shared_ptr<Card>>* m_cards;
};

#endif