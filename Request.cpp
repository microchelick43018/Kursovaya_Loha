#include "Request.h"

Request::Request()
{
	_state = 0;
}

Request::Request(Product product, int state)
{
	_state = state;
	_product = product;
}

Request::~Request()
{
}

void Request::GetInfoFromFile(fstream& fs)
{
	_product.GetInfoFromFile(fs);
	fs.read((char*)&_state, sizeof(int));
}

Product& Request::GetProduct()
{
	return _product;
}

int Request::GetState()
{
	return _state;
}

void Request::PutInfoIntoFile(fstream& fs)
{
	_product.PutInfoIntoFile(fs);
	fs.write((char*)&_state, sizeof(int));
}

void Request::SetState(int newState)
{
	_state = newState;
}

void Request::ShowInfo(bool forClient)
{
	_product.ShowInfo(forClient);
	if (_state == 0)
	{
		cout << "� ��������" << endl;
	}
	else if (_state == 1)
	{
		cout << "��������" << endl;
	}
	else if (_state == 2)
	{
		cout << "��������" << endl;
	}
}

void Request::ShowInfoForOwner(bool isBought)
{
	string out = _product.GetName();
	FillSpaces(out, 16 - out.size());
	out += _product.GetType();
	FillSpaces(out, 16 - _product.GetType().size());
	out += _product.GetClientName();
	FillSpaces(out, 17 - _product.GetClientName().size());
	out += to_string(_product.GetBuyOutPrice());
	FillSpaces(out, 17 - to_string(_product.GetBuyOutPrice()).size());
	if (_product.GetPrice() == 0)
	{
		out += '-';
		FillSpaces(out, 21);
	}
	else
	{
		out += to_string(_product.GetPrice());
		FillSpaces(out, 22 - to_string(_product.GetPrice()).size());
	}
	out += to_string(_product.GetAge());
	FillSpaces(out, 20 - to_string(_product.GetAge()).size());
	if (_state == 0)
	{
		out += "� ��������";
		FillSpaces(out, 9);
	}
	else if (_state == 1)
	{
		out += "��������";
		FillSpaces(out, 11);
	}
	else if (_state == 2)
	{
		out += "��������";
		FillSpaces(out, 11);
	}
	if (isBought)
	{
		out += "������";
	}
	else
	{
		out += "�� ������";
	}
	cout << out;
}

bool operator==(const Request& r1, const Request& r2)
{
	bool b1 = r1._product == r2._product;
	bool b2 = r1._state == r2._state;
	return b1 && b2;
}
