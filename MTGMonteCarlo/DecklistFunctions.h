#ifndef DECKLISTFUNCTIONS_H
#define DECKLISTFUNCTIONS_H

#include "Card.h"
#include "Landtypes.h"
#include <cctype>
#include <vector>

std::vector<Card> GetDecklist(std::vector<Card>, std::string, int);
void PrintDecklist(std::vector<Card>, int);
void PrintMana(Mana&);
void CleanArray(char[], int);

#endif