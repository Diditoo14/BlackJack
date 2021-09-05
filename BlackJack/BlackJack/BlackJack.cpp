#include <iostream>
#include<windows.h>
using namespace std;


//initialize variables
int arrayOfCards[52];
int position = 0;

int hCard1;
int hCard2;

int pCard1;
int pCard2;

int hCardSum;
int pCardSum;

int playerMoney = 1000;
int playerBet;
char playerAnswer;

//initialize functions;
void PopulateArray();
void StartOfGame();
int GetRandomCard();

int main()
{
	PopulateArray();
	StartOfGame();

}

void PopulateArray()
{
	for (int i = 2; i <= 9; i++)
	{
		//adds all cards from 2 to 9, 4 times
		for (int y = 1; y <= 4; y++)
		{
			arrayOfCards[position++] = i;
		}
	}

	for (int x = 1; x <= 16; x++)
	{
		arrayOfCards[position++] = 10;
	}

	for (int z = 1; z <= 4; z++)
	{
		arrayOfCards[position++] = 11;
	}
}

void StartOfGame()
{
	cout << "Welcome to BlackJack C++ game. \n";
	Sleep(1000);
	cout <<	"Please provide you bet. You have " << playerMoney << "EUR now. \n";
	cin >> playerBet;

	while (playerBet > playerMoney)
	{
		cout << "You don't have that amount of money left. Provide a new bet. \n";
		cin >> playerBet;
	}

	cout << "Your bet is " << playerBet << "EUR. \n";
	playerMoney -= playerBet;

	pCard1 = GetRandomCard();
	pCard2 = GetRandomCard();
	hCard1 = GetRandomCard();
	hCard2 = GetRandomCard();

	cout << "Dealing cards now: \n";
	Sleep(1500);
	cout << "Your first card is: " << pCard1 << "\n";
	Sleep(1500);
	cout << "Dealer's first card is: " << hCard1 << "\n";
	Sleep(1500);
	cout << "Your second card is: " << pCard2 << "\n";
	Sleep(1500);
	cout << "Dealer's second card is: X \n";
	Sleep(1500);

	pCardSum = pCard1 + pCard2;
	hCardSum = hCard1 + hCard2;

	// check if both sums == 21; - > return bet
	// check if pCardSum == 21; - > player gets 150% bet
	// check if hCardSum == 21; - > player lose bet
	// check if card1 and 2 are 11; -> second one is = 1

	if (pCardSum == 21 && hCardSum == 21)
	{
		//tie
		return;
	}
	else if (pCardSum == 21)
	{
		//player wins
		return;
	}
	else if (hCardSum == 21)
	{
		// house wins
		return;
	}
	else if (pCardSum == 22)
	{
		pCard2 = 1;
	}
	else if (hCardSum == 22)
	{
		hCard2 = 1;
	}
	
	cout << "Your sum of cards for now is: " << pCard1 + pCard2 << "\nWould you like another card? \n";
	cin >> playerAnswer;


}

int GetRandomCard()
{
	int randomCardIndex = rand() % 52;
	while (arrayOfCards[randomCardIndex] == -1)
	{
		randomCardIndex = rand() % 52;
	}

	int chosenCard = arrayOfCards[randomCardIndex];
	arrayOfCards[randomCardIndex] = -1;

	return chosenCard;
}