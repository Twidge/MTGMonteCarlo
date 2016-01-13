#ifndef LANDTYPES_CPP
#define LANDTYPES_CPP

#include "Landtypes.h"
#include "Mana.h"
#include <iostream>

/*
	*********
	LAND
	*********
*/

// CONSTRUCTORS

Land::Land() : Card(CardType::LandCard)
{
	m_canGen = std::vector<bool>(G_MANA_TYPES, false);

	m_basicTypes = std::vector<BasicType>();
}

Land::Land(Land const& land) : Card(land)
{
	m_canGen = land.m_canGen;

	m_basicTypes = land.m_basicTypes;
}

Land::Land(std::string const& name) : Card(name, CardType::LandCard)
{
	m_canGen = std::vector<bool>(G_MANA_TYPES, false);

	m_basicTypes = std::vector<BasicType>();
}

Land::Land(std::string const& name, std::vector<bool> const& manaItCanGenerate) : Card(name, CardType::LandCard, Mana())
{
	m_canGen = std::vector<bool>(G_MANA_TYPES);

	for (int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		m_canGen[l_manaType] = manaItCanGenerate[l_manaType];
	}

	m_basicTypes = std::vector<BasicType>();
}

// GETTERS

bool Land::CanGen(ManaType type) const
{
	return m_canGen[type];
}

LandType Land::GetLandType() const
{
	return m_landType;
}

// OPERATOR OVERLOADS

void Land::operator= (Land const& land)
{
	Card::operator=(land);

	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		m_canGen[l_manaType] = land.m_canGen[l_manaType];
	}

	m_basicTypes = land.m_basicTypes;
}

/*
	*********
	BASIC LAND
	*********
*/

// CONSTRUCTORS

BasicLand::BasicLand() : Land()
{
	m_landType = LandType::Basic;
}

BasicLand::BasicLand(BasicLand const& basicLand) : Land(basicLand)
{
	m_landType = basicLand.m_landType;
}

BasicLand::BasicLand(std::string const& name, std::vector<bool> const& manaItCanGenerate) : Land(name, manaItCanGenerate)
{
	unsigned int t_typesItCanGenerate = 0;

	m_landType = LandType::Basic;

	for (unsigned int l_manaType = 0; l_manaType < G_BASIC_TYPES; l_manaType++)
	{
		if (manaItCanGenerate[l_manaType])
		{
			if (t_typesItCanGenerate == 0)
			{
				m_basicTypes.push_back(static_cast<BasicType>(l_manaType));
			}

			t_typesItCanGenerate++;
		}
	}

	if (t_typesItCanGenerate > 1)
	{
		std::cout << "Error in BasicLand::BasicLand(string, const bool[]): attempting to create a basic land that generates more than one type of mana.\n";
	}
}

// GETTERS

LandType BasicLand::GetLandType() const
{
	return m_landType;
}

// METHODS

bool BasicLand::TapForMana(ManaType targetType)
{
	bool t_tapWasSuccessful = false;

	if (m_canGen[static_cast<unsigned int>(targetType)] && m_isTapped == false)
	{
		m_isTapped = true;
		t_tapWasSuccessful = true;
	}

	else if (m_isTapped == true)
	{
		std::cout << "Error in BasicLand::TapForMana(): land is already tapped.\n";
	}

	else
	{
		std::cout << "Error in BasicLand::TapForMana(): land cannot generate mana of type " << targetType << ".\n";
	}

	return t_tapWasSuccessful;
}

// OPERATOR OVERLOADS

void BasicLand::operator= (BasicLand const& basicLand)
{
	Land::operator=(basicLand);

	m_landType = basicLand.m_landType;
}

/*
	*********
	FETCHLAND
	*********
*/

// CONSTRUCTORS

Fetchland::Fetchland() : Land()
{
	m_canFind = std::vector<bool>(G_MANA_TYPES, false);

	m_landType = LandType::Fetch;
}

Fetchland::Fetchland(Fetchland const& fetch) : Land(fetch)
{
	m_canFind = fetch.m_canFind;	
	m_landType = fetch.m_landType;
	m_hasConverted = fetch.m_hasConverted;
}

Fetchland::Fetchland(std::string const& name, std::vector<bool> const& typesItCanFind)
	: Land(name)
{
	m_canFind = std::vector<bool>(G_MANA_TYPES);

	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		if (typesItCanFind[l_manaType])
		{
			m_canFind[l_manaType] = true;
		}

		else
		{
			m_canFind[l_manaType] = false;
		}
	}

	m_landType = LandType::Fetch;
}

// GETTERS

LandType Fetchland::GetLandType() const
{
	return m_landType;
}

// METHODS

bool Fetchland::TapForMana(ManaType targetType)
{
	std::cout << "Error in Fetchland::TapForMana(): Fetchland cannot tap for mana.\n";
	return false;
}

// OPERATOR OVERLOADS

void Fetchland::operator= (Fetchland const& fetch)
{
	Land::operator=(fetch);

	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		m_canFind[l_manaType] = fetch.m_canFind[l_manaType];
	}

	m_landType = fetch.m_landType;
	m_hasConverted = fetch.m_hasConverted;
}

/*
	*********
	LIFE TAPLAND
	*********
*/

// CONSTRUCTORS

LifeTapland::LifeTapland() : Land()
{
	m_landType = LandType::LifeTap;
}

LifeTapland::LifeTapland(LifeTapland const& lifetap) : Land(lifetap)
{
	m_landType = lifetap.m_landType;
}

LifeTapland::LifeTapland(std::string const& name, std::vector<bool> const& manaItCanGenerate) : Land(name, manaItCanGenerate)
{
	m_landType = LandType::LifeTap;
}

// GETTERS

LandType LifeTapland::GetLandType() const
{
	return m_landType;
}

// METHODS

bool LifeTapland::TapForMana(ManaType targetType)
{
	bool t_tapWasSuccessful = false;

	if (m_canGen[static_cast<unsigned int>(targetType)] && m_isTapped == false)
	{
		m_isTapped = true;
		t_tapWasSuccessful = true;
	}

	else if (m_isTapped == true)
	{
		std::cout << "Error in LifeTapland::TapForMana(): land is already tapped.\n";
	}

	else
	{
		std::cout << "Error in LifeTapland::TapForMana(): land cannot generate mana of type " << targetType << ".\n";
	}

	return t_tapWasSuccessful;
}

// OPERATOR OVERLOADS

void LifeTapland::operator= (LifeTapland const& lifetap)
{
	Land::operator=(lifetap);

	m_landType = lifetap.m_landType;
}

/*
	*********
	TAP LANDS
	*********
*/

// CONSTRUCTORS

Tapland::Tapland() : Land()
{
	m_landType = LandType::Tap;
}

Tapland::Tapland(Tapland const& tap) : Land(tap)
{
	m_landType = tap.m_landType;
}

Tapland::Tapland(std::string const& name, std::vector<bool> const& manaItCanGenerate) : Land(name, manaItCanGenerate)
{
	m_landType = LandType::Tap;
}

// GETTERS

LandType Tapland::GetLandType() const
{
	return m_landType;
}

// METHODS

bool Tapland::TapForMana(ManaType targetType)
{
	bool t_tapWasSuccessful = false;

	if (m_canGen[static_cast<unsigned int>(targetType)] && m_isTapped == false)
	{
		m_isTapped = true;
		t_tapWasSuccessful = true;
	}

	else if (m_isTapped == true)
	{
		std::cout << "Error in Tapland::TapForMana(): land is already tapped.\n";
	}

	else
	{
		std::cout << "Error in Tapland::TapForMana(): land cannot generate mana of type " << targetType << ".\n";
	}

	return t_tapWasSuccessful;
}

// OPERATOR OVERLOADS

void Tapland::operator= (Tapland const& tap)
{
	Land::operator=(tap);

	m_landType = tap.m_landType;
}

#endif