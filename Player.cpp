#include "Player.h"
//
Player::Player()
{
	name = "";
}
//
string Player::getName()
{
	return name;
}
//
void Player::setName(string name)
{
	this->name = name;
}
//
void Player::inputName()
{
	system("cls");
	string name;
	cout << "ENTER PLAYER'S NAME: ";
	fflush(stdin);
	getline(cin, name);
	setName(name);
}
//
Hero* Player::getHero()
{
	return myHero;
}
//
void Player::playerChoseHero(vector<Hero> listHero)
{
	int k;
	cout << endl << name << " CHOOSE YOUR TEAM 3 HEROES !\n";
	for (int i = 0; i < 3; i++) 
	{
		do
		{
			cout << "\nHERO " << i + 1 << ": ";
			cin >> k;
		} while (k < 0 || k >= listHero.size());
		myHero[i] = listHero[k];
		myHero[i].showHeroShort();
	}
}
//
Player& Player::operator=(const Player& src)
{
	if (this != &src) {
		name = src.name;
		myHero[0] = src.myHero[0];
		myHero[1] = src.myHero[1];
		myHero[2] = src.myHero[2];
	}
	return *this;
}
//
Player::~Player()
{
}
//
NPC::NPC()
{
	name = "NPC";
}
//
void NPC::playerChoseHero(vector<Hero> listHero)
{
	cout << "\n\n\t\t\tVS\n";
	cout << "NPC TEAM:\n";
	int k;
	vector<Hero>::iterator ptr;
	for (int i = 0; i < 3; i++) {
		ptr = listHero.begin();
		srand(time(NULL));
		Sleep(1000);
		k = rand() % (listHero.size() - 1);
		//
		advance(ptr, k);
		myHero[i] = *ptr;
		cout << "\nHERO " << i + 1 << " : ";
		cout << k << endl;
		myHero[i].showHeroShort();
	}
}
//
NPC::~NPC()
{
}