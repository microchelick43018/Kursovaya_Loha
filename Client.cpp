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
			cout << "Найдено соответствие: " << endl;
			break;
		}
		i++;
	}
	if (i == _requests.size())
	{
		cout << "Соответствий не найдено." << endl;
		return;
	}
	list<Request>::iterator it = _requests.begin();
	advance(it, i);
	cout.setf(ios::left);
	cout << setw(8) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Цена выкупа";
	cout << setw(20) << "Возраст товара";
	cout << setw(20) << "Статус запроса" << endl;
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
			cout << "Найдено соответствие: " << endl;
			break;
		}
		i++;
	}
	if (i == _requests.size())
	{
		cout << "Соответствий не найдено." << endl;
		return;
	}
	list<Request>::iterator it = _requests.begin();
	advance(it, i);
	cout.setf(ios::left);
	cout << setw(8) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Цена выкупа";
	cout << setw(20) << "Возраст товара";
	cout << setw(20) << "Статус запроса" << endl;
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
		cout << "Склад пустой." << endl;
		return;
	}

	store.ShowProducts();
	cout << "Выберите товар (0 - отмена): " << endl;
	int choice = MakeAChoice(0, store.GetProductsCount()) - 1;
	if (choice != -1)
	{
		Product product = store.GetProduct(choice);
		if (product.GetPrice() > _balance)
		{
			cout << "Недостаточно средств для покупки этого товара." << endl;
		}
		else
		{
			_balance -= product.GetPrice();
			store.SetBalance(store.GetBalance() + product.GetPrice());
			store.RemoveProduct(choice);
			cout << "Успешно!" << endl;
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
	cout << "Введите имя товара: ";
	cin.clear();
	cin.ignore(50, '\n');
	getline(cin, name);
	cout << "Введите тип товара: ";
	getline(cin, type);
	cout << "Введите цену выкупа: ";
	buyoutPrice = MakeAChoice(10, 1000);
	cout << "Введите возраст товара: ";
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
	cout << "Введите сумму депозита (минимум - 50, максимум - 1000): " << endl;
	int dep = MakeAChoice(50, 100000);
	if (ReadBankCard() == true)
	{
		_balance += dep;
	}
}

void Client::ShowBalance()
{
	cout << "Баланс: " << _balance << '$' << endl;
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
		cout << "Список запросов пуст!" << endl;
		return;
	}
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		cout.setf(ios::left);
		cout << setw(5) << "№";
		cout << setw(16) << "Имя товара";
		cout << setw(16) << "Тип товара";
		cout << setw(17) << "Цена выкупа";
		cout << setw(20) << "Возраст товара";
		cout << setw(20) << "Статус запроса" << endl;
		cout.unsetf(ios::left);
		int i = 1;
		for (Request request : _requests)
		{
			cout << i << "    "; request.ShowInfo(true); cout << endl;
			i++;
		}
		cout << endl;
		cout << "1 - Отсортировать по имени товара." << endl;
		cout << "2 - Отсортировать по цене выкупа." << endl;
		cout << "3 - Фильтр по статусу запроса." << endl;
		cout << "4 - Поиск по имени товара." << endl;
		cout << "5 - Закончить просмотр." << endl;
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
			cout << "Нажмите на любую клавишу, чтобы продолжить..." << endl;
			_getch();
			break;
		}
		case 4:
		{
			cout << "Введите имя товара, который хотите найти: " << endl;
			string name;
			cin.clear();
			cin.ignore(50, '\n');
			getline(cin, name);
			FindRequestByName(name);
			cout << "Нажмите на любую клавишу, чтобы продолжить..." << endl;
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
