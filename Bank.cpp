#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<fstream>
#include <cstdlib>
using namespace std;

enum enMainMenue {
	Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5,
	Transaction = 6, Exit = 7
};

enum enTransactionMenue {
	Deposit = 1, Withdraw = 2,
	TotalBalanc = 3, MainMenue = 4
};

struct ClientData
{
	string accNumber, name;
	string pin, phone;
	int balance = 0;
	bool checkDelete = false;

};

const string namefile = "ClientData.txt";

void PrintMainMenu();

vector<string> SplitString(string s1, string delmnt)
{
	string delet = delmnt;
	string word;

	short pos = 0;
	vector<string>vstring;

	while ((pos = s1.find(delmnt)) != std::string::npos)
	{
		word = s1.substr(0, pos);

		if (word != delmnt)
			vstring.push_back(word);

		s1.erase(0, pos + delet.length());
	}

	word = s1;
	if (word != delmnt)
	{
		vstring.push_back(s1);
	}

	return vstring;
}

ClientData ConvertLinetoRecord(string data, string sperator)
{
	ClientData rdata;
	vector<string> vData;

	vData = SplitString(data, sperator);

	rdata.accNumber = vData[0];
	rdata.pin = vData[1];
	rdata.name = vData[2];
	rdata.phone = vData[3];
	rdata.balance = stoi(vData[4]);

	return rdata;
}

string ConvertRecordtoLine(ClientData data, string seperator)
{
	string str = "";
	str += data.accNumber + seperator;
	str += data.pin + seperator;
	str += data.name + seperator;
	str += data.phone + seperator;
	str += to_string(data.balance);
	return str;
}

vector<ClientData> ReadFile(string namefile)
{
	vector<ClientData> vdata;

	fstream Client;
	Client.open(namefile, ios::in);

	if (Client.is_open())
	{
		string line;
		ClientData data;
		while (getline(Client, line))
		{
			data = ConvertLinetoRecord(line, "#//#");

			vdata.push_back(data);
		}
		Client.close();
	}
	return vdata;
}

bool IsFindAccountNumber(string accNum, string namefile)
{
	fstream Client;
	Client.open(namefile, ios::in);

	if (Client.is_open())
	{
		string line;
		ClientData data;
		while (getline(Client, line))
		{
			data = ConvertLinetoRecord(line, "#//#");
			if (data.accNumber == accNum)
			{
				return true;
			}
		}
	}

	return false;
}

bool FindClient(string accNum, ClientData& Data, vector<ClientData> vclient)
{
	for (ClientData& d : vclient)
	{
		if (accNum == d.accNumber)
		{
			Data = d;
			return true;
		}
	}
	return false;
}

void PreintClientData(ClientData client)
{
	cout << "\nThe following are the client details: " << endl;

	cout << "\nAccount Number: " << client.accNumber << endl;
	cout << "Pin Code        : " << client.pin << endl;
	cout << "Name            : " << client.name << endl;
	cout << "Phone           : " << client.phone << endl;
	cout << "Account Balance : " << client.balance << endl;

}

string ReadAccountNumber()
{
	string acc;
	cout << "Please Enter Account Number? ";
	cin >> acc;
	return acc;
}

void SaveDataWithFile(string namefile, vector<ClientData> vdata)
{
	fstream Data;
	Data.open(namefile, ios::out);

	if (Data.is_open())
	{
		string line;
		for (ClientData& d : vdata)
		{
			line = ConvertRecordtoLine(d, "#//#");
			Data << line << endl;
		}
		Data.close();
	}
}

void SaveDataWithFile(string namefile, string strdata)
{
	fstream ClientData;
	ClientData.open(namefile, ios::app);

	if (ClientData.is_open())
	{
		ClientData << strdata << endl;
		ClientData.close();
	}
}


//----------------------------- Show Client List. -----------------------------

void ShowAllClient()
{

	vector<ClientData> vdatafile;
	vdatafile = ReadFile(namefile);

	cout << "                  Client List (" << vdatafile.size() << ") Client(s). " << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "| Account Number | Pin Code | Client Name         | Phone       | Balance " << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	for (ClientData data : vdatafile)
	{
		cout << "| " << data.accNumber;
		cout << "            | " << data.pin;
		cout << "     | " << data.name;
		cout << "          | " << data.phone;
		cout << "  | " << data.balance << endl;

	}
	cout << "--------------------------------------------------------------------------" << endl;
}

//----------------------------- End Show. -----------------------------



//----------------------------- Add New Client. -----------------------------

ClientData ReadData()
{
	ClientData data;

	cout << "\nEnter Account Number? ";
	getline(cin >> ws, data.accNumber);

	while (IsFindAccountNumber(data.accNumber, namefile))
	{
		cout << "\nClient with [" << data.accNumber << "] already exists,Enter Account Number?";
		getline(cin, data.accNumber);
	}

	cout << "\nEnter PinCode? "; getline(cin, data.pin);

	cout << "\nEnter Name? "; getline(cin, data.name);

	cout << "\nEnter Phone? "; getline(cin, data.phone);

	cout << "\nEnter Account Balance? "; cin >> data.balance;

	return data;
}

void AddClient()
{
	ClientData Client;
	Client = ReadData();

	SaveDataWithFile(namefile, ConvertRecordtoLine(Client, "#//#"));
}

void AddClients()
{
	char again;
	do {

		AddClient();

		cout << "\nClient Added Successfully, do you want to add more clients? " << endl;
		cin >> again;

	} while (toupper(again) == 'Y');

}

void ShowScreenAddClients()
{
	cout << "------------------------------------------------------" << endl;
	cout << "\n\n\n" << setw(25) << "Add New Clients Screen" << endl;
	cout << "------------------------------------------------------" << endl;

	cout << "Adding New Client: " << endl;
	AddClients();
}

//----------------------------- End Add. -----------------------------



//----------------------------- Delete Client. -----------------------------

void MakeCheckDelete(vector<ClientData>& vclient, string accNum)
{
	for (ClientData& C : vclient)
	{
		if (accNum == C.accNumber)
		{
			C.checkDelete = true;
		}
		else
			C.checkDelete = false;
	}
}

void DeleteDataofFile(vector<ClientData>& vclient)
{
	fstream Data;
	Data.open(namefile, ios::out);

	if (Data.is_open())
	{
		string line;
		for (ClientData& Client : vclient)
		{
			if (Client.checkDelete == false)
			{
				line = ConvertRecordtoLine(Client, "#//#");
				Data << line << endl;
			}
		}

	}
}

void DeleteClientData(vector<ClientData>& vclient, string accNum)
{
	char anwser = 'n';
	ClientData Client;

	if (FindClient(accNum, Client, vclient))
	{
		PreintClientData(Client);

		cout << "\nAre you sure you want deleted this client? y/n? ";
		cin >> anwser;

		if (toupper(anwser) == 'Y')
		{
			MakeCheckDelete(vclient, accNum);
			DeleteDataofFile(vclient);

			vclient = ReadFile(namefile);

			cout << "\nClient Deleted Successfully." << endl;
		}
	}
	else
		cout << "\nClient with Account Number(" << accNum << ") Not Found! " << endl;

}

void DeletClientByAccountNumber()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\n\n\n" << setw(24) << "Delete Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string accountNumber = ReadAccountNumber();

	vector<ClientData>vclient;
	vclient = ReadFile(namefile);

	DeleteClientData(vclient, accountNumber);
}

//----------------------------- End Delete. -----------------------------



//-----------------------------Update Client Ifo. -----------------------------

ClientData ChangeClientData(string accNum)
{
	ClientData data;
	data.accNumber = accNum;

	cout << "\nEnter PinCode? "; getline(cin >> ws, data.pin);

	cout << "Enter Name? "; getline(cin, data.name);

	cout << "Enter Phone? "; getline(cin, data.phone);

	cout << "Enter Account Balance? "; cin >> data.balance;

	return data;
}

bool UpdateClientData(string accNum, vector<ClientData>& vdata)
{
	char anwser = 'n';
	ClientData Client;

	if (FindClient(accNum, Client, vdata))
	{
		PreintClientData(Client);

		cout << "\nAre you sure you want Update this client? y/n? ";
		cin >> anwser;

		if (toupper(anwser) == 'Y')
		{
			for (ClientData& c : vdata)
			{
				if (c.accNumber == accNum)
				{
					c = ChangeClientData(accNum);
					break;
				}
			}

			SaveDataWithFile(namefile, vdata);

			cout << "\nClient Update Successfully." << endl;
			return true;
		}
	}
	else
		cout << "\nClient with Account Number(" << accNum << ") Not Found! " << endl;

	return false;
}

void UpdateClientByAccountNumber()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\n\n\n" << setw(29) << "Update Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string accountNumber = ReadAccountNumber();

	vector<ClientData> vdata;
	vdata = ReadFile(namefile);

	UpdateClientData(accountNumber, vdata);

}

//-----------------------------End Update. -----------------------------



//-----------------------------Find Client. -----------------------------

void FindClientByAccountNumber()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\n\n\n" << setw(22) << "Find Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string accountNumber = ReadAccountNumber();

	vector<ClientData> vdata;
	vdata = ReadFile(namefile);

	ClientData Client;

	if (FindClient(accountNumber, Client, vdata))
	{
		PreintClientData(Client);
	}
	else
		cout << "\nClient with Account Number(" << accountNumber << ") Not Found! " << endl;

}

//-----------------------------End Find. -----------------------------



//----------------------------- Deposits. -----------------------------

void TransactionDeposits()
{
	string Accountnumber = ReadAccountNumber();

	vector<ClientData> vdata;
	vdata = ReadFile(namefile);

	ClientData Client;

	while (!FindClient(Accountnumber, Client, vdata))
	{
		cout << "Client with [" << Accountnumber << "] does not exist." << endl;
		Accountnumber = ReadAccountNumber();
	}

	PreintClientData(Client);

	cout << "-------------------------------------------------" << endl;

	char answor = 'n';

	short amount;
	cout << "\nPlease enter deposit amount? " << endl;
	cin >> amount;

	cout << "\nAre you sure you want perform this Transection? y/n? ";
	cin >> answor;

	if (toupper(answor) == 'Y')
	{
		for (ClientData& c : vdata)
		{
			if (c.accNumber == Accountnumber)
			{
				c.balance += amount;

				cout << "Done Successfully." << endl;
				cout << "New Balance: " << c.balance << endl;

				break;
			}
		}

		SaveDataWithFile(namefile, vdata);
	}

}

void ShowDepositScreen()
{
	cout << "\n" << "--------------------------------------------------" << endl;
	cout << "\t\tDeposit Screen" << endl;
	cout << "-----------------------------------------------------" << endl;

	TransactionDeposits();
}

//-----------------------------End Deposits. -----------------------------



//----------------------------- Withdraw. -----------------------------

void TransactionWithdraw()
{
	string Accountnumber = ReadAccountNumber();

	vector<ClientData> vdata;
	vdata = ReadFile(namefile);

	ClientData Client;

	if (FindClient(Accountnumber, Client, vdata))
	{
		PreintClientData(Client);

		char answor = 'n';
		short amount;
		cout << "\nPlease enter withdraw amount? "; cin >> amount;

		while (amount > Client.balance)
		{
			cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.balance << endl;
			cout << "\nPlease enter withdraw amount? "; cin >> amount;
		}

		cout << "\nAre you sure you want perform this Transection? y/n? ";
		cin >> answor;

		if (toupper(answor) == 'Y')
		{
			for (ClientData& c : vdata)
			{
				if (c.accNumber == Accountnumber)
				{
					c.balance -= amount;

					cout << "Done Successfully." << endl;
					cout << "New Balance: " << c.balance << endl;

					break;
				}
			}

			SaveDataWithFile(namefile, vdata);
		}

	}
	else
		cout << "\nClient with Account Number(" << Accountnumber << ") Not Found! " << endl;
}

void ShowWithdrawScreen()
{
	cout << "\n" << "--------------------------------------------------" << endl;
	cout << "\t\tWithdraw Screen" << endl;
	cout << "-----------------------------------------------------" << endl;

	TransactionWithdraw();
}

//-----------------------------End Withdraw. -----------------------------



//----------------------------- Total Balances. -----------------------------

void ShowTotalBalancesScreen()
{

	vector<ClientData> vdatafile;
	vdatafile = ReadFile(namefile);

	cout << "                  Balances List (" << vdatafile.size() << ") Client(s). " << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "| Account Number | Client Name             | Balance " << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	int totalBlance = 0;

	for (ClientData& data : vdatafile)
	{
		cout << "| " << data.accNumber;
		cout << "     | " << data.name;
		cout << "  | " << data.balance << endl;

		totalBlance += data.balance;

	}
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\tTotal Balances = " << totalBlance << endl;
}

//-----------------------------End Total Balances. -----------------------------



//-----------------------------Transactions Client. -----------------------------

enTransactionMenue ReadNumberMenuTrans()
{
	int num;
	do {
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> num;
	} while (num > 4 && num < 1);
	return enTransactionMenue(num);
}

void TransactionsMenuScreen(enTransactionMenue num)
{
	switch (num)
	{
	case Deposit:
		system("cls");
		ShowDepositScreen();

		break;
	case Withdraw:
		system("cls");
		ShowWithdrawScreen();

		break;
	case TotalBalanc:
		system("cls");

		break;
	case MainMenue:
		system("cls");
		PrintMainMenu();

		break;
	default:
		break;
	}
}

void PrintTransactionsMenuScreen()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "\t\t\t Transactions Menu Screen " << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\t\t [1] Deposit." << endl;
	cout << "\t\t [2] Withdraw." << endl;
	cout << "\t\t [3] Total Balances." << endl;
	cout << "\t\t [4] Main Menue." << endl;

	TransactionsMenuScreen(ReadNumberMenuTrans());
}

void ShowScreenTransactions()
{
	PrintTransactionsMenuScreen();
	system("pause");
}

//-----------------------------End Transctions. -----------------------------

void ProgreamExit()
{

	cout << "-------------------------------------------------" << endl;
	cout << "\n\n\n" << setw(15) << "Program End :)" << endl;
	cout << "-------------------------------------------------" << endl;
}

void MenuAllFeatures(enMainMenue num)
{
	switch (num)
	{
	case Show:
		system("cls");
		ShowAllClient();
		break;
	case Add:
		system("cls");
		ShowScreenAddClients();
		break;
	case Delete:
		system("cls");
		DeletClientByAccountNumber();
		break;
	case Update:
		system("cls");
		UpdateClientByAccountNumber();
		break;
	case Find:
		system("cls");
		FindClientByAccountNumber();
		break;
	case Transaction:
		system("cls");
		ShowScreenTransactions();
		break;
	case Exit:
		system("cls");
		ProgreamExit();
		break;
	default:
		break;
	}
}

enMainMenue ReadNumber()
{
	int num;
	do {
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> num;
	} while (num > 7 && num < 1);
	return enMainMenue(num);
}

void PrintMainMenu()
{
	cout << "------------------------------------------------" << endl;
	cout << setw(35) << "Main Menu Screen" << endl;
	cout << "------------------------------------------------" << endl;

	cout << setw(27) << "[1] Show Client List." << endl;
	cout << setw(25) << "[2] Add New Client." << endl;
	cout << setw(24) << "[3] Delete Client." << endl;
	cout << setw(29) << "[4] Update Client Info." << endl;
	cout << setw(22) << "[5] Find Client." << endl;
	cout << setw(23) << "[6] Transactions." << endl;
	cout << setw(15) << "[7] Exit." << endl;
	cout << "--------------------------------------------------" << endl;

	MenuAllFeatures(ReadNumber());
}

int main()
{
		PrintMainMenu();
		system("pause>0");
	return 0;
}