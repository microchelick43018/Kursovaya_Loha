#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <conio.h>
#include "InputChecker.h"
#include "FileManager.h"
#include "Client.h"
#include "Admin.h"
#include "Owner.h"
#include "Store.h"

using namespace std;

extern Store store;
namespace MenuManager
{
	void ShowClientMenu();

	void ShowAdminMenu();

	void ShowMainMenu();

	void ShowOwnerMenu();
}

namespace MakingChoice
{
	void WorkAsUser();

	void WorkAsClient(Client& client);

	void WorkAsAdmin(Admin& admin);

	void WorkAsOwner(Owner& owner);

	void TabtoContinue();
}

