#pragma once
#include "User.h"
#include "Product.h"
#include "Request.h"
#include "Store.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;
class Client : public User
{
private:
	int _balance;
	list<Request> _requests;

	void SortRequestsByName();
	void SortRequestsBuyoutPrice();
	void FilterRequestByStatus();
	void FindRequestByName(string name);
public:
	Client();

	Client(const Client& obj);

	~Client();

	void BuyAProduct(Store& store);

	Request& CreateRequest(Store& store);

	Request& GetRequest(int number);

	Request& GetRequest(Request& request);

	void GetInfoFromFile(string fullName) override;

	void PutInfoIntoFile() override;

	void MakeADeposit();

	void ShowBalance();

	int GetBalance();

	void SetBalance(int newBalance);

	void ShowRequests();
};

