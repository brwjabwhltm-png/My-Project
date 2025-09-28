#include<iostream>
using namespace std;

enum enlevel{Easy=1, Med=2, Hard=3, Mix=4};
enum enOprator{Add=1, Sub=2, Mult=3, Div=4, Max=5};

struct stQuestions
{
	short howmanyquestions;
	enlevel levelquestion;
	enOprator opratorquestion;
	short answer;
	short correctanswer;
	short firstnumber, sacandnumber;
	bool iscorrect;
};
struct stGameResult
{
	stQuestions Questions[100];
	short numberofquestions;
	enlevel levelGame;
	enOprator opratorquestion;
	short countrigth=0,countworng=0;
	bool ispass;
};

int ReadHowManyQuestions(string massage)
{
	int number;
	do {
		cout << massage << endl;
		cin >> number;
	} while (number<1||number>10);
	return number;
}

enlevel ReadLevelQuestion(string massage)
{
	int level;
	do {
		cout << massage << endl;
		cin >> level;
	} while (level>4||level<1);
	return (enlevel)level;
}

enOprator ReadOpratorQuestion(string massage)
{
	int oprator;
	do {
		cout << massage << endl;
		cin >> oprator;
	} while (oprator > 5 || oprator < 1);
	return (enOprator)oprator;
}

int RandomNumber(int from, int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}

string GetOprator(enOprator p)
{
	switch (p)
	{
	case Add:return "+";
		break;
	case Sub: return "-";
		break;
	case Mult:return "*";
		break;
	case Div:return "/";
		break;
	default:
		break;
	}
}

int ReadNumber()
{
	int number;
	cin >> number;
	return number;
}

void ChangeScreen(bool correct)
{
	if (correct)
		system("color 2F");
	else
		system("color 4F");
}

void IsAnsswerCorrect(stGameResult& answer,short a)
{
	answer.Questions[a].iscorrect = (answer.Questions[a].answer == answer.Questions[a].correctanswer);
	if (answer.Questions[a].iscorrect)
	{
		cout << "Right Answer :)" << endl;
		answer.countrigth+=1;
	}
	else
	{
		cout << "Worng Answer :(" << endl;
		cout << "The correct answer is " <<answer.Questions[a].correctanswer<<endl;
		answer.countworng+=1;
	}
	ChangeScreen(answer.Questions[a].iscorrect);
}

string Choice(short nlevel)
{
	string choice[3] = { "Easy", "Med", "Hard" };
	return choice[nlevel - 1];
}

string ChoiceOprator(short optype)
{
	string choice[5] = { "Add", "Sub", "Mult", "Div","Mix"};
	return choice[optype - 1];
}

string IsPassOrNot(bool is)
{
	if (is)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintGameResult(stGameResult gameresult)
{
	cout << "____________________________________________\n" << endl;
	cout << " Final Results is " << IsPassOrNot(gameresult.ispass) << endl;
	cout << "____________________________________________\n" << endl;

	cout << "\n\nNumber Of Questions       : " << gameresult.numberofquestions << endl;
	cout << "Questions level           : " << Choice(gameresult.levelGame) << endl;
	cout << "OpType                    : " << ChoiceOprator(gameresult.opratorquestion) << endl;
	cout << "Number of Right Answer    : " << gameresult.countrigth << endl;
	cout << "Number of Worng Answer    : " << gameresult.countworng << endl;
	cout << "____________________________________________\n" << endl;
}

void PrintQuestion(stGameResult Quize,short counter) 
{
	cout << "Question [" << counter + 1 << "/" << Quize.numberofquestions << "]" << endl;
	cout << "\n" << Quize.Questions[counter].firstnumber << endl;
	cout << Quize.Questions[counter].sacandnumber << " " << GetOprator(Quize.Questions[counter].opratorquestion) << endl;
	cout << "____________" << endl;
}

void AskQuestion(stGameResult& Quize)
{
	
	for (short i = 0; i < Quize.numberofquestions; i++)
	{
		PrintQuestion(Quize, i);
		Quize.Questions[i].answer= ReadNumber();

		IsAnsswerCorrect(Quize,i);
	}
	Quize.ispass = (Quize.countrigth>= Quize.countworng);
}

int CorrectAnswer(stQuestions answer)
{
	switch (answer.opratorquestion)
	{
	case Add:
		return  answer.firstnumber + answer.sacandnumber;
		break;
	case Sub:
		return  answer.firstnumber - answer.sacandnumber;
		break;
	case Mult:
		return  answer.firstnumber * answer.sacandnumber;
		break;
	case Div:
		return  answer.firstnumber / answer.sacandnumber;
		break;
	default:
		break;
	}
}

stQuestions QuestionQuize(enlevel level, enOprator oprator)
{
	stQuestions Question;
	if(level==enlevel::Mix)
		level= (enlevel)RandomNumber(1, 3);

	if(oprator==enOprator::Max)
		oprator=(enOprator)RandomNumber(1, 4);

	Question.opratorquestion = oprator;

	switch (level)
	{
	case Easy:
		Question.firstnumber = RandomNumber(1, 10);
		Question.sacandnumber = RandomNumber(1, 10);
		Question.correctanswer = CorrectAnswer(Question);
		Question.levelquestion = level;
		return Question;

		break;
	case Med:
		Question.firstnumber = RandomNumber(10, 50);
		Question.sacandnumber = RandomNumber(10, 50);
		Question.correctanswer = CorrectAnswer(Question);
		Question.levelquestion = level;
		return Question;

		break;
	case Hard: 
		Question.firstnumber = RandomNumber(50, 100);
		Question.sacandnumber = RandomNumber(50, 100);
		Question.correctanswer = CorrectAnswer(Question);
		Question.levelquestion = level;
		return Question;

		break;
	default:
		break;
	}

	return  Question;
}

void QuestionsQuize(stGameResult& gammath)
{
	for (short numberQuestion = 0; numberQuestion < gammath.numberofquestions; numberQuestion++)
	{
		gammath.Questions[numberQuestion] = QuestionQuize(gammath.levelGame, gammath.opratorquestion);
	}
}

void PlayeGameMath()
{
	stGameResult gamemath;
	gamemath.numberofquestions = ReadHowManyQuestions("How Many Questions do you want to answar: ");
	gamemath.levelGame= ReadLevelQuestion("Enter Questions Level: [1]:Easy, [2]:Med, [3]:Hard, [4]:Max?");
	gamemath.opratorquestion= ReadOpratorQuestion("Enter Oparation Type: [1]:Add, [2]:Sub, [3]:Mult, [4]:Div, [5]:Max?");

	QuestionsQuize(gamemath);
	AskQuestion(gamemath);
	PrintGameResult(gamemath);
}

void ResturtGame()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char again='y';
	do {

		ResturtGame();
		PlayeGameMath();

		cout << "Do you want to play again? Y/N?" << endl;
		cin >> again;

	} while (again=='y'||again=='Y');
}

int main()
{

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}