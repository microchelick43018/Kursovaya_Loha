#include "Admin.h"

Admin::Admin()
{
	FullName[0] = '\0';
}

Admin::~Admin()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Admin::EditProducts(Store& store)
{
	if (store.GetProductsCount() == 0)
	{
		cout << "Склад пустой!" << endl;
		return;
	}
	store.ShowProducts();
	cout << "Выберите продукт, что хотите редактировать (0 - отмена):";
	int choice = MakeAChoice(0, store.GetProductsCount()) - 1;
	if (choice == -1)
	{
		system("cls");
		return;
	}
	else
	{
		Product& chosenProduct = store.GetProduct(choice);
		cout << "1 - Изменить цену." << endl;
		cout << "2 - Изменить название." << endl;
		choice = MakeAChoice(2);
		if (choice == 1)
		{
			cout << "Введите новую цену товара: ";
			int newPrice = MakeAChoice(10, 10000);
			chosenProduct.SetPrice(newPrice);
		}
		else
		{
			cout << "Введите новое название товара: " << endl;
			string newName;
			cin.clear();
			cin.ignore(50, '\n');
			getline(cin, newName);
			chosenProduct.SetName(newName);
		}
		cout << "Успешно!" << endl;
	}
}

void Admin::ServeRequest(Store& store)
{
	int sizeUR = store.ShowUnservedRequests();
	if (sizeUR == 0)
	{
		cout << "Список запросов пуст!" << endl;
		return;
	}
	cout << "Выберите запрос, который хотите обработать: ";
	int choice = MakeAChoice(store.GetRequestsCount()) - 1;
	Request& request = store.GetRequest(choice);
	Product& product = request.GetProduct();
	cout << "1 - принять, 2 - отклонить" << endl;
	int choice2 = MakeAChoice(2);
	Client client;
	client.GetInfoFromFile(product.GetClientName());
	if (choice2 == 1)
	{
		client.GetRequest(request).SetState(1);
		request.SetState(1);
		client.SetBalance(product.GetBuyOutPrice() + client.GetBalance());
		store.SetBalance(store.GetBalance() - product.GetBuyOutPrice());
		cout << "Введите новую цену: " << endl;
		int price = MakeAChoice(100, 10000);
		product.SetPrice(price);
		store.AddProduct(product);
	}
	else
	{
		client.GetRequest(request).SetState(2);
		request.SetState(2);
	}
}

void Admin::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetAdminPath() + fullName, ios::binary | ios::in);
	ConvertStringToMasChar(fullName, FullName);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.close();
}

void Admin::PutInfoIntoFile()
{
	fstream fs;
	fs.open(ConnectStringAndChar(FileManager::GetAdminPath(), FullName), ios::binary | ios::out | ios::trunc);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.close();
}
