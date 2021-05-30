#pragma once
#include "User.h"
#include "Product.h"
#include "InputChecker.h"
#include <fstream>
#include "Store.h"
#include <list>
class Owner : public User
{
private:

public:

	Owner();

	~Owner();

	void GetInfoFromFile(string fullName) override;

	void GiveAdminsSalary(Store& store);

	void PutInfoIntoFile() override;

	void ShowStoreBalance(Store& store);

	void ShowStoreRequestsHistory(Store& store);

	void WithDrawMoney(Store& store);
};

