#ifndef SHUFFLEFUNCTIONS_CPP
#define SHUFFLEFUNCTIONS_CPP

#include <iostream>
#include "Card.h"
#include "ShuffleFunctions.h"
#include "DecklistFunctions.h"
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

vector<Card> ShuffleDeck(vector<Card> source, int deckSize)
{
	vector<Card> target;

	vector<int> remainingCards(deckSize);

	for (int i = 0; i < deckSize; i++)
	{
		remainingCards[i] = i;
	}

	for (int i = 0; i < deckSize; i++)
	{
		int cardChosen = rand() % remainingCards.size();

		target.push_back(source[remainingCards[cardChosen]]);

		for (int j = cardChosen; j < remainingCards.size() - 1; j++)
		{
			remainingCards[j] = remainingCards[j + 1];
		}

		remainingCards.pop_back();
	}

	return target;
}

void PrintShuffledDeck(vector<Card> source, int deckSize)
{
	for (int i = 0; i < deckSize; i++)
	{
		cout << source[i].GetCardName() << " / " << source[i].GetCardType() << " / ";

		Mana tempMana = source[i].GetManaCost();

		PrintMana(tempMana);

		cout << "\n";
	}
}

#endif