#include "User.h"

void User::EncryptPassword(char* password)
{
	auto hash_ = hash<string>{}(password);
	string result;
	result = to_string(hash_);
	ConvertStringToMasChar(result, password);
}

User::User()
{
	Password[0] = '\0';
	FullName[0] = '\0';
}

User::User(const User& obj)
{
	CopyFromCharToChar(obj.FullName, FullName);
	CopyFromCharToChar(obj.Password, Password);
}

User::~User()
{

}


void User::SignUp(string startPath)
{
	char password[100];
	cout << "������� ���� �����: ";
	cin.clear();
	cin.ignore(100, '\n');
	cin.getline(FullName, 100);
	bool isCorrected = false;
	while (isCorrected == false)
	{
		cout << "������� ����� ������: ";
		cin.getline(password, 100);
		system("cls");
		cout << "������� ������ ��� ���: ";
		cin.getline(Password, 100);
		if (ConvertMasCharToString(Password) == ConvertMasCharToString(password))
		{
			isCorrected = true;
			EncryptPassword(Password);
		}
		else
		{
			cout << "������ �� ���������. ���������� ��� ���." << endl;
		}
	}
}

bool User::LogIn(string startPath)
{
	fstream fs;
	char truePassword[100], tempPassword[100];
	bool isCorrected = false;
	while (isCorrected == false)
	{
		cout << "������� ���� �����: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin.getline(FullName, 100);
		fs.open(ConnectStringAndChar(startPath, FullName), ios::in | ios::binary);
		if (fs.is_open() == false)
		{
			cout << "�������� �����, ������� ��������� �������? 1 - ��, 2 - ���." << endl;
			int choice = MakeAChoice(2);
			if (choice == 2)
			{
				return false;
			}
			else
			{
				continue;
			}
		}
		isCorrected = true;
	}
	fs.read((char*)&truePassword, sizeof(char) * 100);
	isCorrected = false;
	while (isCorrected == false)
	{
		cout << "������� ������: ";
		cin.getline(tempPassword, 100);
		EncryptPassword(tempPassword);
		if (ConvertMasCharToString(truePassword) != ConvertMasCharToString(tempPassword))
		{
			cout << "�������� ������, ������� ��������� �������? 1 - ��, 2 - ���." << endl;
			int choice = MakeAChoice(2);
			if (choice == 2)
			{
				return false;
			}
			else
			{
				cin.clear();
				cin.ignore(100, '\n');
				continue;
			}
		}
		else
		{
			cout << "���� ��������!" << endl;
			CopyFromCharToChar(truePassword, Password);
			isCorrected = true;
		}
	}
	fs.close();
	return true;
}

string User::GetFullName()
{
	return ConvertMasCharToString(FullName);
}