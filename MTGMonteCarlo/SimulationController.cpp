#include "SimulationController.h"
#include "Player.h"
#include "Card.h"

// CONSTRUCTORS

SimulationController::SimulationController()
{
	m_tester = new Player();
}

SimulationController::SimulationController(SimulationController const& controller)
{
	m_tester = new Player();
	*m_tester = *controller.m_tester;
}

SimulationController::SimulationController(const Player* tester)
{
	m_tester = new Player();
	*m_tester = *tester;
}

// DESTRUCTOR

SimulationController::~SimulationController()
{
	delete m_tester;
}

// OPERATOR OVERLOADS

void SimulationController::operator= (SimulationController const& controller)
{
	delete m_tester;
	m_tester = new Player();
	*m_tester = *controller.m_tester;
}

// METHODS

bool SimulationController::RunSimulation(Card const& cardToPlay, unsigned int onOrBeforeThisTurn, bool playFirst)
{
	bool t_simulationSuccessful = false;

	// Reset the simulation to the base state

	m_tester->ResetSimulation();

	// Determine starting hand

	m_tester->DetermineStartingHand(playFirst);

	// Draw extra cards to bring the hand up to the size it would be on the last turn the card can be played on

	for (unsigned int l_cardsDrawn = 0; l_cardsDrawn < onOrBeforeThisTurn - 1; l_cardsDrawn++)
	{
		m_tester->DrawCard();
	}

	// Populate land vector

	m_tester->PopulateLandVector();

	// Determine if the card can be played using the lands in the land vector

	if (m_tester->CheckMana(cardToPlay) && m_tester->CheckCardInHand(cardToPlay))
	{
		t_simulationSuccessful = true;
	}

	return t_simulationSuccessful;
}

bool SimulationController::RunOrSimulation(std::vector<Card> const& cardsToPlay, unsigned int onOrBeforeThisTurn, bool playFirst)
{
	bool t_simulationSuccessful = false;

	// Reset the simulation to the base state

	m_tester->ResetSimulation();

	// Determine starting hand

	m_tester->DetermineStartingHand(playFirst);

	// Draw extra cards to bring the hand up to the size it would be on the last turn the card can be played on

	for (unsigned int l_cardsDrawn = 0; l_cardsDrawn < onOrBeforeThisTurn - 1; l_cardsDrawn++)
	{
		m_tester->DrawCard();
	}

	// Populate land vector

	m_tester->PopulateLandVector();

	// Determine if one of the cards can be played using the lands in the land vector

	for (unsigned int l_cardInVector = 0; l_cardInVector < cardsToPlay.size(); l_cardInVector++)
	{
		if (m_tester->CheckMana(cardsToPlay[l_cardInVector]) && m_tester->CheckCardInHand(cardsToPlay[l_cardInVector]))
		{
			t_simulationSuccessful = true;
			break;
		}
	}

	return t_simulationSuccessful;
}

bool SimulationController::RunAndSimulation(std::vector<Card> const& cardsToPlay, unsigned int onOrBeforeThisTurn, bool playFirst)
{
	bool t_simulationSuccessful = true;

	// Reset the simulation to the base state

	m_tester->ResetSimulation();

	// Determine starting hand

	m_tester->DetermineStartingHand(playFirst);

	// Draw extra cards to bring the hand up to the size it would be on the last turn the card can be played on

	for (unsigned int l_cardsDrawn = 0; l_cardsDrawn < onOrBeforeThisTurn - 1; l_cardsDrawn++)
	{
		m_tester->DrawCard();
	}

	// Populate land vector

	m_tester->PopulateLandVector();

	// Determine if all of the cards can be played using the lands in the land vector

	for (unsigned int l_cardInVector = 0; l_cardInVector < cardsToPlay.size(); l_cardInVector++)
	{
		if (!m_tester->CheckMana(cardsToPlay[l_cardInVector]) || !m_tester->CheckCardInHand(cardsToPlay[l_cardInVector]))
		{
			t_simulationSuccessful = false;
			break;
		}
	}

	return t_simulationSuccessful;
}