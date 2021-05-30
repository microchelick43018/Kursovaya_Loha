#pragma once
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include "InputChecker.h"
#include "FileManager.h"
#include "IntStrCharWorker.h"
#include "Product.h"
#include "Request.h"
class Store
{
private:
	vector<Product> _products;
	vector<Request> _requests;
	int _balance;
	int _adminsCount;

	bool CheckRequestproductInWareHouse(Product product);
public:
	Store();

	~Store();

	void AddRequest(Request& request);

	void AddProduct(Product& product);

	int GetAdminsCount();

	int GetBalance();

	int GetProductsCount();

	int GetRequestsCount();

	Product& GetProduct(int number);

	Request& GetRequest(int number);

	void GetInfoFromFile();

	void IncAdminsCount();

	void PutInfoIntoFile();

	void RemoveProduct(Product& product);

	void RemoveProduct(int number);

	void SetBalance(int newBalance);

	void ShowRequests();

	void ShowRequestsForOwner();

	void ShowProducts();

	int ShowUnservedRequests();

	void SortRequstsByState();

	void SortProductsByName();

	void SortProductsByPrice();
};

