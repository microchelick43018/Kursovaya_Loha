#include "Store.h"

bool Store::CheckRequestproductInWareHouse(Product product)
{
	for (const Product& product_ : _products)
	{
		if (product == product_)
		{
			return true;
		}
	}
	return false;
}

Store::Store()
{
	fstream fs;
	fs.open(FileManager::GetStorePath(), ios::binary | ios::in);
	if (fs.is_open() == false)
	{
		fs.close();
		fs.open(FileManager::GetStorePath(), ios::binary | ios::out | ios::trunc);
		_balance = 5000;
		_adminsCount = 0;
	}
	else
	{
		fs.close();
		GetInfoFromFile();
	}
	fs.close();
}

Store::~Store()
{
	PutInfoIntoFile();
}

void Store::AddRequest(Request& request)
{
	_requests.push_back(request);
}

void Store::AddProduct(Product& product)
{
	_products.push_back(product);
}

int Store::GetAdminsCount()
{
	return _adminsCount;
}

int Store::GetBalance()
{
	return _balance;
}

int Store::GetProductsCount()
{
	return _products.size();
}

int Store::GetRequestsCount()
{
	return _requests.size();
}

Product& Store::GetProduct(int number)
{
	return _products[number];
}

Request& Store::GetRequest(int number)
{
	return _requests[number];
}

void Store::GetInfoFromFile()
{
	fstream fs;
	fs.open(FileManager::GetStorePath(), ios::binary | ios::in);
	int productsCount;
	int requestsCount;
	fs.read((char*)&productsCount, sizeof(int));
	Product newProduct;
	for (int i = 0; i < productsCount; i++)
	{
		newProduct.GetInfoFromFile(fs);
		_products.push_back(newProduct);
	}
	fs.read((char*)&requestsCount, sizeof(int));
	Request newRequest;
	for (int i = 0; i < requestsCount; i++)
	{
		newRequest.GetInfoFromFile(fs);
		_requests.push_back(newRequest);
	}
	fs.read((char*)&_balance, sizeof(int));
	fs.read((char*)&_adminsCount, sizeof(int));
}

void Store::IncAdminsCount()
{
	_adminsCount++;
}

void Store::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetStorePath(), ios::binary | ios::out | ios::trunc);
	int productsCount = _products.size();
	int requestsCount = _requests.size();
	fs.write((char*)&productsCount, sizeof(int));
	for (int i = 0; i < productsCount; i++)
	{
		_products[i].PutInfoIntoFile(fs);
	}
	fs.write((char*)&requestsCount, sizeof(int));
	for (int i = 0; i < requestsCount; i++)
	{
		_requests[i].PutInfoIntoFile(fs);
	}
	fs.write((char*)&_balance, sizeof(int));
	fs.write((char*)&_adminsCount, sizeof(int));
}

void Store::RemoveProduct(Product& product)
{
}

void Store::RemoveProduct(int number)
{
	_products.erase(_products.begin() + number);
}

void Store::SetBalance(int newBalance)
{
	_balance = newBalance;
}

void Store::ShowRequests()
{
	cout.setf(ios::left);
	cout << setw(5) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Имя клиента";
	cout << setw(17) << "Цена выкупа";
	cout << setw(20) << "Возраст товара";
	cout << setw(20) << "Статус запроса" << endl;
	cout.unsetf(ios::left);
	int i = 1;
	for (int i = 0; i < _requests.size(); i++)
	{
		cout << i << "    "; _requests[i].ShowInfo(false); cout << endl;
	}
}

void Store::ShowRequestsForOwner()
{
	if (_requests.size() == 0)
	{
		cout << "Склад пуст!" << endl;
		return;
	}
	cout.setf(ios::left);
	cout << setw(5) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Имя клиента";
	cout << setw(17) << "Цена выкупа";
	cout << setw(22) << "Цена в заведении";
	cout << setw(20) << "Возраст товара";
	cout << setw(20) << "Статус запроса";
	cout << setw(29) << "Статус товара на складе" << endl;
	cout.unsetf(ios::left);
	bool b;
	for (int i = 0; i < _requests.size(); i++)
	{
		b = CheckRequestproductInWareHouse(_requests[i].GetProduct());
		cout << i + 1 << "    "; _requests[i].ShowInfoForOwner(b); cout << endl;
	}
}

void Store::ShowProducts()
{
	cout.setf(ios::left);
	cout << setw(5) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Имя клиента";
	cout << setw(17) << "Цена товара";
	cout << setw(20) << "Возраст товара" << endl;
	cout.unsetf(ios::left);
	int i = 0;
	for (; i < _products.size(); i++)
	{
		cout << i + 1 << "    "; _products[i].ShowInfo(false); cout << endl;
	}
}

int Store::ShowUnservedRequests()
{
	SortRequstsByState();
	int i = 0;
	cout.setf(ios::left);
	cout << setw(5) << "№";
	cout << setw(16) << "Имя товара";
	cout << setw(16) << "Тип товара";
	cout << setw(17) << "Имя клиента";
	cout << setw(17) << "Цена выкупа";
	cout << setw(20) << "Возраст товара";
	cout << setw(20) << "Статус запроса" << endl;
	cout.unsetf(ios::left);
	for (; i < _requests.size(); i++)
	{
		if (_requests[i].GetState() == 0)
		{
			cout << i + 1 << "    "; _requests[i].ShowInfo(false);
		}
		else
		{
			break;
		}
	}
	return i;
}

void Store::SortRequstsByState()
{
	for (int i = 0; i < _requests.size() - 1; i++)
	{
		for (int j = i + 1; j < _requests.size(); j++)
		{
			if (_requests[i].GetState() > _requests[j].GetState())
			{
				swap<Request>(_requests[i], _requests[j]);
			}
		}
	}
}

void Store::SortProductsByName()
{
	for (int i = 0; i < _products.size() - 1; i++)
	{
		for (int j = 0; j < _products.size(); j++)
		{
			if (_products[i].GetName() > _products[j].GetName())
			{
				swap<Product>(_products[i], _products[j]);
			}
		}
	}
}

void Store::SortProductsByPrice()
{
	for (int i = 0; i < _products.size() - 1; i++)
	{
		for (int j = 0; j < _products.size(); j++)
		{
			if (_products[i].GetPrice() > _products[j].GetPrice())
			{
				swap<Product>(_products[i], _products[j]);
			}
		}
	}
}
