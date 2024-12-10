#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "template/Card.h"
#include "template/Deck.h"
#include "template/Player.h"

int main()
{
	Deck drawDeck = Deck();
	Deck discardDeck = Deck();

	Player player1 = Player();
	Player player2 = Player();

	void playerTurn(Player & player, Player & opponent, Card & discard, Deck & discardDeck, Deck & drawDeck);
	void dealCards(Player & player, Deck & drawDeck);
	void clearScreen();
	void setPlayerName(Player & player);
	void checkDrawDeck(Deck & drawDeck);
	void checkRank(Card checkCard);
	void startGame(int& gameOption, Player & player1, Player & player2, Deck & drawDeck, Deck & discardDeck, Card &discardCard);
	void endGame(Player &winner, Player &loser, int &gameOption, string &replay);
	void homeScreen(int &gameOption);

	int gameOption = -1; //inavlid option to ensure user input
	Card discardCard = Card(1, "Diamonds");

	while (gameOption != 2) // as long as game hasnt quit, code will run
	{
		homeScreen(gameOption); // Presents the title to the user with menu options
		startGame(gameOption, player1, player2, drawDeck, discardDeck, discardCard);
	}
	
}

void clearScreen() //Clears console and outputs title
{
	system("cls");
	cout << R"(   _____                        _____ _       _     _       )" << endl;
	cout << R"( | |     _ __ __ _ _____   _  | |__   _  __ _| |__ | |_ ___ )" << endl;
	cout << R"( | |    | '__/ _` |_  / | | | |  __| | |/ _` | '_ \| __/ __|)" << endl;
	cout << R"( | |____| | | (_| |/ /| |_| | | |____| | (_| | | | | |_\__ \ )" << endl;
	cout << R"(  \_____|_|  \__,_/___|\__, | |______|_|\__, |_| |_|\__|___/ )" << endl;
	cout << R"(                        __/ |            __/ |              )" << endl;
	cout << R"(                       |___/            |___/               )" << endl;
	cout << "" << endl;
}

void homeScreen(int& gameOption) //Outputs main menu options
{
	clearScreen();
	cout << "Welcome to Crazy Eights! Input the option you wish to select below:" << endl;
	cout << "(0) Start" << endl;
	cout << "(1) Rules" << endl;
	cout << "(2) Quit" << endl;
	cin >> gameOption;
}

void dealCards(Player &player, Deck &drawDeck) //Deals players 7 cards
{
	for (int i = 0; i < 7; i++)
	{
		Card playerDrawnCard = drawDeck.getTopCard();
		player.addCard(playerDrawnCard);	
	}
}

void checkRank(Card checkCard) //Checks rank of cards and changes rank of face cards from a number to their title
{
	if (checkCard.getRank() == 1)
	{
		cout << "Ace of " << checkCard.getSuit() << endl;
	}
	else if (checkCard.getRank() == 11)
	{
		cout << "Jack of " << checkCard.getSuit() << endl;
	}
	else if (checkCard.getRank() == 12)
	{
		cout << "Queen of " << checkCard.getSuit() << endl;
	}
	else if (checkCard.getRank() == 13)
	{
		cout << "King of " << checkCard.getSuit() << endl;
	}
	else
	{
		cout << checkCard.toString() << endl;
	}
}

void setPlayerName(Player& player) //Sets player usernames
{
	string nameInput;
	cin >> nameInput;
	player.setName(nameInput);
}

void checkDrawDeck(Deck& drawDeck) //Fills draw deck with cards from the discard pile if it runs out
{
	if (drawDeck.isEmpty())
	{
		drawDeck.fillDeck();
		drawDeck.shuffle();
	}
}

void endGame(Player& winner, Player& loser, int& gameOption, string& replay)
{
	int pointsGained = loser.sumHand();
	winner.changeScoreBy(pointsGained);	//makes winner score the sum of opponents hand

	cout << winner.getName() << " has no cards remaining and has therefore won!" << endl;
	cout << "Better luck next time " << loser.getName() << "." << endl;
	cout << "" << endl;

	cout << "End scores:" << endl;
	cout << winner.getName() << ": " << winner.getScore() << endl;
	cout << loser.getName() << ": " << loser.getScore() << endl;
	cout << "" << endl;

	cout << "Do you want to replay? yes/no" << endl;
	cin >> replay;
	cout << "" << endl;

	if (replay == "yes")
	{
		cout << "Do you wish to clear existing scores or continue play? clear/continue" << endl;
		string replayOption;
		cin >> replayOption;

		if (replayOption == "clear") //resets player scores to 0
		{
			winner.setScore(0);
			loser.setScore(0);
		}

		winner.clearHand(); //clears player hands, keeping scores the same if the previous if loop isnt ran
		loser.clearHand();
		homeScreen(gameOption);
	}
	else if (replay == "no")
	{
		homeScreen(gameOption);
	}
}

void playerTurn(Player &player, Player &opponent, Card &discard, Deck &discardDeck, Deck &drawDeck)
{	
	bool playableCard = false;
	bool validInput = false;
	string inputOption;
	Card playerCard = Card(1, "Spades");
	int cardIndex;

	cout << player.getName() << "'s turn:" << endl;

	cout << "Card to match: ";
	checkRank(discard);
	cout << "" << endl;

	for (int i = 0; i < player.getHandSize(); i++) //outputs list of player hand
	{
		cout << "(" << i << ") " << "";
		playerCard = player.peekCard(i);
		checkRank(playerCard);
	}

	for (int i = 0; i < player.getHandSize(); i++) //repeats code to compare each card in hand to the top discard card
	{
		playerCard = player.peekCard(i);
		if (playerCard.getRank() == discard.getRank() || playerCard.getSuit() == discard.getSuit() || playerCard.getRank() == 8 ) // if playerCard matches discard card or is the crazy eight it can be played
		{
			playableCard = true;
		}
	}
	if (playableCard == true)
	{
		cout << "Enter the number of the card you would like to play or enter 'x' to pick up: " << endl;
		while(validInput == false)
		{
			cin >> inputOption;

			if (inputOption == "x")
			{
				player.addCard(drawDeck.getTopCard());	//adds draw deck card to player hand when user chooses to pick up a card
				cout << "You have picked up the " << "";
				checkRank(playerCard);
				validInput = true; //stops while loop
			}
			else
			{
				try 
				{
					cardIndex = stoi(inputOption); //converts string input to an integer

					if (cardIndex >= 0 && cardIndex < player.getHandSize()) 
					{
						playerCard = player.peekCard(cardIndex);
						if ((playerCard.getRank() == discard.getRank() || playerCard.getSuit() == discard.getSuit()) && playerCard.getRank() != 8) // if playerCard matches discard card or is the crazy eight it can be played
						{
							discardDeck.addCard(playerCard);	//adds selected player card to discard pile
							discard = discardDeck.getCard(discardDeck.getSize() - 1);

							cout << "You have placed the " << "";
							checkRank(discard);
							player.removeCard(cardIndex);
							validInput = true;
						}

						else if (playerCard.getRank() == 8)
						{
							cout << "You have played the crazy eight! Enter the name of the suit you wish to change to:" << endl;
							string suitChange;
							cin >> suitChange;

							discardDeck.addCard(playerCard);	//adds crazy eight card to discard pile
							playerCard = Card(8, suitChange);

							discardDeck.addCard(playerCard);	//adds changed suit to discard pile
							discard = discardDeck.getCard(discardDeck.getSize() - 1);
							player.removeCard(stoi(inputOption));
							validInput = true;
						}

						else if (playerCard.getRank() == 2)
						{
							cout << "You have played a +2! " << opponent.getName() << " has been dealt 2 extra cards!" << endl;

							discardDeck.addCard(playerCard);	//adds selected player card to discard pile
							discard = discardDeck.getCard(discardDeck.getSize() - 1);

							cout << "You have placed the " << "";
							checkRank(discard);
							player.removeCard(cardIndex);

							for (int i = 0; i < 1; i++) //loops to add 2 new cards to the opponents hand from the draw deck
							{
								opponent.addCard(drawDeck.getTopCard());
							}
							
							validInput = true;
						}
						else
						{
							cout << "Selected card is not playable. Please input a valid card number." << endl; //error when a user inputs an invalid card number but is still part of the index range
						}
					}
					else {
						cout << "Please input a valid card number within the specified range." << endl; //error when a user inputs an invalid card number that is not part of the index range
					}
				}
				catch (const invalid_argument)
				{
					cout << "Please input a valid card number or 'x' to pick up." << endl; //error when an invalid input is entered
				}
			}
		}
	}
	else
	{
		try
		{
			cout << "You cannot play a card. Enter 'x' to pick up:" << endl; //runs when a player physically has no matching cards to the discard card
			cin >> inputOption;
			if (inputOption == "x")
			{
				player.addCard(drawDeck.getTopCard());	//adds draw deck card to player hand
				cout << "You have picked up the " << player.peekCard(player.getHandSize() - 1).toString() << "." << endl;
				validInput = true;
			}
			else
			{
				cout << "Enter 'x' to pick up a card." << endl;
			}
		}
		catch (const invalid_argument)
		{
			cout << "You cannot play a card. Enter 'x' to pick up:" << endl; //error when an invalid input is entered
		}
	}
}
void startGame(int &gameOption, Player &player1, Player &player2, Deck &drawDeck, Deck &discardDeck, Card &discardCard)
{
	int returnHome = 0;
	string replay = "no";
	switch (gameOption) // Takes the gameOption previously stated and runs the code relating to the input option
	{
	case 0: //Starts game
	{
		clearScreen();
		cout << "Enter Player 1's name: ";
		setPlayerName(player1);

		cout << "Enter Player 2's name: ";
		setPlayerName(player2);

		drawDeck.shuffle();
		dealCards(player1, drawDeck);	//draws 7 cards to player 1's deck
		dealCards(player2, drawDeck); //draws 7 cards to player 2's deck

		discardCard = drawDeck.getTopCard();
		discardDeck.addCard(discardCard);	//Draws first card from the draw deck

		while (player1.getHandSize() != 0 && player2.getHandSize() != 0) //gameplay continues until a player has no cards
		{
			checkDrawDeck(drawDeck);
			clearScreen();
			playerTurn(player1, player2, discardCard, discardDeck, drawDeck);
			if (player1.getHandSize() == 0)
			{
				endGame(player1, player2, gameOption, replay);
			}
			clearScreen();
			playerTurn(player2, player1, discardCard, discardDeck, drawDeck);

			if(player2.getHandSize() == 0)
			{
				endGame(player2, player1, gameOption, replay);
			}
		}

		clearScreen(); 
		break;
	}
	case 1: //Outputs rules
	{
		clearScreen();
		cout << "The goal of Crazy Eights is to loose all cards from your hand." << endl;
		cout << "" << endl;
		cout << "Players begin with 7 cards each, dealt from the draw pile." << endl;
		cout << "On your turn, you will either pick up a card or place a card." << endl;
		cout << "" << endl;
		cout << "You can only place a card from your hand if either the card's " << endl;
		cout << "suit or rank match the card drawn the discard pile displayed" << endl;
		cout << "onscreen." << endl;
		cout << "" << endl;
		cout << "Any rank 8 cards can be played at any point in the game," << endl;
		cout << "regardless of suit or rank of the card being matched. The" << endl;
		cout << "eight will enable the player to change the suit of the card" << endl;
		cout << "card to be matched." << endl;
		cout << "" << endl;
		cout << "If you play any rank 2 cards, your oppenent will pick up 2" << endl;
		cout << "random cards from the draw deck." << endl;
		cout << "" << endl;
		cout << "If you cannot play a card, you must pick up from the draw deck." << endl;
		cout << "" << endl;
		cout << "The players turn then ends and the next player takes their turn." << endl;

		cout << "Enter '0' to return to the home page:" << endl;
		cin >> returnHome;

		while (returnHome != 0) //ensures correct input
		{
			cout << "Please enter '0' to return to the home menu" << endl;
			cin >> returnHome;
		}
		break;
	}
	case 2: //Exits game
	{
		cout << "Exiting Crazy Eights..." << endl;
		system("pause");

		break;
	}
	default:
		cout << "Invalid input. Returning to home screen." << endl; //If user inputs a value not listed within the case statements, an error statement will promt re-entry
		homeScreen(gameOption);
		break;
	}
}

