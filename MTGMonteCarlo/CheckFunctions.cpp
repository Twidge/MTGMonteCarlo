#ifndef CHECKFUNCTIONS_CPP
#define CHECKFUNCTIONS_CPP

#include "CheckFunctions.h"
#include "DecklistFunctions.h"
#include <iostream>
#include <string>

bool CheckIfManaFor(const Card& card, std::vector<Card> lands)
{
	std::vector<char> cardManaString;

	if (card.GetManaCost().GetMana(colourless) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(colourless); j++)
		{
			cardManaString.push_back('C');
		}
	}

	if (card.GetManaCost().GetMana(white) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(white); j++)
		{
			cardManaString.push_back('W');
		}
	}

	if (card.GetManaCost().GetMana(blue) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(blue); j++)
		{
			cardManaString.push_back('U');
		}
	}

	if (card.GetManaCost().GetMana(black) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(black); j++)
		{
			cardManaString.push_back('B');
		}
	}

	if (card.GetManaCost().GetMana(red) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(red); j++)
		{
			cardManaString.push_back('R');
		}
	}

	if (card.GetManaCost().GetMana(green) != 0)
	{
		for (int j = 0; j < card.GetManaCost().GetMana(green); j++)
		{
			cardManaString.push_back('G');
		}
	}

	std::vector<std::vector<char>> manaStrings;

	for (int i = 0; i < lands.size(); i++)
	{
		manaStrings.push_back(StringLand(lands[i]));
	}

	std::vector<std::vector<char>> allStrings;
	std::vector<char> currentString;

	allStrings = ConstructAllManaStrings(allStrings, cardManaString, manaStrings, currentString, 0);

	for (int i = 0; i < allStrings.size(); i++)
	{
		bool stringWorks = true;

		stringWorks = CheckIfStringHasMana(card, allStrings[i], colourless);

		if (stringWorks)
		{
			stringWorks = CheckIfStringHasMana(card, allStrings[i], white);
		}

		if (stringWorks)
		{
			stringWorks = CheckIfStringHasMana(card, allStrings[i], blue);
		}

		if (stringWorks)
		{
			stringWorks = CheckIfStringHasMana(card, allStrings[i], black);
		}

		if (stringWorks)
		{
			stringWorks = CheckIfStringHasMana(card, allStrings[i], red);
		}

		if (stringWorks)
		{
			stringWorks = CheckIfStringHasMana(card, allStrings[i], green);
		}

		if (stringWorks)
		{
			bool untapLandExists = false;

			for (int j = 0; j < lands.size(); j++)
			{
				for (int k = 0; k < cardManaString.size(); k++)
				{
					if (lands[j].GetCardType().find(cardManaString[k]) != std::string::npos && (lands[j].GetCardType().find("Land") != std::string::npos || lands[j].GetCardType().find("Fetchland") != std::string::npos))
					{
						untapLandExists = true;
					}
				}
			}

			stringWorks = untapLandExists;
		}

		if (stringWorks)
		{
			return true;
		}
	}

	return false;
}

bool CheckIfStringHasMana(const Card& card, std::vector<char> foo, ManaTypes mana)
{
	if (card.GetManaCost().GetMana(mana) > 0)
	{
		int colCount = 0;

		for (int j = 0; j < foo.size(); j++)
		{
			if (mana == colourless)
			{
				if (foo[j] == 'C')
				{
					colCount++;
				}
			}

			else if (mana == white)
			{
				if (foo[j] == 'W')
				{
					colCount++;
				}
			}

			else if (mana == blue)
			{
				if (foo[j] == 'U')
				{
					colCount++;
				}
			}

			else if (mana == black)
			{
				if (foo[j] == 'B')
				{
					colCount++;
				}
			}

			else if (mana == red)
			{
				if (foo[j] == 'R')
				{
					colCount++;
				}
			}

			else if (mana == green)
			{
				if (foo[j] == 'G')
				{
					colCount++;
				}
			}
		}

		if (colCount < card.GetManaCost().GetMana(mana))
		{
			return false;
		}
	}

	return true;
}

void DisplayAllManaStrings(std::vector<std::vector<char>> allStrings)
{
	std::cout << "All mana strings:\n";
	std::cout << "\n";

	for (int i = 0; i < allStrings.size(); i++)
	{
		for (int j = 0; j < allStrings[i].size(); j++)
		{
			std::cout << allStrings[i][j];
		}

		std::cout << "\n";
	}
}

std::vector<std::vector<char>> ConstructAllManaStrings(std::vector<std::vector<char>> target, std::vector<char> cardString, std::vector<std::vector<char>> manaStrings, std::vector<char> currentString, int n)
{
	if (manaStrings.size() == 0)
	{
		return target;
	}

	for (int i = 0; i < manaStrings[n].size(); i++)
	{
		currentString.push_back(manaStrings[n][i]);
		
		if (n == manaStrings.size() - 1)
		{
			bool shouldAdd = true;

			for (int j = 0; j < cardString.size(); j++)
			{
				bool manaPresent = false;

				if (cardString[j] != 'C')
				{
					for (int k = 0; k < currentString.size(); k++)
					{
						if (currentString[k] == cardString[j])
						{
							manaPresent = true;
							break;
						}
					}
				}

				if (!manaPresent)
				{
					shouldAdd = false;
				}
			}

			if (shouldAdd)
			{
				target.push_back(currentString);
			}
		}

		else
		{
			target = ConstructAllManaStrings(target, cardString, manaStrings, currentString, n + 1);
		}

		currentString.pop_back();
	}

	return target;
}

std::vector<char> StringLand(const Card& land)
{
	std::vector<char> end;
	bool colourless;

	if (land.GetCardType().find("W") != std::string::npos)
	{
		end.push_back('W');
		colourless = true;
	}

	if (land.GetCardType().find("U") != std::string::npos)
	{
		end.push_back('U');
		colourless = true;
	}

	if (land.GetCardType().find("B") != std::string::npos)
	{
		end.push_back('B');
		colourless = true;
	}

	if (land.GetCardType().find("R") != std::string::npos)
	{
		end.push_back('R');
		colourless = true;
	}

	if (land.GetCardType().find("G") != std::string::npos)
	{
		end.push_back('G');
		colourless = true;
	}

	if (colourless)
	{
		end.push_back('C');
	}

	return end;
}

std::vector<int> RefreshLands(int x)
{
	std::vector<int> end(x);

	for (int i = 0; i < x; i++)
	{
		end[i] = i;
	}

	return end;
}

#endif