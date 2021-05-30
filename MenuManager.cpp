#include "MenuManager.h"
Store store;

namespace MenuManager
{
	void ShowClientMenu()
	{
		cout << "1 - Создать запрос на продажу товара." << endl;
		cout << "2 - Пополнить баланс." << endl;
		cout << "3 - Покупка." << endl;
		cout << "4 - Просмотр истории запросов." << endl;
		cout << "5 - Выход из аккаунта" << endl;
	}

	void MenuManager::ShowAdminMenu()
	{
		cout << "1 - Обслужить запросы." << endl;
		cout << "2 - Редакция товаров на складе." << endl;
		cout << "3 - Выход из аккаунта." << endl;
	}

	void MenuManager::ShowMainMenu()
	{
		cout << "1 - Войти как клиент." << endl;
		cout << "2 - Войти как администратор." << endl;
		cout << "3 - Войти как владелец." << endl;
		cout << "4 - Зарегистрироваться как клиент." << endl;
		cout << "5 - Зарегистрироваться как администратор." << endl;
		cout << "6 - Зарегистрироваться как владелец." << endl;
		cout << "7 - Выйти из программы." << endl;
	}

	void MenuManager::ShowOwnerMenu()
	{
		cout << "1 - Просмотреть историю всех запросов." << endl;;
		cout << "2 - Раздать зарплату администраторам (каждому по 400$)." << endl;
		cout << "3 - Вывод средств." << endl;
		cout << "4 - Выйти из программы." << endl;
	}
}

void MakingChoice::TabtoContinue()
{
	cout << "Нажмите любую клавишу, чтобы продолжить...";
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
