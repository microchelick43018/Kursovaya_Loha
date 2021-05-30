#include "MenuManager.h"
Store store;

namespace MenuManager
{
	void ShowClientMenu()
	{
		cout << "1 - ������� ������ �� ������� ������." << endl;
		cout << "2 - ��������� ������." << endl;
		cout << "3 - �������." << endl;
		cout << "4 - �������� ������� ��������." << endl;
		cout << "5 - ����� �� ��������" << endl;
	}

	void MenuManager::ShowAdminMenu()
	{
		cout << "1 - ��������� �������." << endl;
		cout << "2 - �������� ������� �� ������." << endl;
		cout << "3 - ����� �� ��������." << endl;
	}

	void MenuManager::ShowMainMenu()
	{
		cout << "1 - ����� ��� ������." << endl;
		cout << "2 - ����� ��� �������������." << endl;
		cout << "3 - ����� ��� ��������." << endl;
		cout << "4 - ������������������ ��� ������." << endl;
		cout << "5 - ������������������ ��� �������������." << endl;
		cout << "6 - ������������������ ��� ��������." << endl;
		cout << "7 - ����� �� ���������." << endl;
	}

	void MenuManager::ShowOwnerMenu()
	{
		cout << "1 - ����������� ������� ���� ��������." << endl;;
		cout << "2 - ������� �������� ��������������� (������� �� 400$)." << endl;
		cout << "3 - ����� �������." << endl;
		cout << "4 - ����� �� ���������." << endl;
	}
}

void MakingChoice::TabtoContinue()
{
	cout << "������� ����� �������, ����� ����������...";
	_getch();
}

void MakingChoice::WorkAsUser()
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowMainMenu();
		choice = MakeAChoice(7);
		switch (choice)
		{
		case 1:
		{
			shared_ptr<Client> client = make_shared<Client>();
			bool b = client->LogIn(FileManager::GetClientPath());
			if (b == true)
			{
				client->GetInfoFromFile(client->GetFullName());
				WorkAsClient(*client);
			}
			break;
		}
		case 2:
		{
			shared_ptr<Admin> admin = make_shared<Admin>();
			if (admin->LogIn(FileManager::GetAdminPath()) == true)
			{
				admin->GetInfoFromFile(admin->GetFullName());
				WorkAsAdmin(*admin);
			}
			break;
		}
		case 3:
		{
			shared_ptr<Owner> owner = make_shared<Owner>();
			if (owner->LogIn(FileManager::GetOwnerPath()) == true)
			{
				owner->GetInfoFromFile(owner->GetFullName());
				WorkAsOwner(*owner);
			}
			break;
		}
		case 4:
		{
			Client client;
			client.SignUp(FileManager::GetClientPath());
			WorkAsClient(client);
			break;
		}
		case 5:
		{
			Admin admin;
			admin.SignUp(FileManager::GetAdminPath());
			store.IncAdminsCount();
			WorkAsAdmin(admin);
			break;
		}
		case 6:
		{
			Owner owner;
			owner.SignUp(FileManager::GetOwnerPath());
			WorkAsOwner(owner);
			break;
		}
		case 7:
			exit = true;
			break;
		default:
			break;
		}
		system("cls");
	}
}

void MakingChoice::WorkAsClient(Client& client)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		client.ShowBalance();
		MenuManager::ShowClientMenu();
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			client.CreateRequest(store);
			break;
		}
		case 2:
		{
			client.MakeADeposit();
			break;
		}
		case 3:
		{
			client.BuyAProduct(store);
			break;
		}
		case 4:
		{
			client.ShowRequests();
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
		TabtoContinue();
		system("cls");
	}
	store.PutInfoIntoFile();
}

void MakingChoice::WorkAsAdmin(Admin& admin)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowAdminMenu();
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			admin.ServeRequest(store);
			break;
		}
		case 2:
		{
			admin.EditProducts(store);
			break;
		}
		case 3:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
	store.PutInfoIntoFile();
}

void MakingChoice::WorkAsOwner(Owner& owner)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		owner.ShowStoreBalance(store);
		MenuManager::ShowOwnerMenu();
		choice = MakeAChoice(4);
		switch (choice)
		{
		case 1:
		{
			owner.ShowStoreRequestsHistory(store);
			break;
		}
		case 2:
		{
			owner.GiveAdminsSalary(store);
			break;
		}
		case 3:
		{
			owner.WithDrawMoney(store);
			break;
		}
		case 4:
			exit = true;
			break;
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
}
