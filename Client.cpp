#include "Client.h"

void Client::SortRequestsByName()
{
	list<Request>::iterator i = _requests.begin();
	list<Request>::iterator j;
	for (; i != _requests.end(); i++)
	{
		for (j = i; j != _requests.end(); j++)
		{
			if (i->GetProduct().GetName() > j->GetProduct().GetName())
			{
				swap<Request>(*i, *j);
			}
		}
	}
}

void Client::SortRequestsBuyoutPrice()
{
	list<Request>::iterator i = _requests.begin();
	list<Request>::iterator j;
	for (; i != _requests.end(); i++)
	{
		for (j = i; j != _requests.end(); j++)
		{
			if (i->GetProduct().GetBuyOutPrice() > j->GetProduct().GetBuyOutPrice())
			{
				swap<Request>(*i, *j);
			}
		}
	}
}

void Client::FilterRequestByStatus()
{
	system("cls");
	int i = 0;
	for (Request request : _requests)
	{
		if (request.GetState() == 0)
		{
			cout << "������� ������������: " << endl;
			break;
		}
		i++;
	}
	if (i == _requests.size())
	{
		cout << "������������ �� �������." << endl;
		return;
	}
	list<Request>::iterator it = _requests.begin();
	advance(it, i);
	cout.setf(ios::left);
	cout << setw(8) << "�";
	cout << setw(16) << "��� ������";
	cout << setw(16) << "��� ������";
	cout << setw(17) << "���� ������";
	cout << setw(20) << "������� ������";
	cout << setw(20) << "������ �������" << endl;
	cout.unsetf(ios::left);
	i = 1;
	for (; it != _requests.end(); *it++)
	{
		if (it->GetState() == 0)
		{
			cout << i << "    "; it->ShowInfo(true); cout << endl;
			i++;
		}
	}
}

void Client::FindRequestByName(string name)
{
	system("cls");
	int i = 0;
	for (Request request : _requests)
	{
		if (request.GetProduct().GetName() == name)
		{
			cout << "������� ������������: " << endl;
			break;
		}
		i++;
	}
	if (i == _requests.size())
	{
		cout << "������������ �� �������." << endl;
		return;
	}
	list<Request>::iterator it = _requests.begin();
	advance(it, i);
	cout.setf(ios::left);
	cout << setw(8) << "�";
	cout << setw(16) << "��� ������";
	cout << setw(16) << "��� ������";
	cout << setw(17) << "���� ������";
	cout << setw(20) << "������� ������";
	cout << setw(20) << "������ �������" << endl;
	cout.unsetf(ios::left);
	i = 1;
	for (; it != _requests.end(); *it++)
	{
		if (it->GetProduct().GetName() == name)
		{
			cout << i << "       "; it->ShowInfo(true); cout << endl;
			i++;
		}
	}
}

Client::Client()
{
	_balance = 0;
	FullName[0] = '\0';
}

Client::Client(const Client& obj) : User(obj)
{
	_balance = obj._balance;	
}

Client::~Client()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Client::BuyAProduct(Store& store)
{
	if (store.GetProductsCount() == 0)
	{
		cout << "����� ������." << endl;
		return;
	}

	store.ShowProducts();
	cout << "�������� ����� (0 - ������): " << endl;
	int choice = MakeAChoice(0, store.GetProductsCount()) - 1;
	if (choice != -1)
	{
		Product product = store.GetProduct(choice);
		if (product.GetPrice() > _balance)
		{
			cout << "������������ ������� ��� ������� ����� ������." << endl;
		}
		else
		{
			_balance -= product.GetPrice();
			store.SetBalance(store.GetBalance() + product.GetPrice());
			store.RemoveProduct(choice);
			cout << "�������!" << endl;
		}
	}
}

Request& Client::CreateRequest(Store& store)
{
	string name;
	string type;
	string clientName;
	int buyoutPrice;
	int price;
	int age;
	Product product;
	cout << "������� ��� ������: ";
	cin.clear();
	cin.ignore(50, '\n');
	getline(cin, name);
	cout << "������� ��� ������: ";
	getline(cin, type);
	cout << "������� ���� ������: ";
	buyoutPrice = MakeAChoice(10, 1000);
	cout << "������� ������� ������: ";
	age = MakeAChoice(1, 20);
	product.Set(name, type, ConvertMasCharToString(FullName), buyoutPrice, 0, age);
	Request request(product, 0);
	store.AddRequest(request);
	_requests.push_back(request);
	return request;
}

Request& Client::GetRequest(int number)
{
	list<Request>::iterator request = _requests.begin();
	advance(request, number);
	return *request;
}

Request& Client::GetRequest(Request& request)
{
	for (auto& clientRequest : _requests)
	{
		if (clientRequest == request)
		{
			return clientRequest;
		}
	}
}

void Client::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetClientPath() + ConvertMasCharToString(FullName), ios::out | ios::trunc | ios::binary);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.write((char*)&_balance, sizeof(int));
	int requestsSize = _requests.size();
	fs.write((char*)&requestsSize, sizeof(int));
	for (auto request : _requests)
	{
		request.PutInfoIntoFile(fs);
	}
	fs.close();
}

void Client::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetClientPath() + fullName, ios::in | ios::binary);
	ConvertStringToMasChar(fullName, FullName);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.read((char*)&_balance, sizeof(int));
	int requestsSize;
	fs.read((char*)&requestsSize, sizeof(int));
	Request newRequest;
	for (int i = 0; i < requestsSize; i++)
	{
		newRequest.GetInfoFromFile(fs);
		_requests.push_back(newRequest);
	}
	fs.close();
}

void Client::MakeADeposit()
{
	cout << "������� ����� �������� (������� - 50, �������� - 1000): " << endl;
	int dep = MakeAChoice(50, 100000);
	if (ReadBankCard() == true)
	{
		_balance += dep;
	}
}

void Client::ShowBalance()
{
	cout << "������: " << _balance << '$' << endl;
}

int Client::GetBalance()
{
	return _balance;
}

void Client::SetBalance(int newBalance)
{
	_balance = newBalance;
}

void Client::ShowRequests()
{
	if (_requests.empty() == true)
	{
		cout << "������ �������� ����!" << endl;
		return;
	}
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		cout.setf(ios::left);
		cout << setw(5) << "�";
		cout << setw(16) << "��� ������";
		cout << setw(16) << "��� ������";
		cout << setw(17) << "���� ������";
		cout << setw(20) << "������� ������";
		cout << setw(20) << "������ �������" << endl;
		cout.unsetf(ios::left);
		int i = 1;
		for (Request request : _requests)
		{
			cout << i << "    "; request.ShowInfo(true); cout << endl;
			i++;
		}
		cout << endl;
		cout << "1 - ������������� �� ����� ������." << endl;
		cout << "2 - ������������� �� ���� ������." << endl;
		cout << "3 - ������ �� ������� �������." << endl;
		cout << "4 - ����� �� ����� ������." << endl;
		cout << "5 - ��������� ��������." << endl;
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			SortRequestsByName();
			break;
		}
		case 2:
		{
			SortRequestsBuyoutPrice();
			break;
		}
		case 3:
		{
			FilterRequestByStatus();
			cout << "������� �� ����� �������, ����� ����������..." << endl;
			_getch();
			break;
		}
		case 4:
		{
			cout << "������� ��� ������, ������� ������ �����: " << endl;
			string name;
			cin.clear();
			cin.ignore(50, '\n');
			getline(cin, name);
			FindRequestByName(name);
			cout << "������� �� ����� �������, ����� ����������..." << endl;
			_getch();
			break;
		}
		case 5:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
	}
}
