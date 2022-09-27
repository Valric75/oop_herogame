#pragma once
#include "Player.h"
struct Time 
{
	string hour;
	string minute;
	string second;
	string day;
	string month;
	string year;
};
/*this struct use to save an object to file log.txt*/
struct LogIn 
{
	string envi;
	Time time;
	Player *p1;
	Player *p2;
	int result=0;
};
/*this struct use to get an object from file log.txt*/
struct LogOut {
	string time;
	string date;
	string envi;
	string nameP1;
	string nameP2;
	string myHero1[3];
	string myHero2[3];
	string result;
};
void readFile(string, vector<Hero>&);
void showHeroList(vector<Hero>);
string setEnvironment();
float setTime();
void showResult(Player*, Player*);
void checkImcompatible(Hero& , Hero& );
int Fight(Hero, Hero, float, float&);
int Battle(Player*, Player*, float, string&);
LogIn createLogIn(Player*, Player*, int, string);
void readFileLog(string, vector<LogOut>& );
void writeFileHero(ofstream&, Hero);
void writeFile(string, LogIn);
void showFileLog(vector<LogOut>);
void showLogOut(LogOut);
void showDetailLog(int&, vector<LogOut>);
void editListHero(vector<Hero> &listHero);
void getInputChoice(int& choice, int begin, int end);
void writeFileHero(string, vector<Hero>);
void menu();