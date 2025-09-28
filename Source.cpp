#include<iostream>
using namespace std;
enum enChoice{Storn=1, Paper=2, Scissor=3};
enum enWiner{player=1, computer=2, draw=3};

struct stRounds
{
	short round;
	enChoice player;
	enChoice computer;
	enWiner winer;
	string winername;
};
struct stGame
{
	short howrounds = 0;
	short winplayer, wincomputer;
	short drawtimes;
	string namewiner;
};

short ReadHowRounds(string massage)
{
	short numberrounds = 0;
	do {
		cout << massage << endl;
		cin >> numberrounds;
	} while (numberrounds > 10 || numberrounds <= 0);
	return numberrounds;
}

enChoice ReadChoicePlayer(string massage)
{
	int read;
	do {
		cout << massage << endl;
		cin >> read;
	} while (read>3||read<1);
	return (enChoice)read;
}

int RandomNumber(int from, int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}

enChoice GetRandomNumber()
{
	return (enChoice)RandomNumber(1, 3);
}

enWiner WhoWon(stRounds info)
{
	if (info.computer == info.player)
	{
		return enWiner::draw;
	}
	switch (info.player)
	{
	case Storn:
		if (info.computer == enChoice::Paper) return enWiner::computer;
		break;
	case Paper: if(info.computer== enChoice::Scissor) return enWiner::computer;
		break;
	case Scissor:if (info.computer == enChoice::Storn) return enWiner::computer;
		break;
	default:
		break;
	}
	return enWiner::player;
}

string GetNameWiner(short number)
{
	string win[3] = { "player", "computer", "draw" };
	return win[number - 1];
}

string Choice(short number)
{
	string choice[3] = { "Storn", "Paper", "Scisor" };
	return choice[number - 1];
}

void PrintRoundResult(stRounds info)
{
	cout << "__________________Round [" << info.round << "]__________________\n" << endl;
	cout << "Player1 Choice: " << Choice(info.player) << endl;
	cout << "Computer Choice: " << Choice(info.computer) << endl;
	cout << "Round Winner: " << info.winername << endl;
	cout << "______________________________________________\n" << endl;
}

string WhoWonGame(short contp, short contc)
{
	if (contp > contc)
		return "player";
	else if (contp < contc)
		return "computer";
	else
		return "draw";
}

stGame FillResultGame(stRounds info, short contplayer, short contcomputer, short contdraw)
{
	stGame result;
	result.howrounds = info.round;
	result.winplayer = contplayer;
	result.wincomputer = contcomputer;
	result.drawtimes = contdraw;
	result.namewiner = WhoWonGame(contplayer, contcomputer);
	return result;
}

void ChangeScreen(stRounds info)
{
	if (info.winername == "player")
		system("color 2F");
	else if (info.winername == "computer")
		system("color 4F");
	else
		system("color 6F");
}

stGame PlayGame(short howrounds)
{
	stRounds info;
	short contplayer=0, contcomputer=0, contdraw=0;
	for (int round = 1; round <= howrounds; round++)
	{
		cout << "Round[" << round << "] begins:" << endl;
		info.round = round;
		info.player = ReadChoicePlayer("Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors?");
		info.computer = GetRandomNumber();
		info.winer = WhoWon(info);
		info.winername = GetNameWiner(info.winer);
		
		if (info.winername == "player")
			++contplayer;
		else if (info.winername == "computer")
			++contcomputer;
		else
			++contdraw;
		ChangeScreen(info);


		PrintRoundResult(info);
	}
	return FillResultGame( info,contplayer,contcomputer,contdraw);
}

string Tabs(int number)
{
	string t = "";
	for (int i = 0; i < number; i++)
	{
		t += "\t";
	}
	return t;
}

void PrintGameOver()
{
	cout << Tabs(3) << "__________________________________________________________________________" << endl;
	cout<<Tabs(3) << "                            +++ G a m e   O v e r +++                       " << endl;
	cout<< Tabs(3) << "___________________________________________________________________________" << endl;
}

void PrintGameResult(stGame rgame)
{
	cout << endl;
	cout << Tabs(3) << "_______________________________[ Game Results ]____________________________" << endl;
	cout << Tabs(3) << "Game Rounds            : " << rgame.howrounds << endl;
	cout << Tabs(3) << "Player1 won times      : " << rgame.winplayer << endl;
	cout << Tabs(3) << "Computer won times     : " << rgame.wincomputer << endl;
	cout << Tabs(3) << "Draw times             : " << rgame.drawtimes << endl;
	cout << Tabs(3) << "Final Winner           : " << rgame.namewiner << endl;
	cout << Tabs(3) << "___________________________________________________________________________" << endl;
}

void Resturt()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char agiangame='Y';
	do {
		Resturt();
		stGame gameresult=PlayGame(ReadHowRounds("How Many Rounds 1 to 10?"));
		PrintGameOver();
		PrintGameResult(gameresult);
		cout << "Do you want to play again? Y/N?" << endl;
		cin >> agiangame;
	} while (agiangame == 'y' || agiangame == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}