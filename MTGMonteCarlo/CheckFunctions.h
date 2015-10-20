#ifndef CHECKFUNCTIONS_H
#define CHECKFUNCTIONS_H

#include "Card.h"
#include <vector>

bool CheckIfManaFor(const Card&, std::vector<Card>);
std::vector<std::vector<char>> ConstructAllManaStrings(std::vector<std::vector<char>>, std::vector<char>, std::vector<std::vector<char>>, std::vector<char>, int);
void DisplayAllManaStrings(std::vector<std::vector<char>>);
bool CheckIfStringHasMana(const Card&, std::vector<char>, ManaTypes);

std::vector<char> StringLand(const Card&);

std::vector<int> RefreshLands(int);

#endif