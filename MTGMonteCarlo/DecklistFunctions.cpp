#ifndef DECKLISTFUNCTIONS_CPP
#define DECKLISTFUNCTIONS_CPP

#include <iostream>
#include <fstream>
#include "DecklistFunctions.h"

using namespace std;

vector<Card> GetDecklist(vector<Card> target, string filename, int deckSize)
{
	ifstream input;
	input.open(filename);

	if (!input.is_open())
	{
		cout << "decklist.txt failed to open. Please ensure it is in the correct directory.\n";
	}

	const int limit = 50;

	bool amountRead = false, cardNameRead = false, cardTypeRead = false, manaCostRead = false;
	char nextline[limit];

	int currentCard = 0;
	int amount = 0;
	string cardName;
	string cardType;
	Mana manaCost = Mana();
	bool manaGen[6] = { false, false, false, false, false, false };
	bool deckBelowMax = true;

	do
	{
		CleanArray(nextline, limit);

		input.getline(&nextline[0], limit);

		if (!amountRead)
		{
			if (nextline[1] != 'x')
			{
				amount += 10 * (nextline[0] - '0');
				amount += (nextline[1] - '0');
			}

			else
			{
				amount += nextline[0] - '0';
			}

			amountRead = true;
		}

		else if (!cardNameRead)
		{
			cardName = nextline;
			cardNameRead = true;
		}

		else if (!cardTypeRead)
		{
			cardType = nextline;
			cardTypeRead = true;

			// Note: this next bit is SUPER hacky. It works because Land, Scryland, Tapland and Fetchland start with L, S, T and F.

			if (cardType.find("Land") != string::npos || cardType.find("Fetchland") != string::npos || cardType.find("Scryland") != string::npos || cardType.find("Tapland") != string::npos)
			{
				if (cardType.find("W") != string::npos)
				{
					manaGen[white] = true;
					manaGen[colourless] = true;
				}

				if (cardType.find("U") != string::npos)
				{
					manaGen[blue] = true;
					manaGen[colourless] = true;
				}

				if (cardType.find("B") != string::npos)
				{
					manaGen[black] = true;
					manaGen[colourless] = true;
				}

				if (cardType.find("R") != string::npos)
				{
					manaGen[red] = true;
					manaGen[colourless] = true;
				}

				if (cardType.find("G") != string::npos)
				{
					manaGen[green] = true;
					manaGen[colourless] = true;
				}
			}
		}

		else if (!manaCostRead)
		{
			manaCost = Mana();

			for (int i = 0; i < limit; i++)
			{
				if (isdigit(nextline[i]))
				{
					// IMPORTANT: This does not currently work if the colourless mana cost is above 9.

					manaCost.AddMana(nextline[i] - '0', 'C');
				}

				else if (nextline[i] != '\0')
				{
					manaCost.AddMana(1, nextline[i]);
				}

				else
				{
					break;
				}
			}

			if (cardType == "Land")
			{
				for (int i = currentCard; i < currentCard + amount; i++)
				{
					if (i >= deckSize)
					{
						cout << "More than " << deckSize << " cards found in decklist. Please adjust your decklist and try again.";
						deckBelowMax = false;
						break;
					}

					target.push_back(Land(&cardName, &manaCost, manaGen));
				}
			}

			else if (cardType == "Fetchland")
			{
				for (int i = currentCard; i < currentCard + amount; i++)
				{
					if (i >= deckSize)
					{
						cout << "More than " << deckSize << " cards found in decklist. Please adjust your decklist and try again.";
						deckBelowMax = false;
						break;
					}

					target.push_back(Fetchland(&cardName, &manaCost, manaGen));
				}
			}

			else if (cardType == "Scryland")
			{
				for (int i = currentCard; i < currentCard + amount; i++)
				{
					if (i >= deckSize)
					{
						cout << "More than " << deckSize << " cards found in decklist. Please adjust your decklist and try again.";
						deckBelowMax = false;
						break;
					}

					target.push_back(Scryland(&cardName, &manaCost, manaGen));
				}
			}

			else if (cardType == "Tapland")
			{
				for (int i = currentCard; i < currentCard + amount; i++)
				{
					if (i >= deckSize)
					{
						cout << "More than " << deckSize << " cards found in decklist. Please adjust your decklist and try again.";
						deckBelowMax = false;
						break;
					}

					target.push_back(Tapland(&cardName, &manaCost, manaGen));
				}
			}

			else
			{
				for (int i = currentCard; i < currentCard + amount; i++)
				{
					if (i >= deckSize)
					{
						cout << "More than " << deckSize << " cards found in decklist. Please adjust your decklist and try again.";
						deckBelowMax = false;
						break;
					}

					target.push_back(Card(&cardName, &cardType, &manaCost));
				}
			}

			currentCard += amount;

			input.getline(&nextline[0], limit);

			amountRead = cardNameRead = cardTypeRead = manaCostRead = false;

			for (int i = 0; i < 6; i++)
			{
				manaGen[i] = false;
			}

			amount = 0;
		}

	} while (!input.eof() && deckBelowMax);

	return target;
}

void PrintDecklist(vector<Card> source, int deckSize)
{
	int indexFirstSeen = 0;

	for (int i = 0; i < deckSize; i++)
	{
		if (i >= 1 && i != deckSize - 1)
		{
			if (source[i].GetCardName() != source[i - 1].GetCardName())
			{
				cout << i - indexFirstSeen << "x ";

				cout << source[i - 1].GetCardName() << " / " << source[i - 1].GetCardType() << " / ";

				Mana tempMana = source[i - 1].GetManaCost();

				PrintMana(tempMana);

				cout << "\n";

				indexFirstSeen = i;
			}
		}

		else if (i == deckSize - 1)
		{
			if (source[i].GetCardName() == source[i - 1].GetCardName())
			{
				cout << deckSize - indexFirstSeen << "x ";

				cout << source[i].GetCardName() << " / " << source[i].GetCardType() << " / ";

				Mana tempMana = source[i].GetManaCost();

				PrintMana(tempMana);

				cout << "\n";
			}

			else
			{
				cout << i - indexFirstSeen << "x ";

				cout << source[i - 1].GetCardName() << " / " << source[i - 1].GetCardType() << " / ";

				Mana tempMana = source[i - 1].GetManaCost();

				PrintMana(tempMana);

				cout << "\n";

				cout << "1x ";

				cout << source[i].GetCardName() << " / " << source[i].GetCardType() << " / ";

				tempMana = source[i].GetManaCost();

				PrintMana(tempMana);

				cout << "\n";
			}
		}
	}
}

void PrintMana(Mana &mana)
{
	if (mana.GetMana(colourless) != 0)
	{
		cout << mana.GetMana(colourless);
	}

	if (mana.GetMana(white) != 0)
	{
		for (int i = 0; i < mana.GetMana(white); i++)
		{
			cout << "W";
		}
	}

	if (mana.GetMana(blue) != 0)
	{
		for (int i = 0; i < mana.GetMana(blue); i++)
		{
			cout << "U";
		}
	}

	if (mana.GetMana(black) != 0)
	{
		for (int i = 0; i < mana.GetMana(black); i++)
		{
			cout << "B";
		}
	}

	if (mana.GetMana(red) != 0)
	{
		for (int i = 0; i < mana.GetMana(red); i++)
		{
			cout << "R";
		}
	}

	if (mana.GetMana(green) != 0)
	{
		for (int i = 0; i < mana.GetMana(green); i++)
		{
			cout << "G";
		}
	}
}

void CleanArray(char word[], int size)
{
	for (int i = 0; i < size; i++)
	{
		word[i] = '\0';
	}
}

#endif