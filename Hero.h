/*
	Project Name: Hero Game
	Date start: 21st May 2021
	Developer: Quoc Bao - 19120175
*/
#pragma once
#pragma warning(disable : 4996)
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
class Hero 
{
	string name;
	string element;
	float HP;
	float ATK;
	float DEF;
	float AS;
public:
	Hero();
	Hero(string, string, float, float, float, float);
	Hero(const Hero&);
	~Hero();
	string getElement();
	string getName();
	float getHP();
	float getAS();
	float getATK();
	float getDEF();
	void setName(string);
	void setElement(string);
	void setHP(float);
	void setATK(float);
	void setDEF(float);
	void setAS(float);
	void inputHero();
	void editHero();
	void alliesBuff(string, string);
	void environmentBuff(string);
	void beBuff(string, string, string);
	void showHeroShort();
	void showHeroFull();
	Hero& operator = (const Hero&);	
};