//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>

#include "Visit.h"
#include "User.h"

bool login(User &current)
{
	char username[128], password[128];
	cout << "Username: ";
	cin.getline(username, 128);

	ifstream f;
	f.open("users.db", ios::binary);

	bool userExists = false;
	while (f and !userExists)
	{
		current.read(f);
		if (!strcmp(current.getUsername(), username))
		{
			userExists = true;
		}
	}
	if (!userExists)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "Password: ";
			cin.getline(password, 128);
			if (!strcmp(password, current.getPassword()))
			{
				return true;
			}
			cout << "Wrong password, you have "<< 2-i<<" attempt(s) left\n";
		}
		return false;
	}
	f.close();
}

int main()
{
	Visit personalDatabase;
	personalDatabase.setDestination("Sofia", "Bulgaria");
	personalDatabase.setTimePeriod(2020, 3, 8, 2020, 6, 1);
	personalDatabase.setGrade(1);
	personalDatabase.setComment("This quarantine fucking sucks, man, I miss the homies");
	personalDatabase.setNumberOfPhotos(2);
	personalDatabase.setPhoto(1, "dickpick.png");
	personalDatabase.setPhoto(0, "sittingontoilet.jpeg");
	personalDatabase.print();
	ifstream f;
	f.open("Miteshan.db", ios::binary);
	personalDatabase.read(f);
	f.close();
	personalDatabase.print();
	return 0;





	/*

	User current;
	char command[64];
	cout << "Do you already have an account? ('No' - register new account; 'Yes' - log in)\n> ";
	cin.getline(command, 64);
	while (strcmp(command, "Yes") and strcmp(command, "No"))
	{
		cout << "Unknown command, please try again:\n'No' - register new account; 'Yes' - log in\n> ";
		cin.getline(command, 64);
	}
	if (!strcmp(command, "Yes"))
	{
		if (login(current))
		{
			cout << "\nSuccessful login\n";
		}
		else
		{
			cout << "\nUnsuccessfil login, initiating self-destruct protocol\n";
			return 0;
		}
		current.print();
	}*/
}

// users.db