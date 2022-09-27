#include "Header.h"
//
void readFile(string fileName, vector<Hero>& listHero)
{
	fstream f(fileName, ios::in);
	if (f.is_open()) 
	{
		string extraLine;
		getline(f, extraLine);
		string s, r;
		string a, b, c, d;
		while (!f.eof()) 
		{
			getline(f, s, ';');
			getline(f, r, ';');
			getline(f, a, ';');
			getline(f, b, ';');
			getline(f, c, ';');
			getline(f, d);
			Hero temp(s, r, stof(a), stof(b), stof(c), stof(d));
			listHero.push_back(temp);
		}
		f.close();
	}
	else cout << "Unable to open file";
}
//
void showHeroList(vector<Hero> listHero)
{
	cout << "\n\tX______LIST OF HERO______X \n";
	cout << "\t         ____T____\n";
	cout << "\t           _____\n\n";
	int n = listHero.size();
	for (int i = 0; i < n; i++) 
	{
		cout << "HERO " << i <<"________"<< "\n";
		listHero[i].showHeroFull();
	}
}
//
string setEnvironment()
{
	int k;
	srand(time(NULL));
	k = rand() % 4 + 0;
	string a[5] = { "Water","Wood","Fire","Earth","Metal" };
	return a[k];
}
//
float setTime()
{
	int choice;
	float time;
	Menu:
	cout << "\n\nSET TIME:\n";
	cout << "1. 1000\n";
	cout << "2. 2000\n";
	cout << "3. 5000\n";
	cout << "YOUR CHOICE:";
	cin >> choice;
	if (choice == 1)time = 1000.0f;
	else if (choice == 2)time = 2000.0f;
	else if (choice == 3)time = 5000.0f;
	else goto Menu;
	return time;
}
//
void showResult(Player *p1, Player *p2)
{
	cout << "\nTeam " << p1->getName() << endl;
	p1->getHero()[0].showHeroShort();
	cout << endl;
	p1->getHero()[1].showHeroShort();
	cout << endl;
	p1->getHero()[2].showHeroShort();
	cout << endl;
	cout << "\nTeam " << p2->getName() << endl;
	p2->getHero()[0].showHeroShort();
	cout << endl;
	p2->getHero()[1].showHeroShort();
	cout << endl;
	p2->getHero()[2].showHeroShort();
}
//
void checkImcompatible(Hero& a, Hero& b) 
{
	string ele[5] = { "Wood","Earth","Water","Fire","Metal" };
	int i;
	//find the element of a
	for (i = 0; i < 5; i++) if (a.getElement() == ele[i]) break;
	// exception
	if (i == 0) i = 5;
	//if incompatible with enemy
	if (b.getElement() == ele[i - 1]) 
	{
		b.setATK(b.getATK() * 110 / 100);
		a.setDEF(a.getDEF() * 50 / 100);
	}
}
//
int Fight(Hero a, Hero b, float roundTime, float& endTime)
{
	checkImcompatible(a, b);
	checkImcompatible(b, a);
	float timeAlive1, timeAlive2;
	timeAlive1 = (a.getHP() / (b.getATK() - a.getDEF())) * b.getAS();
	timeAlive2 = (b.getHP() / (a.getATK() - b.getDEF())) * a.getAS();
	/*the result will be decided by time survive of the hero*/
	//tie result
	if (timeAlive1 > roundTime && timeAlive2 > roundTime) 
	{
		endTime = roundTime;
		return 0;
	}
	//hero 1 win
	if (timeAlive1 > timeAlive2) 
	{
		endTime = timeAlive2;
		return 1;
	}
	//hero 2 win
	if (timeAlive1 < timeAlive2) 
	{
		endTime = timeAlive1;
		return 2;
	}
	return 3;
}
//
int Battle(Player *p1, Player *p2, float roundTime, string& envi)
{
	/*A battle will have 3 fights*/
	system("cls");
	envi = setEnvironment();
	int result[3] = { 0,0,0 };
	//
	float fightTime[3];
	//Round 1
	p1->getHero()[0].beBuff(p1->getHero()[1].getElement(), p1->getHero()[2].getElement(), envi);
	p2->getHero()[0].beBuff(p2->getHero()[1].getElement(), p2->getHero()[2].getElement(), envi);
	result[0] = Fight(p1->getHero()[0], p2->getHero()[0], roundTime, fightTime[0]);
	//Round 2
	p1->getHero()[1].beBuff(p1->getHero()[0].getElement(), p1->getHero()[2].getElement(), envi);
	p2->getHero()[1].beBuff(p2->getHero()[0].getElement(), p2->getHero()[2].getElement(), envi);
	result[1] = Fight(p1->getHero()[1], p2->getHero()[1], roundTime, fightTime[1]);
	//Round 3
	p1->getHero()[2].beBuff(p1->getHero()[0].getElement(), p1->getHero()[1].getElement(), envi);
	p2->getHero()[2].beBuff(p2->getHero()[0].getElement(), p2->getHero()[1].getElement(), envi);
	result[2] = Fight(p1->getHero()[2], p2->getHero()[2], roundTime, fightTime[2]);
	//
	int p1Point = 0;
	int p2Point = 0;
	/*set current HP for two teams heroes*/
	for (int i = 0; i < 3; i++) {
		if (result[i] == 0) //tie
		{
			p1->getHero()[i].setHP( p1->getHero()[i].getHP() - (roundTime / p2->getHero()[i].getAS()) * (p2->getHero()[i].getATK() - p1->getHero()[i].getDEF()));
			p2->getHero()[i].setHP(  p2->getHero()[i].getHP() - (roundTime / p1->getHero()[i].getAS()) * (p1->getHero()[i].getATK() - p2->getHero()[i].getDEF()));
		}
		else if (result[i] == 1) //p1 win
		{
			p1->getHero()[i].setHP( p1->getHero()[i].getHP() - (fightTime[i] / p2->getHero()[i].getAS()) * (p2->getHero()[i].getATK() - p1->getHero()[i].getDEF()));
			p2->getHero()[i].setHP(0);
			p1Point++;
		}
		 else if (result[i] == 2) //p2 win
		{
			p1->getHero()[i].setHP(0);
			p2->getHero()[i].setHP(p2->getHero()[i].getHP() - (fightTime[i] / p1->getHero()[i].getAS()) * (p1->getHero()[i].getATK() - p2->getHero()[i].getDEF()));
			p2Point++;
		}
	}
	cout << "Enviroment: -" << envi << "-" << endl << endl;
	if (p1Point == p2Point) 
	{
		cout << "TIE !\n";
		showResult(p1, p2);
		return 0;
	}
	if (p1Point > p2Point)
	{
		cout << p1->getName() << " WIN !\n";
		showResult(p1, p2);
		return 1;
	}
	if (p1Point < p2Point)
	{
		cout << p2->getName() << " WIN !\n";
		showResult(p1, p2);
		return 2;
	}
	system("pause");
	return 3;
}
//
LogIn createLogIn(Player *p1, Player *p2, int result, string envi) 
{
	LogIn log;
	/*current date/time based on current system*/
	time_t now = time(0);
	tm* ltm = localtime(&now);
	//
	log.time.year = to_string(1900 + ltm->tm_year);
	log.time.month = to_string(1+ltm->tm_mon);
	log.time.day = to_string(ltm->tm_mday);
	log.time.hour = to_string(ltm->tm_hour);
	log.time.minute = to_string(ltm->tm_min);
	log.time.second = to_string(ltm->tm_sec);
	//
	log.envi = envi;
	log.p1 = p1;
	log.p2 = p2;
	log.result = result;
	return log;
}
//
void readFileLog(string fileName, vector<LogOut>& listLogOut)
{
	fstream f(fileName, ios::in);
	if (f.is_open()) 
	{
		LogOut temp;
		string extraLine;
		getline(f, extraLine);
		while (!f.eof()) 
		{
			getline(f, temp.time);
			getline(f, temp.date);
			getline(f, temp.envi);
			getline(f, temp.nameP1);
			for (int i = 0; i < 3; i++) 
			{
				getline(f, temp.myHero1[i]);
			}
			getline(f, temp.nameP2);
			for (int i = 0; i < 3; i++) 
			{
				getline(f, temp.myHero2[i]);
			}
			getline(f, temp.result);
			listLogOut.push_back(temp);
		}
		f.close();
	}
	else cout << "Unable to open file";
}
//
void writeFileHero(ofstream& f, Hero hero) 
{
	f << endl << hero.getName() << ";" << hero.getElement() << ";" << hero.getHP() << ";" << hero.getATK() << ";" << hero.getDEF() << ";" << hero.getAS() ;
}
//
void writeFile(string fileName, LogIn logIn) 
{
	ofstream f(fileName,ios::app);
	if (f.is_open()) 
	{
		f << endl;
		f << logIn.time.hour << ":" << logIn.time.minute << ":" << logIn.time.second << endl;
		f << logIn.time.day << "/" << logIn.time.month << "/" << logIn.time.year << endl;
		f << logIn.envi << endl;
		f << logIn.p1->getName() ;
		for (int i = 0; i < 3; i++) 
		{
			writeFileHero(f, logIn.p1->getHero()[i]);
		}
		f << endl << logIn.p2->getName() ;
		for (int i = 0; i < 3; i++) 
		{
			writeFileHero(f, logIn.p2->getHero()[i]);
		}
		f << endl << logIn.result ;
	}
	else cout << "Unable to open file";
	f.close();
}
//
void showFileLog(vector<LogOut> listLogOut) 
{
	system("cls");
	cout << "\tFILE LOG.TXT\n\n";
	vector<LogOut>::iterator ptr;
	for (ptr= listLogOut.begin(); ptr < listLogOut.end(); ptr++) 
	{
		cout << ptr->time << endl;
		cout << ptr->date << endl;
		cout << "------------------" << endl;
	}
}
//
void showLogOut(LogOut log) 
{
	cout << endl << log.time << endl;
	cout << log.date << endl << endl;
	cout << "-" << log.envi << "-" << endl << endl;
	cout << log.nameP1 << endl;
	for (int i = 0; i < 3; i++) 
	{
		cout << log.myHero1[i] << endl;
	}
	cout << endl << log.nameP2 << endl;
	for (int i = 0; i < 3; i++) 
	{
		cout << log.myHero2[i] << endl;
	}
	if (log.result == "0") 
	{
		cout << "\nTIE RESULT !!\n\n";
	}
	else if (log.result == "1") 
	{
		cout << endl << log.nameP1 << " WIN !\n\n";
	}
	else if (log.result == "2") 
	{
		cout << endl << log.nameP2 << " WIN !\n\n";
	}
}
//
void showDetailLog(int& choice2, vector<LogOut> listLogOut)
{
	string time;
	string date;
	string day, month, year;
	string hour, minute, second;
	bool found = 0;
	//
	showFileLog(listLogOut);
	cout << "\nSEE DETAIL\n";
	cout << "1. CHOOSE DATE\n";
	cout << "2. CHOOSE DATE AND TIME\n";
	cout << "3. EXIT";
	getInputChoice(choice2, 1, 3);
	//
	if (choice2 == 1)
	{
		showFileLog(listLogOut);
		string day, month, year;
		cout << "\nDAY: ";
		cin >> day;
		cout << "MONTH: ";
		cin >> month;
		cout << "YEAR: ";
		cin >> year;
		date = day + "/" + month + "/" + year;
		system("cls");
		cout << "GAME HISTORY:\n";
		cout << "--------------";
		for (int i = 0; i < listLogOut.size(); i++)
		{
			if (date == listLogOut[i].date)
			{
				showLogOut(listLogOut[i]);
				cout << "--------------";
				found = 1;
			}
		}
		if (found == 0)
		{
			cout << "\nNo record found !\n";
		}
		system("pause");
	}
	else if (choice2 == 2)
	{
		showFileLog(listLogOut);
		cout << "\nDAY: ";
		cin >> day;
		cout << "MONTH: ";
		cin >> month;
		cout << "YEAR: ";
		cin >> year;
		cout << "HOUR: ";
		cin >> hour;
		cout << "MINUTE: ";
		cin >> minute;
		cout << "SECOND: ";
		cin >> second;
		time = hour + ":" + minute + ":" + second;
		date = day + "/" + month + "/" + year;
		system("cls");
		cout << "GAME HISTORY:\n";
		cout << "--------------";
		for (int i = 0; i < listLogOut.size(); i++)
		{
			if (listLogOut[i].date == date)
			{
				if (listLogOut[i].time == time)
				{
					showLogOut(listLogOut[i]);
					cout << "--------------";
					found = 1;
				}
			}
		}
		if (found == 0)
		{
			cout << "\nNo record found !\n";
		}
		system("pause");
	}
	else if (choice2 == 3) return;
}
//
void editListHero(vector<Hero> &listHero)
{
	int choice;
	do {
		system("cls");
		showHeroList(listHero);
		cout << "1. ADD HERO\n";
		cout << "2. EDIT HERO\n";
		cout << "3. DELETE HERO\n";
		cout << "4. EXIT";
		getInputChoice(choice, 1, 4);
		if (choice == 1)
		{
			Hero temp;
			cout << "\nADD HERO:\n";
			temp.inputHero();
			listHero.push_back(temp);
		}
		else if (choice == 2)
		{
			int k;
			do
			{
				system("cls");
				showHeroList(listHero);
				cout << "\nEDIT HERO:\n";
				cout << "\nSELECT HERO :";
				cin >> k;
			} while (k < 0 || k >= listHero.size());
			listHero[k].editHero();
		}
		else if (choice == 3)
		{
			int m;
			do
			{
				system("cls");
				showHeroList(listHero);
				cout << "\nDELETE HERO:\n";
				cout << "\nSELECT HERO: ";
				cin >> m;
			} while (m < 0 || m >= listHero.size() || cin.fail());
			vector<Hero>::iterator it = listHero.begin();
			advance(it, m);
			listHero.erase(it);
		}
	} while (choice != 4);
}
//
void writeFileHero(string fileName, vector<Hero> listHero) 
{
	ofstream f(fileName, ios::trunc);
	if (f.is_open())
	{
		f << "-This line is reserved-";
		for (std::vector<Hero>::iterator it = listHero.begin(); it != listHero.end(); ++it) writeFileHero(f, *it);	
	}
	else cout << "Unable to open file";
	f.close();
}
//
void getInputChoice(int& choice, int begin, int end)
{
	cout << "\nENTER YOUR CHOICE:";
	cin >> choice;
	while ( choice < begin || choice > end) {
		cout << "PLEASE ENTER YOUR CHOICE CORECTLY: ";
		cin >> choice;
	}
}
//
void menu()
{
	int choiceMenu = 0, choice1 = 0, choice2 = 0;
	int result;
	string envi;
	vector<LogIn> listLogIn;
	vector<LogOut> listLogOut;
	string fileHero = "ListHero.txt";
	string fileLog = "Log.txt";
	Player* p1 = new Player;
	Player* p2 = new Player;
	Player* npc = new NPC;
	vector<Hero> listHero;
	readFile(fileHero, listHero);
	//
	p1->inputName();
	do
	{
		system("cls");
		cout << " _    _   ______   _____     ____\n";
		cout << "| |  | | |  ____| |  __ \\   / __ \\\n";
		cout << "| |__| | | |__    | |__) | | |  | |\n";
		cout << "|  __  | |  __|   |  _  /  | |  | |\n";
		cout << "| |  | | | |____  | | \\ \\  | |__| |\n";
		cout << "|_|  |_| |______| |_|  \\_\\  \\____/\n";
		cout << "______________________\n";
		cout << "1. PLAY\n";
		cout << "2. LOG\n";
		cout << "3. HERO\n";
		cout << "4. EXIT";
		getInputChoice(choiceMenu, 1, 4);
		//
		switch (choiceMenu)
		{
		case 1:
			system("cls");
			cout << "CHOOSE MODE:\n";
			cout << "1. PVC\n";
			cout << "2. PVP";
			getInputChoice(choice1, 1, 2);
			if (choice1 == 1)
			{
				system("cls");
				showHeroList(listHero);
				p1->playerChoseHero(listHero);
				npc->playerChoseHero(listHero);
				result = Battle(p1, npc, 1000.0f, envi);
				//save file
				LogIn logIn = createLogIn(p1, npc, result, envi);
				writeFile(fileLog, logIn);
				cout << endl;
				system("pause");
			}
			else if (choice1 == 2)
			{
				cout << "PLAYER 2 ";
				p2->inputName();
				showHeroList(listHero);
				p1->playerChoseHero(listHero);
				cout << endl;
				p2->playerChoseHero(listHero);
				result = Battle(p1, p2, setTime(), envi);
				//save file
				LogIn logIn = createLogIn(p1, p2, result, envi);
				writeFile(fileLog, logIn);
				cout << endl;
				system("pause");
			}
			break;
		case 2:
			readFileLog(fileLog, listLogOut);
			do 
			{
				showDetailLog(choice2, listLogOut);
			} while (choice2 != 3);
			listLogOut.clear();
			break;
		case 3:
			editListHero(listHero);
			writeFileHero(fileHero, listHero);
			break;
		default:
			break;
		}
	} while (choiceMenu != 4);
	delete p1;
	delete p2;
	delete npc;
}