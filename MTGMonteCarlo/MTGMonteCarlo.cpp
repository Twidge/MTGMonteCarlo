// MTGMonteCarlo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimulationController.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <future>

using namespace std;

const unsigned int G_NUMBER_OF_TRIALS = 100000;
const unsigned int G_TURNS_TO_CHECK = 4;
const bool G_ON_PLAY = true;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	unsigned int t_mana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};
	unsigned int t_secondMana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};
	unsigned int t_thirdMana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};

	const Card t_cardToCheck = Card("Jeskai Ascendancy", Enchantment, Mana(t_mana));
	const Card t_secondCardToCheck = Card("Rattleclaw Mystic", Creature, Mana(t_secondMana));
	const Card t_thirdCardToCheck = Card("Expedite", Instant, Mana(t_thirdMana));

	std::vector<Card> t_cardsToCheck{ t_cardToCheck, t_secondCardToCheck, t_thirdCardToCheck };

	float t_successfulTrials = 0;

	Player t_simPlayerOne = Player();
	Player t_simPlayerTwo = Player();
	t_simPlayerOne.ConstructDeck("decklist.txt");
	t_simPlayerTwo.ConstructDeck("decklist.txt");
	SimulationController t_simControllerOne = SimulationController(&t_simPlayerOne);
	SimulationController t_simControllerTwo = SimulationController(&t_simPlayerTwo);

	std::future<unsigned int> t_futureUIntOne =
		std::async(&SimulationController::RunAndSimulationLoop, &t_simControllerOne, t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY, G_NUMBER_OF_TRIALS / 2);
	std::future<unsigned int> t_futureUIntTwo =
		std::async(&SimulationController::RunAndSimulationLoop, &t_simControllerTwo, t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY, G_NUMBER_OF_TRIALS / 2);

	std::future_status t_futureOneStatus, t_futureTwoStatus;

	do
	{
		t_futureOneStatus = t_futureUIntOne.wait_for(std::chrono::milliseconds(100));
		t_futureTwoStatus = t_futureUIntTwo.wait_for(std::chrono::milliseconds(100));

	} while (t_futureOneStatus != std::future_status::ready || t_futureTwoStatus != std::future_status::ready);

	std::cout << "Number of trials: " << G_NUMBER_OF_TRIALS << ".\n";
	std::cout << "Successful trials: " << t_futureUIntOne.get() + t_futureUIntTwo.get() << ".\n";

	std::cin.get();

	return 0;
}