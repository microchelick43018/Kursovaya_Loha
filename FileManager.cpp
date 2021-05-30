#include "FileManager.h"
const string FileManager::CLIENT_PATH = "Clients/";
const string FileManager::ADMIN_PATH = "Admins/";
const string FileManager::OWNER_PATH = "Owners/";
const string FileManager::STORE_PATH = "Store";

string FileManager::GetAdminPath()
{
	return ADMIN_PATH;
}

string FileManager::GetClientPath()
{
	return CLIENT_PATH;
}

string FileManager::GetTablesPath()
{
	return OWNER_PATH;
}

string FileManager::GetStorePath()
{
	return STORE_PATH;
}

string FileManager::GetOwnerPath()
{
	return OWNER_PATH;
}

void FileManager::CreateAdminsDir()
{
	if (exists(ADMIN_PATH) == false)
	{
		create_directory(ADMIN_PATH);
	}
}

void FileManager::CreateClientsDir()
{
	if (exists(CLIENT_PATH) == false)
	{
		create_directory(CLIENT_PATH);
	}
}

void FileManager::CreateOwnersDir()
{
	if (exists(OWNER_PATH) == false)
	{
		create_directory(OWNER_PATH);
	}
}