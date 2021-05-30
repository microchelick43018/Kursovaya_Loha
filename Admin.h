#pragma once
#include "User.h"
#include <fstream>
#include "Store.h"
#include "Client.h"
class Admin : public User
{
private:

public:
	Admin();

	~Admin();

	void EditProducts(Store& store);

	void ServeRequest(Store& store);

	void GetInfoFromFile(string fullName) override;

	void PutInfoIntoFile() override;
};

