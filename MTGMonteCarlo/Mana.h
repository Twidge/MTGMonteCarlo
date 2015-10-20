#ifndef MANA_H
#define MANA_H

enum ManaTypes {colourless, white, blue, black, red, green};

class Mana
{
private :

	int mana[6];

public :

	Mana(int, int, int, int, int, int);
	Mana();
	void AddMana(int, char);

	int GetMana(int) const;
	int GetMana(ManaTypes) const;
};

#endif