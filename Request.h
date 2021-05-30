#pragma once
#include <fstream>
#include "Product.h"
class Request
{
private:
	int _state;// 0 - � ��������, 1 - ����� ������, 2 - ������ ��������
	Product _product;
public:
	Request();

	Request(Product product, int state);

	~Request();

	void GetInfoFromFile(fstream& fs);

	Product& GetProduct();

	int GetState();

	void PutInfoIntoFile(fstream& fs);

	void SetState(int newState);

	void ShowInfo(bool forClient);

	void ShowInfoForOwner(bool isBought);

	friend bool operator==(const Request& r1, const Request& r2);
};

