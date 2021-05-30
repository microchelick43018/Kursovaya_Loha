#pragma once
#include <iostream>
#include <string>
#include "FileManager.h"
#include "IntStrCharWorker.h"
#include "InputChecker.h"
using namespace std;
class Product
{
private:
	char _name[50];
	char _type[50];
	char _clientName[100];
	int _buyoutPrice;
	int _price;
	int _age;
public:
	Product();

	Product(string name, string type, string clientName, int buyoutPrice, int price, int age);

	string GetName();

	string GetClientName();

	string GetType();

	int GetBuyOutPrice();

	void GetInfoFromFile(fstream& fs);

	int GetPrice();

	int GetAge();

	void PutInfoIntoFile(fstream& fs);

	void ShowInfo(bool forClient);

	void Set(string name, string type, string clientName, int buyoutPrice, int price, int age);

	void SetPrice(int newPrice);

	void SetName(string newName);

	Product& operator=(const Product& p2);

	friend bool operator==(const Product& p1, const Product& p2);
};

