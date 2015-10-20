// MTGMonteCarlo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DecklistFunctions.h"
#include "ShuffleFunctions.h"
#include "CheckFunctions.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

bool CheckMulligan(vector<Card>, vector<Card>);

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	int size = 60;
	float trials = 0;
	int loopCount = 0;
	float successfulTrials = 0;

	const int maxCardsAllowed = 9;
	const int maxOpeningHandSize = 7;
	int cardsAllowed = 9;
	int openingHandSize = 7;
	bool shouldMulligan = false;

	vector<Card> deck;

	deck = GetDecklist(deck, "decklist.txt", size);

	cout << "Enter amount of trials: ";
	cin >> trials;

	do
	{
		vector<Card> shuffledDeck = ShuffleDeck(deck, size);

		vector<Card> topCards;
		vector<Card> lands;

		for (int i = 0; i < cardsAllowed; i++)
		{
			topCards.push_back(shuffledDeck[i]);

			if (shuffledDeck[i].GetCardType().find("Land") != string::npos || shuffledDeck[i].GetCardType().find("Fetchland") != string::npos || shuffledDeck[i].GetCardType().find("Scryland") != string::npos || shuffledDeck[i].GetCardType().find("Tapland") != string::npos)
			{
				lands.push_back(shuffledDeck[i]);
			}

			if (i == openingHandSize - 1)
			{
				shouldMulligan = CheckMulligan(topCards, lands);
			}
		}

		if (shouldMulligan)
		{
			cardsAllowed--;
			openingHandSize--;
			continue;
		}

		else
		{
			cardsAllowed = maxCardsAllowed;
			openingHandSize = maxOpeningHandSize;
		}

		/*
		bool isInHand = false;

		for (int i = 0; i < topCards.size(); i++)
		{
			if (topCards[i].GetCardName() == deck[0].GetCardName())
			{
				isInHand = true;
			}
		}

		bool works = isInHand;
		*/

		bool works = true;

		if (works)
		{
			if (lands.size() >= 6)
			{
				vector<Card> newLands;

				for (int i = 0; i < lands.size(); i++)
				{
					newLands.push_back(lands[i]);

					works = CheckIfManaFor(deck[0], newLands);
					
					if (works)
					{
						works = CheckIfManaFor(deck[3], newLands);
					}

					if (works)
					{
						break;
					}
				}
			}

			else
			{
				works = CheckIfManaFor(deck[0], lands);

				if (works)
				{
					CheckIfManaFor(deck[3], lands);
				}
			}
		}

		loopCount++;

		if (works)
		{
			cout << "Trial " << loopCount << " successful.\n";
			successfulTrials++;
		}

	} while (loopCount <= trials);

	cout << successfulTrials << " of " << trials << " trials were successful.\n";
	cout << successfulTrials / trials << " success rate.\n";

	cin.get();
	cin.get();

	return 0;
}

bool CheckMulligan(vector<Card> openingHand, vector<Card> openingLands)
{
	switch (openingHand.size())
	{
	case 7:

		if (openingLands.size() <= 1 || openingLands.size() >= 6)
		{
			return true;
		}

		else
		{
			return false;
		}

		break;

	case 6:

		if (openingLands.size() <= 1 || openingLands.size() >= 5)
		{
			return true;
		}

		else
		{
			return false;
		}

		break;

	case 5:

		if (openingLands.size() == 0 || openingLands.size() == 5)
		{
			return true;
		}

		else
		{
			return false;
		}

		break;

	default:

		return false;
	}
}
