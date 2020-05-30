#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

int strToInt(char* source, int &index, bool updateIndex = true)
{
	int res = 0, i = index;
	while (source[i] == ' ') i++;
	while (source[i] >= '0' and source[i] <= '9')
	{
		res = 10 * res + (source[i++] - '0');
	}
	if (updateIndex)
		index = i;
	return res;
}

void extractWord(const char* source, char* destination, int& startIndex, int limit, bool keepStartIndex = false, char divider = ' ')
{
	int index = startIndex;
	while (source[index] == ' ' or source[index] == 9 or source[index] == divider) index++;
	bool endOfWord = false;
	for (int i = 0; i < limit and !endOfWord; i++)
	{
		if (source[index] == divider or source[index] == '\0' or source[index] == ' ' or source[index] == 9)
		{
			endOfWord = true;
			destination[i] = '\0';
		}
		else
		{
			destination[i] = source[index++];
		}

		if (i == limit - 1 && destination[i] != '\0')
			destination[0] = '\0';
	}
	if (!keepStartIndex)
		startIndex = index;
	return;
}

#include "ImageFile.hpp"
#include "TimePeriod.hpp"
#include "ListOfVisits.hpp"
#include "ListOfDestinations.hpp"
#include "FriendList.hpp"
#include "UsersDatabase.hpp"
#include "User.hpp"

void Destination::printRatings(UsersDatabase database)
{
	int numberOfGrades = 0;
	double avgGrade = 0;
	int numberOfUsers = database.getNumberOfUsers();
	for (int i = 0; i < numberOfUsers; i++)
	{
		int len = strlen(database[i].getUsername()) + 4;
		char* filename = new char[len];
		strcpy(filename, database[i].getUsername());
		strcat(filename, ".db");
		ifstream f;
		f.open(filename, ios::binary);
		if (f.fail())
		{
			cout << "Failed to open " << filename << endl;
			delete[] filename;
			continue;
		}
		User current;
		current.readFromFile(f);
		f.close();
		bool found = false;
		int numberOfVisits = current.getNumberOfVisits();
		for (int i = 0; i < numberOfVisits and !found; i++)
		{
			if (!strcmp(current[i].getCity(), city) and !strcmp(current[i].getCountry(), country))
			{
				double currentGrade = current[i].getGrade();
				avgGrade = (avgGrade * numberOfGrades + currentGrade) / (numberOfGrades + 1);
				numberOfGrades++;
				cout << current.getUsername() << " " << currentGrade << endl;
				found = true;
			}
		}
		delete[] filename;
	}
	if (avgGrade > 0)
		cout << "Average grade: " << avgGrade << endl;
	else cout << "No ratings yet\n";
}
void ListOfDestinations::load(UsersDatabase database)
{
	*this = ListOfDestinations();
	int numberOfUsers = database.getNumberOfUsers();
	for (int i = 0; i < numberOfUsers; i++)
	{
		int len = strlen(database[i].getUsername()) + 4;
		char* filename = new char[len];
		strcpy(filename, database[i].getUsername());
		strcat(filename, ".db");
		ifstream f;
		f.open(filename, ios::binary);
		if (f.fail())
		{
			cout << "Failed to open " << filename << endl;
			delete[] filename;
			continue;
		}
		User current;
		current.readFromFile(f);
		f.close();
		int numberOfVisits = current.getNumberOfVisits();
		for (int i = 0; i < numberOfVisits; i++)
		{
			addDestination(Destination(current[i].getCity(), current[i].getCountry()));
		}
		delete[] filename;
	}
}
void startup()
{
	cout << "Possible actions:\n";
	cout << "login <username> <password>              - log into an existing account\n";
	cout << "register <username> <password> <email>   - register new account\n";
	cout << "exit                                     - exit program\n";
	cout << endl;
}

void afterLogin()
{
	cout << "Possible actions:\n";
	cout << "destinations                             - view list of all recorded destinations\n";
	cout << "visits                                   - view list of visits\n";
	cout << "deletevisit <visit#>                     - delete visit #<visit#>\n";
	cout << "newvisit                                 - add new visit\n";
	cout << "friends                                  - view list of friends\n";
	cout << "addfriend <user>                         - add <user> as a friend\n";
	cout << "removefriend <user>                      - remove <user> as a friend\n";
	cout << "comments <city>, <country>               - view comments for <city>, <country> left by your friends\n";
	cout << "ratings <city>, <country>                - view all ratings for <city>, <country>\n";
	cout << "logout                                   - log out from current account\n";
	cout << "exit                                     - exit program\n";
	cout << endl;
}

int main()
{
	UsersDatabase database;
	ListOfDestinations destinations;
	ifstream f;
	f.open("users.db", ios::binary);
	database.readFromFile(f);
	f.close();
	//database.print();
	destinations.load(database);
	//destinations.print();
	User user;
	bool loggedIn = false;
	char command[64] = "open";
	do
	{
		if(!loggedIn)
		{
			startup();
			char inputLine[1024];
			cout << "> ";
			cin.getline(inputLine, 1024);
			int index = 0;
			extractWord(inputLine, command, index, 64);
			if (!strcmp(command, "login"))
			{
				cout << endl;
				char username[64];
				char password[64];
				extractWord(inputLine, username, index, 64);
				extractWord(inputLine, password, index, 64);
				if (database.usernameIsAvailable(username))
				{
					cout << "Username " << username << " is available.\nUse register <username> <password> <email> to register \n\n";
				}
				else
				{
					int numberOfUsers = database.getNumberOfUsers();
					for (int i = 0; i < numberOfUsers; i++)
					{
						if (!strcmp(password, database[i].getPassword()))
						{
							loggedIn = true;
							user.setUsername(username);
							user.loadDatabase();
							cout << "Successfully logged in!\nWelcome, " << username << "!\n\n";
						}
					}
					if (!loggedIn)
						cout << "Wrong password, please try again...\n\n";
				}
			}
			else if (!strcmp(command, "register"))
			{
				cout << endl;
				char username[64];
				char password[64];
				char email[64];
				extractWord(inputLine, username, index, 64);
				extractWord(inputLine, password, index, 64);
				extractWord(inputLine, email, index, 64);
				if (!database.usernameIsAvailable(username))
				{
					cout << "Username is already taken...\n";
				}
				else
				{
					if (!user.setUsername(username))
						cout << "Invalid username.\nUsername can contain only lowercase letters(a - z),\nuppercase letters(A - Z) and numbers (0 - 9)\n";
					else
					{
						user.setPassword(password);

						if (!user.setEmail(email))
						{
							cout << "Invalid email.\nEmail can contain only lowercase letters(a - z),\nuppercase letters(A - Z), numbers (0 - 9), '.' and '@'\n";
						}
						else
						{
							database.addUser(user);
							cout << "Successfully registered!\nWelcome, " << username << "!" << endl;
							user.saveDatabase();
							user.print();
							loggedIn = true;
						}
					}
				}
			}
			else if (!strcmp(command, "admin"))
			{
				cout << endl;
				database.print();
			}
		}
		else
		{
			char inputLine[1024];
			cout << "> ";
			cin.getline(inputLine, 1024);
			int index = 0;
			extractWord(inputLine, command, index, 64);
			if (!strcmp(command, "logout"))
			{
				cout << "Logging out...\n\n";
				user.saveDatabase();
				user = User();
				loggedIn = false;
			}
			else if (!strcmp(command, "help"))
			{
				cout << endl;
				afterLogin();
			}
			else if (!strcmp(command, "destinations"))
			{
				cout << endl;
				int count = destinations.getNumberOfDestinations();
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ") ";
					destinations[i].print();
					cout << endl;
					destinations[i].printRatings(database);
					cout << endl;
				}
			}
			else if (!strcmp(command, "visits"))
			{
				cout << endl;
				user.printVisits();
			}
			else if (!strcmp(command, "newvisit"))
			{
				cout << endl;
				destinations.addDestination(user.inputNewVisit());
			}
			else if (!strcmp(command, "deletevisit"))
			{
				int number = strToInt(inputLine, index);
				if (number < 1 or number > user.getNumberOfVisits())
				{
					cout << "Invalid index\n";
				}
				else
				{
					user.removeVisit(number - 1);
					user.saveDatabase();
					destinations.load(database);
					cout << "Visit has been deleted\n";
				}
			}
			else if (!strcmp(command, "friends"))
			{
				cout << endl;
				user.printFriends();
			}
			else if (!strcmp(command, "addfriend"))
			{
				char username[64];
				extractWord(inputLine, username, index, 64);
				if (!strcmp(user.getUsername(), username))
					cout << "You can't add yourself as a friend :)\n";
				else if (database.usernameIsAvailable(username))
					cout << "No user with that username\n";
				else
				{
					user.addFriend(username);
					User buddy;
					buddy.setUsername(username);
					buddy.loadDatabase();
					buddy.addFriend(user.getUsername());
					buddy.saveDatabase();
					user.saveDatabase();
					cout << "Added " << username << " as a friend\n";
				}
			}
			else if (!strcmp(command, "removefriend"))
			{
				char username[64];
				extractWord(inputLine, username, index, 64);
				if (!strcmp(user.getUsername(), username))
					cout << "You can't remove yourself as a friend :(\n";
				else if (!user.isFriend(username))
					cout << "No friend with that username\n";
				else
				{
					user.removeFriend(username);
					User buddy;
					buddy.setUsername(username);
					buddy.loadDatabase();
					buddy.removeFriend(user.getUsername());
					buddy.saveDatabase();
					user.saveDatabase();
					cout << "Removed " << username << " as a friend\n";
				}
			}
			else if (!strcmp(command, "comments"))
			{
				cout << endl;
				char city[64];
				char country[64];
				extractWord(inputLine, city, index, 64, false, ',');
				index++;
				extractWord(inputLine, country, index, 64);
				Destination target(city, country);
				user.printFriendsCommentsOn(target);
			}
			else if (!strcmp(command, "ratings"))
			{
				cout << endl;
				char city[64];
				char country[64];
				extractWord(inputLine, city, index, 64, false, ',');
				index++;
				extractWord(inputLine, country, index, 64);
				Destination target(city, country);
				target.printRatings(database);
			}
		}
	} while (strcmp(command, "exit"));
	cout << "Exiting...\n";
	ofstream g;
	g.open("users.db", ios::binary | ios::trunc);
	database.writeToFile(g);
	g.close();
}