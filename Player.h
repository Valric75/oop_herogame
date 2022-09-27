#pragma once
#include "Hero.h"
class Player 
{
protected:
	string name;
	Hero myHero[3];
public:
	Player();
	virtual ~Player();
	Hero* getHero();
	string getName();
	void setName(string);
	void inputName();
	virtual void playerChoseHero(vector<Hero>);
	Player& operator = (const Player&);
};
class NPC :public Player 
{
public:
	NPC();
	~NPC();
	void playerChoseHero(vector<Hero>);
};