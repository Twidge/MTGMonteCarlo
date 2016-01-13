#ifndef MANA_H
#define MANA_H

enum ManaType
{
	Colourless,
	White,
	Blue,
	Black,
	Red,
	Green,
	AnyColour
};

const unsigned int G_MANA_TYPES = 7;

class Mana
{
private :

	unsigned int mana[G_MANA_TYPES];

public :

	// CONSTRUCTORS

	Mana();
	Mana(Mana const&);
	Mana(unsigned int[G_MANA_TYPES]);

	// GETTERS

	unsigned int GetMana(ManaType) const;

	// METHODS

	void AddMana(unsigned int, ManaType);
	void RemoveMana(unsigned int, ManaType);

	// OPERATOR OVERLOADS

	void operator= (Mana const&);
};

#endif