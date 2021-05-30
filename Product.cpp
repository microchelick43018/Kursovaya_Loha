#include "Product.h"

void Product::Set(string name, string type, string clientName, int buyoutPrice, int price, int age)
{
	ConvertStringToMasChar(name, _name);
	ConvertStringToMasChar(type, _type);
	ConvertStringToMasChar(clientName, _clientName);
	_buyoutPrice = buyoutPrice;
	_price = price;
	_age = age;
}

void Product::SetPrice(int newPrice)
{
	_price = newPrice;
}

void Product::SetName(string newName)
{
	ConvertStringToMasChar(newName, _name);
}

Product& Product::operator=(const Product& p2)
{
	CopyFromCharToChar(p2._name, _name);
	CopyFromCharToChar(p2._type, _type);
	CopyFromCharToChar(p2._clientName, _clientName);
	_buyoutPrice = p2._buyoutPrice;
	_price = p2._price;
	_age = p2._age;
	return *this;
}

Product::Product()
{
	_buyoutPrice = 0;
	_price = 0;
	_age = 0;
}

Product::Product(string name, string type, string clientName, int buyoutPrice, int price, int age)
{
	Set(name, type, clientName, buyoutPrice, price, age);
}

string Product::GetName()
{
	return ConvertMasCharToString(_name);
}

string Product::GetClientName()
{
	return ConvertMasCharToString(_clientName);
}

string Product::GetType()
{
	return ConvertMasCharToString(_type);
}

int Product::GetBuyOutPrice()
{
	return _buyoutPrice;
}

void Product::GetInfoFromFile(fstream& fs)
{
	fs.read((char*)&_name, sizeof(char) * 50);
	fs.read((char*)&_type, sizeof(char) * 50);
	fs.read((char*)&_clientName, sizeof(char) * 100);
	fs.read((char*)&_buyoutPrice, sizeof(int));
	fs.read((char*)&_price, sizeof(int));
	fs.read((char*)&_age, sizeof(int));
}

int Product::GetPrice()
{
	return _price;
}

int Product::GetAge()
{
	return _age;
}

void Product::PutInfoIntoFile(fstream& fs)
{
	fs.write((char*)&_name, sizeof(char) * 50);
	fs.write((char*)&_type, sizeof(char) * 50);
	fs.write((char*)&_clientName, sizeof(char) * 100);
	fs.write((char*)&_buyoutPrice, sizeof(int));
	fs.write((char*)&_price, sizeof(int));
	fs.write((char*)&_age, sizeof(int));
}

void Product::ShowInfo(bool forClient)
{
	string out = ConvertMasCharToString(_name);
	FillSpaces(out, 16 - out.size());
	out += ConvertMasCharToString(_type);
	FillSpaces(out, 16 - ConvertMasCharToString(_type).size());
	if (forClient == false)
	{
		out += ConvertMasCharToString(_clientName);
		FillSpaces(out, 17 - ConvertMasCharToString(_clientName).size());
		if (_price == 0)
		{
			out += to_string(_buyoutPrice);
			FillSpaces(out, 17 - to_string(_buyoutPrice).size());
		}
		else
		{
			out += to_string(_price);
			FillSpaces(out, 17 - to_string(_price).size());
		}
	}
	else
	{
		out += to_string(_buyoutPrice);
		FillSpaces(out, 17 - to_string(_buyoutPrice).size());
	}
	out += to_string(_age);
	FillSpaces(out, 20 - to_string(_age).size());
	cout << out;
}

bool operator==(const Product& p1, const Product& p2)
{
	bool b1 = StrCmp1(p1._name, p2._name) == 0;
	bool b2 = StrCmp1(p1._type, p2._type) == 0;
	bool b3 = StrCmp1(p1._clientName, p2._clientName) == 0;
	bool b4 = p1._buyoutPrice == p2._buyoutPrice;
	bool b5 = p1._price == p2._price;
	bool b6 = p1._age == p2._age;
	return b1 && b2 && b3 && b4 && b5 && b6;
}
