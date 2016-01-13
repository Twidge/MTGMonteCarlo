#ifndef LANDTYPES_H
#define LANDTYPES_H

#include "Card.h"
#include <vector>

class Card;
enum LandType;
enum ManaType;

enum BasicType
{
	Wastes,
	Plains,
	Island,
	Swamp,
	Mountain,
	Forest
};

const unsigned int G_BASIC_TYPES = 6;

// Lands are the sources of mana for MTG spells

class Land : public Card
{
protected :

	std::vector<bool> m_canGen; // A Boolean vector that determines whether the land can generate Colourless, White, Blue, Black, Red or Green mana
	LandType m_landType;
	std::vector<BasicType> m_basicTypes;

public :

	// CONSTRUCTORS

	Land();
	Land(Land const&);
	Land(std::string const&);
	Land(std::string const&, std::vector<bool> const&);
	
	// GETTERS
	
	bool CanGen(ManaType) const;
	LandType GetLandType() const;

	// METHODS

	// OPERATOR OVERLOADS

	void operator= (Land const&);
};

// Basic lands have one basic type and can tap for one kind of mana

class BasicLand : public Land
{
private :

public :

	// CONSTRUCTORS

	BasicLand();
	BasicLand(BasicLand const&);
	BasicLand(std::string const&, std::vector<bool> const&);

	// GETTERS

	LandType GetLandType() const;

	// METHODS

	virtual bool TapForMana(ManaType const);

	// OPERATOR OVERLOADS

	void operator= (BasicLand const&);
};

// Fetchlands cannot tap for mana; they can be sacrificed at the cost of 1 life to find a land of a given type in the deck

class Fetchland : public Land
{
private :

	std::vector<bool> m_canFind;
	bool m_hasConverted = false;

public :

	// CONSTRUCTORS

	Fetchland();
	Fetchland(Fetchland const&);
	Fetchland(std::string const&, std::vector<bool> const&);

	// GETTERS

	LandType GetLandType() const;

	// METHODS

	virtual bool TapForMana(ManaType const);
	void Convert(Land const&);

	// OPERATOR OVERLOADS

	void operator= (Fetchland const&);
};

// Life Taplands (eg. Blossoming Sands) enter the battlefield tapped, provide one life when they enter, and tap for one of two colours

class LifeTapland : public Land
{
private :

public :

	// CONSTRUCTORS

	LifeTapland();
	LifeTapland(LifeTapland const&);
	LifeTapland(std::string const&, std::vector<bool> const&);

	// GETTERS

	LandType GetLandType() const;

	// METHODS

	virtual bool TapForMana(ManaType const);

	// OPERATOR OVERLOADS

	void operator= (LifeTapland const&);
};

// Taplands (eg. Ashen Moor) enter the battlefield tapped and tap for one of two colours

class Tapland : public Land
{
private :

public :

	// CONSTRUCTORS

	Tapland();
	Tapland(Tapland const&);
	Tapland(std::string const&, std::vector<bool> const&);

	// GETTERS

	LandType GetLandType() const;

	// METHODS

	virtual bool TapForMana(ManaType const);

	// OPERATOR OVERLOADS

	void operator= (Tapland const&);
};

// Tangolands (eg. Cinder Glade) enter the battlefield tapped unless their controller has two or more basic lands in play. They have two
// basic land types (so can be fetched) and tap for one of two colours

// NOT CURRENTLY IMPLEMENTED

class Tangoland : public Land
{
private :

public :

	// CONSTRUCTORS

	Tangoland();
	Tangoland(Tangoland const&);
	Tangoland(std::string const&, std::vector<bool> const&);

	// GETTERS

	LandType GetLandType() const;
	
	// METHODS

	virtual bool TapForMana(ManaType const);

	// OPERATOR OVERLOADS

	void operator= (Tangoland const&);
};

#endif