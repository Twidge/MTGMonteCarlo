#include "Mana.h"
#include <iostream>

// CONSTRUCTORS

Mana::Mana()
{
	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		mana[l_manaType] = 0;
	}
}

Mana::Mana(Mana const& otherMana)
{
	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		mana[l_manaType] = otherMana.mana[l_manaType];
	}
}

Mana::Mana(unsigned int manaTypes[G_MANA_TYPES])
{
	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		mana[l_manaType] = manaTypes[l_manaType];
	}
}

// GETTERS

unsigned int Mana::GetMana(ManaType colour) const
{
	return mana[colour];
}

// METHODS

void Mana::AddMana(unsigned int amount, ManaType colour)
{
	mana[colour] += amount;
}

void Mana::RemoveMana(unsigned int amount, ManaType colour)
{
	if (mana[colour] >= amount)
	{
		mana[colour] -= amount;
	}

	else
	{
		std::cout << "Error in Mana::RemoveMana(): cannot remove the amount of mana requested.\n";
	}
}

// OPERATOR OVERLOADS

void Mana::operator= (Mana const& otherMana)
{
	for (unsigned int l_manaType = 0; l_manaType < G_MANA_TYPES; l_manaType++)
	{
		mana[l_manaType] = otherMana.mana[l_manaType];
	}
}