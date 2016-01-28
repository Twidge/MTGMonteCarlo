#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Mana.h"
#include "Landtypes.h"
#include <fstream>
#include <iostream>
#include <string>

// CONSTRUCTORS

Player::Player()
{
	m_deck = new Deck();
	m_lands = new std::vector<std::shared_ptr<Card>>();
	m_library = new std::vector<std::shared_ptr<Card>>();
	m_hand = new std::vector<std::shared_ptr<Card>>();
}

Player::Player(Player const& player)
{
	m_deck = new Deck();
	*m_deck = *player.m_deck;

	m_lands = new std::vector<std::shared_ptr<Card>>();
	*m_lands = *player.m_lands;

	m_library = new std::vector<std::shared_ptr<Card>>();
	*m_library = *player.m_library;

	m_hand = new std::vector<std::shared_ptr<Card>>();
	*m_hand = *player.m_hand;

	m_canMulligan = player.m_canMulligan;
}

Player::Player(const Deck* deck)
{
	m_deck = new Deck();
	*m_deck = *deck;

	// The Player constructor that takes a Deck argument does NOT load that deck into the library

	m_lands = new std::vector<std::shared_ptr<Card>>();

	m_library = new std::vector<std::shared_ptr<Card>>();

	m_hand = new std::vector<std::shared_ptr<Card>>();
}

// DESTRUCTOR

Player::~Player()
{
	delete m_deck;
	delete m_lands;
	delete m_library;
	delete m_hand;
}

// GETTERS

bool Player::CanMulligan() const
{
	return m_canMulligan;
}

// METHODS

// Takes a filename argument and reads in a deck from that file

void Player::ConstructDeck(std::string const& filename)
{
	std::ifstream t_fileReader;
	t_fileReader.open(filename);

	if (!t_fileReader.is_open())
	{
		std::cout << "Error in Player::ConstructDeck(): could not open file with given name.\n";
	}

	else
	{
		unsigned int t_deckSize = 0;

		do
		{
			unsigned int t_cardAmount = 0;
			std::string t_cardName;
			std::string t_typeString;
			std::string t_manaString;

			// Read in the amount, card name, card type and string representing mana cost

			t_fileReader >> t_cardAmount;
			t_fileReader.get(); // Get rid of line break
			std::getline(t_fileReader, t_cardName);
			std::getline(t_fileReader, t_typeString);
			std::getline(t_fileReader, t_manaString);

			// Skip a line afterwards

			std::getline(t_fileReader, std::string());

			// Parse the mana string

			Mana t_manaCost = GetManaCostFromString(t_manaString);

			// Create the relevant object by parsing the type string

			std::shared_ptr<Card> t_newCardPointer;

			if (t_typeString == "Creature" || t_typeString == "Planeswalker" || t_typeString == "Instant" || t_typeString == "Sorcery"
				|| t_typeString == "Enchantment" || t_typeString == "Artifact")
			{
				Card t_newCard = CreateObjectFromListInfo(t_cardName, t_typeString, t_manaCost);
				t_newCardPointer = std::shared_ptr<Card>(new Card(t_newCard));
			}

			else
			{
				Land t_newLand = CreateLandFromListInfo(t_cardName, t_typeString, t_manaCost);
				t_newCardPointer = std::shared_ptr<Card>(new Land(t_newLand));
			}

			// Add the desired amount of copies to the deck

			if (t_cardAmount <= G_MAX_OF_ONE_NONLAND_CARD || t_typeString.substr(0, G_BASIC_STRING.size()) == G_BASIC_STRING)
			{
				for (unsigned int l_copy = 1; l_copy <= t_cardAmount; l_copy++)
				{
					m_deck->AddCard(t_newCardPointer);
					t_deckSize++;
				}
			}

			else
			{
				std::cout << "Error in Player::ConstructDeck(): attempting to add more copies of one card than is possible.\n";
			}

		} while (!t_fileReader.eof() && t_deckSize <= G_DECK_SIZE);
	}
}

// Given a card name, mana cost and string representing a land card type in a decklist file, returns the land that should be created

Land Player::CreateLandFromListInfo(std::string const& cardName, std::string const& typeString, Mana const& manaCost) const
{
	Land t_cardToCreate = Land();
	std::string t_landPrefix = "Land ";
	std::string t_basicPrefix = "Basic ";
	std::string t_fetchPrefix = "Fetchland ";
	std::string t_lifeTapPrefix = "LifeTapland ";
	std::string t_tapPrefix = "Tapland ";
	std::string t_tangoPrefix = "Tangoland ";

	// Parse the type string and return a land of the appropriate type which taps for the appropriate colours of mana
	// String should be of the form "Land (LandType Colours)"

	if (typeString.substr(0, t_landPrefix.size()) == t_landPrefix)
	{
		std::string t_remainingTypeString = typeString.substr(t_landPrefix.size());

		// If LandType == "Basic", create an appropriate basic land

		if (t_remainingTypeString.substr(0, t_basicPrefix.size()) == t_basicPrefix)
		{
			std::string t_colours = t_remainingTypeString.substr(t_basicPrefix.size());

			std::vector<bool> t_canGen = GetManaGenArrayFromString(t_colours);

			t_cardToCreate = BasicLand(cardName, t_canGen);
		}

		// If LandType == "Fetchland", create an appropriate fetchland

		else if (t_remainingTypeString.substr(0, t_fetchPrefix.size()) == t_fetchPrefix)
		{
			std::string t_colours = t_remainingTypeString.substr(t_fetchPrefix.size());

			std::vector<bool> t_canFind = GetManaGenArrayFromString(t_colours);

			t_cardToCreate = Fetchland(cardName, t_canFind);
		}

		// If LandType == "LifeTapland", create an appropriate lifegain tapland

		else if (t_remainingTypeString.substr(0, t_lifeTapPrefix.size()) == t_lifeTapPrefix)
		{
			std::string t_colours = t_remainingTypeString.substr(t_lifeTapPrefix.size());

			std::vector<bool> t_canGen = GetManaGenArrayFromString(t_colours);

			t_cardToCreate = LifeTapland(cardName, t_canGen);
		}

		// If LandType == "Tapland", create an appropriate tapland

		else if (t_remainingTypeString.substr(0, t_tapPrefix.size()) == t_tapPrefix)
		{
			std::string t_colours = t_remainingTypeString.substr(t_tapPrefix.size());

			std::vector<bool> t_canGen = GetManaGenArrayFromString(t_colours);

			t_cardToCreate = Tapland(cardName, t_canGen);
		}

		// Otherwise, error

		else
		{
			std::cout << "Error in Player::CreateObjectFromListInfo(): land card could not be parsed.\n";
		}
	}

	return t_cardToCreate;
}

// Given a card name, mana cost and string representing the non-land card type in a decklist file, returns the card that should be created

Card Player::CreateObjectFromListInfo(std::string const& cardName, std::string const& typeString, Mana const& manaCost) const
{
	Card t_cardToCreate = Card();

	// In the non-land cases, card creation is fairly simple
	// (For now, we choose to skip eg. enchantment creatures since we are only checking mana bases)

	if (typeString == "Creature")
	{
		t_cardToCreate = Card(cardName, Creature, manaCost);
	}

	else if (typeString == "Planeswalker")
	{
		t_cardToCreate = Card(cardName, Planeswalker, manaCost);
	}

	else if (typeString == "Instant")
	{
		t_cardToCreate = Card(cardName, Instant, manaCost);
	}

	else if (typeString == "Sorcery")
	{
		t_cardToCreate = Card(cardName, Sorcery, manaCost);
	}

	else if (typeString == "Enchantment")
	{
		t_cardToCreate = Card(cardName, Enchantment, manaCost);
	}

	else if (typeString == "Artifact")
	{
		t_cardToCreate = Card(cardName, Artifact, manaCost);
	}

	return t_cardToCreate;
}

// Given a string representing a mana cost, turn this into a mana object corresponding to that mana cost

Mana Player::GetManaCostFromString(std::string const& manaString) const
{
	bool t_numberSeen = false;
	Mana t_output = Mana();

	for (unsigned int l_letter = 0; l_letter < manaString.length(); l_letter++)
	{
		if (isdigit(manaString[l_letter]))
		{
			if (!t_numberSeen)
			{
				t_output.AddMana(static_cast<unsigned int>(manaString[l_letter] - '0'), AnyColour);

				t_numberSeen = true;
			}

			else
			{
				std::cout << "Error in Player::GetManaCostFromString(): string has more than one number in.\n";
			}
		}

		else if (manaString[l_letter] == 'C')
		{
			t_output.AddMana(1, Colourless);
		}

		else if (manaString[l_letter] == 'W')
		{
			t_output.AddMana(1, White);
		}

		else if (manaString[l_letter] == 'U')
		{
			t_output.AddMana(1, Blue);
		}

		else if (manaString[l_letter] == 'B')
		{
			t_output.AddMana(1, Black);
		}

		else if (manaString[l_letter] == 'R')
		{
			t_output.AddMana(1, Red);
		}

		else if (manaString[l_letter] == 'G')
		{
			t_output.AddMana(1, Green);
		}

		else
		{
			std::cout << "Error in Player::GetManaFromString(): unfamiliar symbol encountered.\n";
			std::cout << "Symbol is: " << manaString[l_letter] << "\n";
			std::cin.get();
		}
	}

	return t_output;
}

// Given a string representing a collection of colours a land can generate, returns m_canGen for that land

std::vector<bool> Player::GetManaGenArrayFromString(std::string const& manaGenString) const
{
	std::vector<bool> t_canGen = std::vector<bool>(G_MANA_TYPES, false);

	for (unsigned int l_letter = 0; l_letter < manaGenString.length(); l_letter++)
	{
		if (manaGenString[l_letter] == 'C')
		{
			t_canGen[Colourless] = true;
			t_canGen[AnyColour] = true;
		}

		else if (manaGenString[l_letter] == 'W')
		{
			t_canGen[White] = true;
			t_canGen[AnyColour] = true;
		}

		else if (manaGenString[l_letter] == 'U')
		{
			t_canGen[Blue] = true;
			t_canGen[AnyColour] = true;
		}

		else if (manaGenString[l_letter] == 'B')
		{
			t_canGen[Black] = true;
			t_canGen[AnyColour] = true;
		}

		else if (manaGenString[l_letter] == 'R')
		{
			t_canGen[Red] = true;
			t_canGen[AnyColour] = true;
		}

		else if (manaGenString[l_letter] == 'G')
		{
			t_canGen[Green] = true;
			t_canGen[AnyColour] = true;
		}
	}

	return t_canGen;
}

void Player::ShuffleLibrary()
{
	for (unsigned int l_card = 0; l_card < m_library->size() - 1; l_card++)
	{
		unsigned int t_cardChosen = (rand() % (m_library->size() - l_card)) + l_card;

		std::shared_ptr<Card> t_tempPtr = (*m_library)[l_card];
		(*m_library)[l_card] = (*m_library)[t_cardChosen];
		(*m_library)[t_cardChosen] = t_tempPtr;
	}

	/*
	std::vector<unsigned int> t_remainingCards(m_library->size());
	std::vector<std::shared_ptr<Card>> t_shuffledLibrary(m_library->size());

	// Populate a vector of unsigned ints representing remaining cards

	for (unsigned int l_card = 0; l_card < m_library->size(); l_card++)
	{
		t_remainingCards[l_card] = l_card;
	}
	
	// Put random cards from the library into the new, shuffled deck

	for (unsigned int l_card = 0; l_card < m_library->size(); l_card++)
	{
		unsigned int t_cardChosen = rand() % t_remainingCards.size();

		t_shuffledLibrary[l_card] = ((*m_library)[t_remainingCards[t_cardChosen]]);

		t_remainingCards.erase(t_remainingCards.begin() + t_cardChosen);
	}

	*m_library = t_shuffledLibrary;
	*/
}

// HAND SIMULATION

// Checks if a given card is in the player's hand

bool Player::CheckCardInHand(Card const& desiredCard)
{
	bool t_cardIsInHand = false;

	for (unsigned int l_cardInHand = 0; l_cardInHand < m_hand->size(); l_cardInHand++)
	{
		if ((*m_hand)[l_cardInHand]->GetCardName() == desiredCard.GetCardName())
		{
			t_cardIsInHand = true;
			break;
		}
	}

	return t_cardIsInHand;
}

// Checks if the mana cost of the card in the argument can be paid for using the lands in the player's hand

bool Player::CheckMana(Card const& desiredCard)
{
	bool t_playerHasMana = false;
	bool t_costIsZero = true;

	// Check if the mana cost is zero (so we can always play it)

	for (unsigned int l_manaColour = 0; l_manaColour < G_MANA_TYPES; l_manaColour++)
	{
		if (desiredCard.GetManaCost().GetMana(static_cast<ManaType>(l_manaColour)) != 0)
		{
			t_costIsZero = false;
			break;
		}
	}

	// If the cost is zero, we can play it

	if (t_costIsZero)
	{
		t_playerHasMana = true;
	}

	// Otherwise, check the mana cost can be achieved

	else
	{
		t_playerHasMana = CheckMana(desiredCard.GetManaCost(), std::vector<std::shared_ptr<Card>>(), *m_lands);
	}

	return t_playerHasMana;
}

// Checks if the mana cost in the argument can be paid for using the lands in the land vector

bool Player::CheckMana(Mana const& manaCostRemaining, std::vector<std::shared_ptr<Card>> const& landsUsedSoFar,
	std::vector<std::shared_ptr<Card>> const& landsRemaining)
{
	unsigned int t_convertedManaCost = 0;
	bool t_canPay = false;

	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		t_convertedManaCost += manaCostRemaining.GetMana(static_cast<ManaType>(l_manaType));
	}

	// Base case: if the CMC is 1, check there's a land that can produce the mana necessary

	if (t_convertedManaCost == 1)
	{
		// Find the type of mana required

		for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
		{
			if (manaCostRemaining.GetMana(static_cast<ManaType>(l_manaType)) == 1)
			{
				// Find a land that can produce that colour of mana

				for (unsigned int l_landRemaining = 0; l_landRemaining < landsRemaining.size(); l_landRemaining++)
				{
					if (landsRemaining[l_landRemaining]->CanGen(static_cast<ManaType>(l_manaType)))
					{
						// Check if the combination of that land with the ones used so far contains a land that comes in untapped
						// (ie. fetch or basic)

						std::vector<std::shared_ptr<Card>> t_newLandsUsedSoFar = landsUsedSoFar;

						t_newLandsUsedSoFar.push_back(landsRemaining[l_landRemaining]);

						t_canPay = VectorContainsLandETBUntapped(t_newLandsUsedSoFar);

						if (t_canPay)
						{
							break;
						}
					}
				}

				if (t_canPay)
				{
					break;
				}
			}
		}
	}

	else
	{
		// Find the next type of mana required

		for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
		{
			if (manaCostRemaining.GetMana(static_cast<ManaType>(l_manaType)) >= 1)
			{
				// Find a land that can produce that colour of mana

				for (unsigned int l_landRemaining = 0; l_landRemaining < landsRemaining.size(); l_landRemaining++)
				{
					if (landsRemaining[l_landRemaining]->CanGen(static_cast<ManaType>(l_manaType)))
					{
						// Check if the combination of that land with the ones used so far contains a land that comes in untapped
						// (ie. fetch or basic)

						std::vector<std::shared_ptr<Card>> t_newLandsUsedSoFar = landsUsedSoFar;
						std::vector<std::shared_ptr<Card>> t_newLandsRemaining = landsRemaining;
						Mana t_newManaCostRemaining = manaCostRemaining;

						t_newLandsUsedSoFar.push_back(landsRemaining[l_landRemaining]);
						t_newLandsRemaining.erase(t_newLandsRemaining.begin() + l_landRemaining);
						t_newManaCostRemaining.RemoveMana(1, static_cast<ManaType>(l_manaType));

						t_canPay = CheckMana(t_newManaCostRemaining, t_newLandsUsedSoFar, t_newLandsRemaining);

						if (t_canPay)
						{
							break;
						}
					}
				}

				if (t_canPay)
				{
					break;
				}
			}
		}
	}

	return t_canPay;
}

// Decides whether to mulligan based on the current starting hand
// NOTE: Vancouver mulligan not yet implemented
// Returns true exactly if either a) hand contains 0, 1, 6 or 7 lands or b) hand is of size 4

bool Player::DecideMulligan()
{
	bool t_shouldMulligan;
	unsigned int t_numberOfLands = 0;

	if (!m_canMulligan)
	{
		std::cout << "Error in Player::DecideMulligan(): player not able to mulligan.\n";
	}

	else if (m_hand->size() == G_MIN_HAND_SIZE_TO_ALWAYS_KEEP)
	{
		t_shouldMulligan = false;
		m_canMulligan = false;
	}

	else
	{
		for (unsigned int l_cardInHand = 0; l_cardInHand < m_hand->size(); l_cardInHand++)
		{
			if ((*m_hand)[l_cardInHand]->GetCardType() == LandCard)
			{
				t_numberOfLands++;
			}
		}

		if ((t_numberOfLands <= 1 || t_numberOfLands >= 6) && m_hand->size() == 7)
		{
			t_shouldMulligan = true;
		}

		else if ((t_numberOfLands <= 1 || t_numberOfLands == 6) && m_hand->size() == 6)
		{
			t_shouldMulligan = true;
		}

		else if ((t_numberOfLands == 0 || t_numberOfLands == 5) && m_hand->size() == 5)
		{
			t_shouldMulligan = true;
		}

		else
		{
			t_shouldMulligan = false;
			m_canMulligan = false;
		}
	}

	return t_shouldMulligan;
}

// Determines the player's starting hand by drawing 7, then resolving mulligans repeatedly until they keep a hand
// (then drawing an extra card if on the draw).

void Player::DetermineStartingHand(bool playFirst)
{
	bool t_mulligansComplete = false;
	unsigned int t_cardsToDraw = G_SIZE_OF_STARTING_HAND;

	do
	{
		ShuffleLibrary();

		for (unsigned int l_cardBeingDrawn = 0; l_cardBeingDrawn < t_cardsToDraw; l_cardBeingDrawn++)
		{
			DrawCard();
		}

		bool t_shouldMulligan = DecideMulligan();

		if (t_shouldMulligan)
		{
			DumpHandIntoLibrary();
			t_cardsToDraw--;
		}

		else
		{
			t_mulligansComplete = true;
		}

	} while (!t_mulligansComplete);

	if (!playFirst)
	{
		DrawCard();
	}
}

// Adds the top card of the player's library to their hand

void Player::DrawCard()
{
	if (m_library->size() != 0)
	{
		m_hand->push_back((*m_library)[m_library->size() - 1]);
		m_library->pop_back();
	}

	else
	{
		std::cout << "Error in Player::DrawCard(): library is empty.\n";
	}
}

// Puts all cards from the player's hand into their library

void Player::DumpHandIntoLibrary()
{
	for (unsigned int l_cardInHand = 0; l_cardInHand < m_hand->size(); l_cardInHand++)
	{
		m_library->push_back((*m_hand)[l_cardInHand]);
	}

	m_hand->clear();
}

// Copies all lands from player's hand into vector of lands

void Player::PopulateLandVector()
{
	m_lands->clear();

	for (unsigned int l_cardInHand = 0; l_cardInHand < m_hand->size(); l_cardInHand++)
	{
		if ((*m_hand)[l_cardInHand]->GetCardType() == LandCard)
		{
			m_lands->push_back((*m_hand)[l_cardInHand]);
		}
	}
}

// Resets the player's simulation to its starting state

void Player::ResetSimulation()
{
	// Reset ability to mulligan

	m_canMulligan = true;

	// Empty hand and lands

	delete m_hand;
	delete m_lands;

	m_hand = new std::vector<std::shared_ptr<Card>>();
	m_lands = new std::vector<std::shared_ptr<Card>>();

	// Set the deck to be the player's library

	SetDeckAsLibrary();
}

// Sets the player's deck as their library

void Player::SetDeckAsLibrary()
{
	delete m_library;
	m_library = new std::vector<std::shared_ptr<Card>>();
	*m_library = *m_deck->GetCards();
}

// OPERATOR OVERLOADS

void Player::operator= (Player const& player)
{
	delete m_deck;
	m_deck = new Deck();
	*m_deck = *player.m_deck;

	delete m_lands;
	m_lands = new std::vector<std::shared_ptr<Card>>();
	*m_lands = *player.m_lands;

	delete m_library;
	m_library = new std::vector<std::shared_ptr<Card>>();
	*m_library = *player.m_library;

	delete m_hand;
	m_hand = new std::vector<std::shared_ptr<Card>>();
	*m_hand = *player.m_hand;

	m_canMulligan = player.m_canMulligan;
}