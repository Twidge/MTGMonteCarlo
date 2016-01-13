#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>

class Mana; // .
class Card; // .
class Land; // .
class Deck; // Forward declarations

const std::string G_BASIC_STRING = "Land Basic";
const unsigned int G_SIZE_OF_STARTING_HAND = 7;
const unsigned int G_MIN_HAND_SIZE_TO_ALWAYS_KEEP = 4;

class Player
{
public :

	// CONSTRUCTORS

	Player();
	Player(Player const&);
	Player(const Deck*);

	// DESTRUCTOR

	~Player();

	// GETTERS

	// virtual bool CanGen() const;
	bool CanMulligan() const;

	// METHODS

	void ConstructDeck(std::string const&);
	Land CreateLandFromListInfo(std::string const&, std::string const&, Mana const&) const;
	Card CreateObjectFromListInfo(std::string const&, std::string const&, Mana const&) const;
	Mana GetManaCostFromString(std::string const&) const;
	std::vector<bool> GetManaGenArrayFromString(std::string const&) const;
	void ShuffleLibrary();

	// HAND SIMULATION

	bool CheckCardInHand(Card const&);
	bool CheckMana(Card const&);
	bool CheckMana(Mana const&, std::vector<std::shared_ptr<Card>> const&, std::vector<std::shared_ptr<Card>> const&);
	bool DecideMulligan();
	void DetermineStartingHand(bool);
	void DrawCard();
	void DumpHandIntoLibrary();
	void PopulateLandVector();
	void ResetSimulation();
	void SetDeckAsLibrary();

	// OPERATOR OVERLOADS

	void operator= (Player const&);

private :

	Deck* m_deck;
	std::vector<std::shared_ptr<Card>>* m_lands;
	std::vector<std::shared_ptr<Card>>* m_library;
	std::vector<std::shared_ptr<Card>>* m_hand;

	bool m_canMulligan = true;
};

#endif