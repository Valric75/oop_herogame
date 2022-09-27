#include "Hero.h"
//
Hero::Hero()
{
	name = element = "";
	HP = 0;
	ATK = 0;
	DEF = 0;
	AS = 0;
}
//
Hero::Hero(string name, string element, float HP, float	ATK, float DEF, float AS)
{
	this->element = element;
	this->name = name;
	this->ATK = ATK;
	this->DEF = DEF;
	this->HP = HP;
	this->AS = AS;
}
//
Hero::Hero(const Hero& h)
{
	element = h.element;
	name = h.name;
	ATK = h.ATK;
	DEF = h.DEF;
	HP = h.HP;
	AS = h.AS;
}
//
string Hero::getName()
{
	return name;
}
//
string Hero::getElement()
{
	return element;
}
//
float Hero::getHP()
{
	return HP;
}
//
float Hero::getDEF()
{
	return DEF;
}
//
float Hero::getAS()
{
	return AS;
}
//
float Hero::getATK()
{
	return ATK;
}
//
void Hero::setName(string name)
{
	this->name = name;
}
//
void Hero::setElement(string element)
{
	this->element = element;
}
//
void Hero::setHP(float HP)
{
	this->HP = HP;
}
//
void Hero::setATK(float ATK)
{
	this->ATK = ATK;
}
//
void Hero::setDEF(float DEF)
{
	this->DEF = DEF;
}
//
void Hero::setAS(float AS)
{
	this->AS = AS;
}
//
void Hero::inputHero()
{
	cout << "Name: ";
	cin.ignore();
	getline(cin, name);
	
	int m;
	string a[5] = { "Water","Wood","Fire","Earth","Metal" };
	cout << "[ 0.Water 1.Wood 2.Fire 3.Earth 4.Metal ]\n";
	do {
		cout << "Choose element (Number only): ";
		cin >> m;
	} while (m < 0 || m>4);
	element = a[m];
	cout << "Element: " << element << endl;
	cout << "HP: "; 
	cin >> HP;
	cout << "ATK: "; 
	cin >> ATK;
	cout << "DEF: "; 
	cin >> DEF;
	cout << "AS: "; 
	cin >> AS;
}
//
void Hero::editHero()
{
	int choice=0;
	do
	{
		system("cls");
		cout << "EDIT HERO\n";
		cout << "\n1. Name: " << name;
		cout << "\n2. Element: " << element;
		cout << "\n3. HP: " << HP;
		cout << "\n4. ATK: " << ATK;
		cout << "\n5. DEF: " << DEF;
		cout << "\n6. AS: " << AS;
		cout << "\n7. EXIT ";
		cout << "\nEnter your choice: ";
		cin >> choice;
		if (choice == 1) {
			cout <<  name << " -> ";
			cin.ignore();
			getline(cin, name);
		}
		else if (choice == 2) {
			int m;
			string a[5] = { "Water","Wood","Fire","Earth","Metal" };
			cout << "[ 0.Water 1.Wood 2.Fire 3.Earth 4.Metal ]\n";
			do {
				cout << element << " -> (number only): ";
				cin >> m;
			} while (m < 0 || m>4);
			element = a[m];
		}
		else if (choice == 3) {
			cout  << HP << " -> ";
			cin >> HP;
		}
		else if (choice == 4) {
			cout << ATK << " -> ";
			cin >> ATK;
		}
		else if (choice == 5) {
			cout <<  DEF << " -> ";
			cin >> DEF;
		}
		else if (choice == 6) {
			cout <<  AS << " -> ";
			cin >> AS;
		}
	} while (choice != 7);
}
//
void Hero::alliesBuff(string ali1, string ali2)
{
	/*check if compatible*/
	vector<string> a = { "Water","Wood","Fire","Earth","Metal" };
	int i;
	float upHP = 0;
	for (i = 0; i < 5; i++) if (element == a[i]) break;
	if (i == 0) i = 5;
	if (ali1 == a[i - 1]) upHP += 15;
	if (ali2 == a[i - 1]) upHP += 15;
	HP = (HP * (100 + upHP)) / 100;
	/*check if incompatible*/
	string b[5] = { "Wood","Earth","Water","Fire","Metal" };
	int upAS = 0;
	for (i = 0; i < 5; i++) if (element == b[i]) break;
	if (i == 0) i = 5;
	if (ali1 == a[i - 1]) upAS += 10;
	if (ali2 == a[i - 1]) upAS += 10;
	AS = (AS * (100 + upAS)) / 100;
}
//
void Hero::environmentBuff(string envi)
{
	/*check if compatible*/
	vector<string> a = { "Water","Wood","Fire","Earth","Metal" };
	int i;
	for (i = 0; i < 5; i++) if (element == a[i]) break;
	if (i == 0) i = 5;
	if (envi == a[i - 1]) {
		HP = (HP * (100 + 5)) / 100;
		AS = (AS * (100 - 10)) / 100;
	}
	/*check if incompatible*/
	string b[5] = { "Wood","Earth","Water","Fire","Metal" };
	for (i = 0; i < 5; i++) if (element == b[i]) break;
	if (i == 0) i = 5;
	if (envi == a[i - 1]) HP = (HP * (100 - 3)) / 100;
}
//
void Hero::beBuff(string ali1, string ali2, string envi)
{
	Hero::alliesBuff(ali1, ali2);
	Hero::environmentBuff(envi);
}
//
void Hero::showHeroShort()
{
	 cout << name << "; " << element << "; " << HP << "; " << ATK << "; " << DEF << "; " << AS;
}
//
void Hero::showHeroFull()
{
	cout << "Name: " << name << endl;
	cout << "Element: " << element << endl;
	cout << "\t\tHP: " << HP << "\tATK: " << ATK << endl;
	cout << "\t\tDEF: " << DEF << "\tAS: " << AS << endl;
}
//
Hero& Hero::operator=(const Hero& src)
{
	if (this != &src) {
		name = src.name;
		element = src.element;
		HP = src.HP;
		ATK = src.ATK;
		DEF = src.DEF;
		AS = src.AS;
	}
	return *this;
}
//
Hero::~Hero()
{
}