#include "Owner.h"

Owner::Owner()
{
}

Owner::~Owner()
{
	if (FullName[0] == '\0')
	{
		PutInfoIntoFile();
	}
}

void Owner::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetOwnerPath() + fullName, ios::binary | ios::in);
	ConvertStringToMasChar(fullName, FullName);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.close();
}

void Owner::GiveAdminsSalary(Store& store)
{
	if (store.GetBalance() < 400 * store.GetAdminsCount())
	{
		cout << "� �������� ������������ ����� ��� ������ ��������." << endl;
	}
	else
	{
		store.SetBalance(store.GetBalance() - store.GetAdminsCount() * 400);
		cout << "��� �������������� (" << store.GetAdminsCount() << ") ������� �������� ��������!" << endl;
	}
}

void Owner::PutInfoIntoFile()
{
	fstream fs;
	fs.open(ConnectStringAndChar(FileManager::GetOwnerPath(), FullName), ios::binary | ios::out | ios::trunc);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.close();
}

void Owner::ShowStoreBalance(Store& store)
{
	cout << "������ �����������: " << store.GetBalance() << '$' << endl;
}

void Owner::ShowStoreRequestsHistory(Store& store)
{
	store.ShowRequestsForOwner();
}

void Owner::WithDrawMoney(Store& store)
{
	cout << "������� ����� ��� ������ (0 - ������): " << endl;
	int withdraw;
	withdraw = MakeAChoice(0, store.GetBalance());
	if (withdraw == 0)
	{
		cout << "������ ��������..." << endl;
	}
	else if (ReadBankCardNumber() == true)
	{
		store.SetBalance(store.GetBalance() - withdraw);
		cout << "�������!" << endl;
	}
}
