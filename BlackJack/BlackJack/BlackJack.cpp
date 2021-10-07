#include <iostream>
#include<windows.h>
#include <time.h>
using namespace std;


//initialize variables
int arrayOfCards[52];
int position = 0;

int dealerCards[10];
int playerCards[10];

double playerMoney = 1000;
double playerBet;
char playerAnswer;

//initialize functions;
void PopulateArray();
void StartOfGame();
int GetRandomCard();
int CalculatePlayerCardSum();
int CalculateDealerCardSum();
void PlayerDrawing();
void DealerDrawing();
void CalculateEndScores();
void PlayerWins(bool isBlackJack = false);
void DealerWins();
void Tie();
void Restart();

int main()
{
	srand(time(0));
	PopulateArray();


	cout << "Welcome to BlackJack C++ game. \n";
	Sleep(1000);

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

	//all cards with value of 10
	for (int x = 1; x <= 16; x++)
	{
		arrayOfCards[position++] = 10;
	}

	//all cards with value of 11 or 1 (Aces)
	for (int z = 1; z <= 4; z++)
	{
		arrayOfCards[position++] = 11;
	}
}

void StartOfGame()
{
	cout <<	"Please provide you bet. You have " << playerMoney << "EUR now. \n";
	cin >> playerBet;

	while (playerBet > playerMoney)
	{
		cout << "You don't have that amount of money left. Provide a new bet. \n";
		cin >> playerBet;
	}

	cout << "Your bet is " << playerBet << "EUR. \n";
	playerMoney -= playerBet;

	playerCards[0] = GetRandomCard();
	playerCards[1] = GetRandomCard();
	dealerCards[0] = GetRandomCard();
	dealerCards[1] = GetRandomCard();

	cout << "Dealing cards now: \n";
	Sleep(1500);
	cout << "Your first card is: " << playerCards[0] << "\n";
	Sleep(1500);
	cout << "Dealer's first card is: " << dealerCards[0] << "\n";
	Sleep(1500);
	cout << "Your second card is: " << playerCards[1] << "\n";
	Sleep(1500);
	cout << "Dealer's second card is: X \n";
	Sleep(1500);

	int pCardSum = CalculatePlayerCardSum();
	int hCardSum = CalculateDealerCardSum();

	if (pCardSum == 21 && hCardSum == 21)
	{
		Tie();
		return;
	}
	else if (pCardSum == 21)
	{
		//player wins
		PlayerWins(true);
		return;
	}
	else if (hCardSum == 21)
	{
		//house wins
		cout << "Dealer's second card is: " << dealerCards[1] << " \n";
		DealerWins();
		return;
	}
	
	//if 2 Aces
	if (pCardSum == 22)
	{
		playerCards[1] = 1;
	}
	if (hCardSum == 22)
	{
		dealerCards[1] = 1;
	}
	
	PlayerDrawing();
	if (CalculatePlayerCardSum() > 21)
	{
		cout << "You bust. \n";
		DealerWins();
		return;
	}

	DealerDrawing();
}

void PlayerDrawing()
{
	cout << "Your sum of cards for now is: " << CalculatePlayerCardSum() << "\nWould you like another card? (Y/N) \n";
	cin >> playerAnswer;

	while (playerAnswer == 'Y')
	{
		for (int i = 0; i < 10; i++)
		{
			if (playerCards[i] == 0)
			{
				int playerSum = CalculatePlayerCardSum();
				playerCards[i] = GetRandomCard();
				if (playerCards[i] == 11 && playerSum > 10)
				{
					playerCards[i] = 1;
				}
				cout << "You drew: " << playerCards[i] << "\n";
				Sleep(1500);

				playerSum = CalculatePlayerCardSum();
				cout << "Your sum of cards for now is: " << playerSum << "\n";
				Sleep(1500);
				if (playerSum > 21)
				{
					DealerWins();
					return;
				}
				break;
			}
		}

		cout << "Would you like another card ? (Y / N) \n";
		cin >> playerAnswer;
	}


}

void DealerDrawing()
{
	cout << "Dealer's second card is: " << dealerCards[1]<<  "\n";
	Sleep(1500);

	cout << "Dealer's sum of cards is: " << CalculateDealerCardSum() << "\n";
	Sleep(1500);

	while (CalculateDealerCardSum() < 17)
	{
		cout << "Dealer's total sum of cards is less than 17. Drawing.\n";
		Sleep(1500);
		for (int i = 0; i < 10; i++)
		{
			if (dealerCards[i] == 0)
			{
				int dealerSum = CalculateDealerCardSum();
				dealerCards[i] = GetRandomCard();
				if (dealerCards[i] == 11 && dealerSum > 10)
				{
					dealerCards[i] = 1;
				}
				cout << "Dealer drew: " << dealerCards[i] <<  "\n";
				Sleep(1500);

				dealerSum = CalculateDealerCardSum();
				cout << "Dealer's sum of cards for now is: " << dealerSum << "\n";
				Sleep(1500);
				if (dealerSum > 21)
				{
					cout << "Dealer bust. \n";
					PlayerWins();
					return;
				}
				break;
			}
		}
	}
	CalculateEndScores();
}

void PlayerWins(bool isBlackJack)
{
	cout << "You win! \n";
	if (isBlackJack)
	{
		playerMoney += (2 * playerBet) + (playerBet / 2);
	}
	playerMoney += (2 * playerBet);
	cout << "Your total amount of money is: " << playerMoney << "\n";
	Restart();
}

void DealerWins()
{
	cout << "You lost! \n";
	cout << "Your total amount of money is: " << playerMoney << "\n";
	Restart();
}

void Tie()
{
	cout << "Tie! \n";
	playerMoney += playerBet;
	cout << "Your total amount of money is: " << playerMoney << "\n";
	Restart();

}


void Restart()
{
	playerBet = 0;
	
	for (int i = 0; i < 10; i++)
	{
		playerCards[i] = 0;
		dealerCards[i] = 0;
	}
	position = 0;
	PopulateArray();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	StartOfGame();
}

void CalculateEndScores()
{
	int dealerEndScore = CalculateDealerCardSum();
	int playerEndScore = CalculatePlayerCardSum();

	if (playerEndScore > dealerEndScore)
	{
		PlayerWins();
	}
	else if (playerEndScore < dealerEndScore)
	{
		DealerWins();
	}
	else
	{
		Tie();
	}
}

int CalculatePlayerCardSum()
{
	int pCardSum = 0;
	for (int i = 0; i < 10; i++)
	{
		pCardSum += playerCards[i];
	}

	return pCardSum;
}

int CalculateDealerCardSum()
{
	int hCardSum = 0;
	for (int i = 0; i < 10; i++)
	{
		hCardSum += dealerCards[i];
	}

	return hCardSum;
}

int GetRandomCard()
{
	int randomCardIndex = rand() % 52;
	//when a card is alredy drawn - replace it with -1
	while (arrayOfCards[randomCardIndex] == -1)
	{
		randomCardIndex = rand() % 52;
	}

	int chosenCard = arrayOfCards[randomCardIndex];
	arrayOfCards[randomCardIndex] = -1;

	return chosenCard;
}