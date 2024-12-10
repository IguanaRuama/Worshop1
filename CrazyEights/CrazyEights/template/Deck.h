#pragma once
#include <vector>
#include <string>
#include "Card.h"

using namespace std;

/**
 * @brief Deck class represents a collection of cards in a vector format. 
 * Intended to represent a deck, however can be used for stock piles, discard piles, and other uses.
 */
class Deck
{
private:
	/**
	 * Vector of Card objects. Private, so must be accessed through indirectly through functions.
	 */
	vector<Card> deck_vector;

public:
	/**
	 * Constructor to make a new deck. Pre-fills the deck with ordered cards by default.
	 * Also sets the seed for random number generation (required for shuffling the deck, see shuffle() function). Current time is used for seed (see https://en.cppreference.com/w/cpp/chrono/c/time)
	 */
	Deck();

	/**
	 * Gets the size of the deck.
	 * \return The number of cards in the deck.
	 */
	int getSize();

	/**
	 * Returns true/false depending on whether there are any cards in the deck.
	 * \return boolean flag of if the deck is empty.
	 */
	bool isEmpty();

	/**
	 * Shuffles the deck into a pseudo-random order. 
	 * Uses the current time to set the seed for shuffle algorithm. See constructor documentation for more information on this.
	 */
	void shuffle();

	/**
	 * Removes all cards from the deck.
	 */
	void clear();

	/**
	 * Fills the deck with all 52 cards. Does not shuffle the deck.
	 */
	void fillDeck();

	/**
	 * Adds a new card to the deck. Card is placed at the back of the deck vector.
	 * \param new_card New card object to be added to the deck.
	 */
	void addCard(Card new_card);

	/**
	 * Returns the card at the top of deck. Will return the last card in the vector. Important to note is the card will not be removed from the deck.
	 * \return Card object of the top card in the deck. 
	 */
	Card peekTopCard();

	/**
	 * Returns the card at the given index. Important to note is the card will not be removed from the deck.
	 * \param index The index of the desired card.
	 * \return Card object of the card at the given index.
	 */
	Card peekCard(int index);

	/**
	 * Removes and returns the card at the top of the deck. Will return the last card in the vector. Important to note is the card will be removed from the deck.
	 * \return Card object of the top card in the deck.
	 */
	Card getTopCard();

	/**
	 * Removes and returns the card at the given index. Important to note is the card will be removed from the deck.
	 * \param index The index of the desired card.
	 * \return Card object of the card at the given index.
	 */
	Card getCard(int index);
	/**
	 * Removes the card at the given index from the deck. Does not return the removed card.
	 * \param index The index of the desired card to remove.
	 */
	void removeCard(int index);

};

