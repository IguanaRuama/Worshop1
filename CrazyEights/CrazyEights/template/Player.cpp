#include "Player.h"

Player::Player()
{
	this->name = "Unamed Player";
	this->hand = {};
	this->score = 0;
}

string Player::getName()
{
	return this->name;
}

void Player::setName(string new_name)
{
	this->name = new_name;
}

int Player::getHandSize()
{
	return this->hand.size();
}

vector<Card> Player::getHand()
{
	return this->hand;
}

void Player::clearHand()
{
	this->hand.clear();
}

Card Player::peekCard(int index)
{
	return this->hand[index];
}

bool Player::isEmpty()
{
	return this->hand.empty();
}

Card Player::getCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card tmp_card = this->hand[index];
	this->hand.erase(this->hand.begin() + index);
	return tmp_card;
}

void Player::addCard(Card new_card)
{
	this->hand.push_back(new_card);
}

void Player::removeCard(int index)
{
	this->hand.erase(this->hand.begin() + index);
}

int Player::sumHand()
{
	int total = 0;
	for (Card c : this->hand) {
		total += c.getRank();
	}

	return total;
}

void Player::outputHand()
{
	//Iterate through each card in hand and output toString for each one
	for (Card c : this->hand) {
		cout << c.toString() << endl;
	}
}

void Player::changeScoreBy(int toAdd)
{
	this->score += toAdd;
}

void Player::setScore(int newScore)
{
	this->score = newScore;
}

int Player::getScore()
{
	return this->score;
}
