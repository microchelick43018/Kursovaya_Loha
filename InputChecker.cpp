#include "InputChecker.h"

bool TryParse(string str, int& value)
{
	try
	{
		size_t a = 0;
		value = stoi(str, &a);
		if (a != str.size())
		{
			throw false;
		}
		return true;
	}
	catch (...)
	{
		value = 0;
		return false;
	}
}

bool TryParse(string str, double& value)
{
	try
	{
		size_t a = 0;
		setlocale(LC_ALL, "en");
		value = stod(str, &a);
		setlocale(LC_ALL, "");
		if (a != str.size())
		{
			throw false;
		}
		return true;
	}
	catch (...)
	{
		value = 0;
		return false;
	}
}

int ReadInt()
{
	int value;
	string str;
	cin >> str;
	bool isCorrect = TryParse(str, value);
	while (isCorrect == false)
	{
		cout << "�������� ����, ��������� �������: ";
		cin >> str;
		isCorrect = TryParse(str, value);
	}
	return value;
}

void ReadMasChar(char* c, int size = 0)
{
	cin.clear();
	cin.ignore(size, '\n');
	cin.getline(c, size);
}


bool AskForEnd()
{
	int choice;
	cout << "������ ����������? 1 - ��, 2 - ���." << endl;
	choice = MakeAChoice(2);
	if (choice == 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double ReadDouble()
{
	double value;
	string str;
	cin >> str;
	bool isCorrect = TryParse(str, value);
	while (isCorrect == false)
	{
		cout << "�������� ����, ��������� �������: ";
		cin >> str;
		isCorrect = TryParse(str, value);
	}
	return value;
}

string ReadDate()
{
	string date;
	int i;
	bool isCorrected = false;
	while (isCorrected == false)
	{
		cin >> date;
		if (date.length() != 10 || date[2] != '.' || date[5] != '.')
		{
			system("cls");
			cout << "�������� ����. ��������� �������: ";
			continue;
		}
		for (i = 0; date[i] != '\0'; i++)
		{
			if ((date[i] < '0' || date[i] > '9') && i != 2 && i != 5)
			{
				cout << "�������� ����. ��������� �������: ";
				break;
			}
		}
		if (date[i] == '\0')
		{
			isCorrected = true;
		}
	}
	return date;
}

int MakeAChoice(int maxNumber)
{
	int choice = ReadInt();
	while (choice <= 0 || choice > maxNumber)
	{
		cout << "�������� ����, ��������� �������: " << endl;
		choice = ReadInt();
	}
	return choice;
}

int MakeAChoice(int minNumber, int maxNumber)
{
	int choice = ReadInt();
	while (choice < minNumber || choice > maxNumber)
	{
		cout << "�������� ����, ��������� �������: " << endl;
		choice = ReadInt();
	}
	return choice;
}

bool ReadBankCard()
{
	int i;
	string date;
	string CVC;
	bool isCorrected;
	if (ReadBankCardNumber() == false)
	{
		return false;
	}
	cout << "������� ���� (������ ���� 01/23): ";
	isCorrected = false;
	while (isCorrected == false)
	{
		cin >> date;
		if (date.length() != 5 || date[2] != '/')
		{
			cout << "�������� ����. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; date[i] != '\0'; i++)
		{
			if ((date[i] < '0' || date[i] > '9') && i != 2)
			{
				cout << "�������� ����. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (date[i] == '\0')
		{
			isCorrected = true;
		}
	}
	cout << "������� CVC (3 ����� �� ������� ������� �����): ";
	isCorrected = false;
	while (isCorrected == false)
	{
		cin >> CVC;
		if (CVC.length() != 3)
		{
			cout << "�������� ����. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; CVC[i] != '\0'; i++)
		{
			if (CVC[i] < '0' || CVC[i] > '9')
			{
				cout << "�������� ����. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (CVC[i] == '\0')
		{
			isCorrected = true;
		}
	}
	cout << "�������!" << endl;
	return true;
}

bool ReadBankCardNumber()
{
	string number;
	cout << "������� ����� ����� (��� ��������): ";
	bool isCorrected = false;
	int i;
	while (isCorrected == false)
	{
		cin >> number;
		if (number.length() != 16)
		{
			cout << "�������� ����. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; number[i] != '\0'; i++)
		{
			if (number[i] < '0' || number[i] > '9')
			{
				cout << "�������� ����. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (i == number.size())
		{
			isCorrected = true;
		}
	}
	return true;
}
