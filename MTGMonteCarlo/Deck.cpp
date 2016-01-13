#include "Deck.h"
#include "Card.h"
#include <fstream>
#include <iostream>

// CONSTRUCTORS

Deck::Deck()
{
	m_cards = new std::vector<std::shared_ptr<Card>>();
}

Deck::Deck(Deck const& deck)
{
	m_cards = new std::vector<std::shared_ptr<Card>>();
	*m_cards = *deck.m_cards;
}

Deck::Deck(std::vector<std::shared_ptr<Card>>* const cards)
{
	m_cards = new std::vector<std::shared_ptr<Card>>();
	*m_cards = *cards;
}

// DESTRUCTOR

Deck::~Deck()
{
	delete m_cards;
}

// GETTERS

std::shared_ptr<Card> Deck::GetCard(unsigned int number) const
{
	std::shared_ptr<Card> t_cardToReturn = std::shared_ptr<Card>(new Card());

	if (number > m_cards->size())
	{
		std::cout << "Error in Deck::GetCard(): attempting to access card out of bounds.\n";
	}

	else
	{
		t_cardToReturn = (*m_cards)[number];
	}

	return t_cardToReturn;
}

std::vector<std::shared_ptr<Card>>* Deck::GetCards() const
{
	return m_cards;
}

// METHODS

void Deck::AddCard(std::shared_ptr<Card> const& card)
{
	m_cards->push_back(card);
}

// OPERATOR OVERLOADS

void Deck::operator= (Deck const& deck)
{
	delete m_cards;
	m_cards = new std::vector<std::shared_ptr<Card>>();
	*m_cards = *deck.m_cards;
}