#include<iostream>
#include<string>
using namespace std;
enum enPlay{stone=1, paper=2, scissor=3};

struct VaribleGame {
	int player=0 , computer=0;
	int winplayer = 0, wincomputer = 0, draw = 0;
	string winer;
};

int ReadPositiveNumber(string massage)
{
	int number;
	do {
		cout << massage << endl;
		cin >> number;
	} while (number < 0);
	return number;
}

int RandomNumber(int from, int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}

string CheckWiner(int numberplayer, int numbercomputer)
{
	if (numbercomputer == numberplayer)
		return "draw";
	switch (numberplayer)
	{
	case stone:
	{
		if (numbercomputer != 3)
			return "computer";
		else
			return "player";
	}
		break;
	case paper:
	{
		if (numbercomputer == 3)
			return "computer";
		else
			return "player";
	}
		break;
	case scissor:
	{
		if (numbercomputer != 1)
			return "player";
		else
			return "computer";
	}
		break;
	default:
		break;
	}
}

void CheckEnter(int number)
{
	switch (number)
	{
	case stone:cout << "Choice: Stone" << endl;
		break;
	case paper:cout << "Choice: Paper" << endl;
		break;
	case scissor:cout << "Choice: Scissor" << endl;
		break;
	default:
		break;
	}
}

void PrintResultRound(VaribleGame var)
{
	cout << "Player1 "; CheckEnter(var.player);
	cout << "Computer "; CheckEnter(var.computer);
	cout << "Round Winner : [" << var.winer << "]" << endl;
}

void ChanageScreen(string win)
{
	if (win == "computer")
		system("color 4F");
	else if (win == "player")
		system("color 2F");
	else
		system("color 6F");
}

void CounterWin(VaribleGame& count)
{
	if (count.winer == "player")
		 count.winplayer+=1;
	else if (count.winer == "computer")
		  count.wincomputer+=1;
	else
		 count.draw+=1;
}

void ManageRound(int count, VaribleGame& round)
{
	round.computer = RandomNumber(1, 3);
	round.player = ReadPositiveNumber("Your Choice: [1]:stone, [2]:Paper, [3]:Scissor ? ");
	round.winer=CheckWiner(round.player, round.computer);
	cout << "____________________________Round [" << count +1 << "]_______________________\n" << endl;
	PrintResultRound(round);
	cout << "_____________________________________________________________" << endl;
	ChanageScreen(round.winer);
	CounterWin(round);
}

void RepetRount(int round , VaribleGame& vargame)
{
	for (int i = 0; i < round; i++)
	{
		cout << "Round [" << i + 1 << "] begins " << endl;
		ManageRound(i ,vargame);
	}
	
}

void Space()
{
	cout << "\n \n";
	cout << "\t \t \t \t_____________________________________________________________________________________" << endl;
	cout << "\n \n";
}

void PrintResultGame(int counter, VaribleGame& result)
{
	Space();
	cout << "\t \t \t \t \t \t \t \t +++ G a m e  O v e r +++ " << endl;
	Space();
	cout << "\t \t \t \t______________________________________[ Game Results ]_______________________________" << endl;
	cout << "\n \n";
	cout << "\t \t \t \t Game Rounds \t: " << counter << endl;
	cout << "\t \t \t \t Game Player1 won times  : " << result.winplayer << endl;
	cout << "\t \t \t \t Game Computer won times  : " << result.wincomputer << endl;
	cout << "\t \t \t \t Draw times \t : " << result.draw << endl;
	cout << "\t \t \t \t Final Winner \t  : " <<result.winer<< endl;
	Space();
}
int main()
{
	srand((unsigned)time(NULL));
	char end;
	do {
	int round = ReadPositiveNumber("How Many Rounds 1 to 10? ");
	VaribleGame var;
	RepetRount(round,var);
	PrintResultGame(round, var);
	cout << "Do you want to play again? Y/N?" << endl;
	cin >> end;
	if (end == 'Y' || end == 'y')
	{
		system("cls");
		system("color 0F");
	}
		
	} while (end!='N'||end!='n');
	return 0;
}