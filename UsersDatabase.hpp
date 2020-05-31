class UsersDatabase
{
	int numberOfUsers;
	UserInfo* users;
public:
	UsersDatabase();
	UsersDatabase(const UsersDatabase& other);
	~UsersDatabase();
	UsersDatabase& operator=(const UsersDatabase& other);

	UserInfo operator[](int index);
	int getNumberOfUsers() const;

	bool usernameIsAvailable(const char*) const;
	void addUser(const UserInfo);
	void removeUser(const UserInfo);

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
UsersDatabase::UsersDatabase(): numberOfUsers(0), users(nullptr) {}
UsersDatabase::UsersDatabase(const UsersDatabase& other): numberOfUsers(other.numberOfUsers)
{
	if (numberOfUsers > 0)
	{
		users = new UserInfo[numberOfUsers];
		for (int i = 0; i < numberOfUsers; i++)
			users[i] = other.users[i];
	}
	else users = nullptr;
}
UsersDatabase::~UsersDatabase()
{
	if (users != nullptr)
		delete[] users;
}
UsersDatabase& UsersDatabase::operator=(const UsersDatabase& other)
{
	if (this == &other)
		return *this;
	if (users != nullptr)
		delete[] users;
	numberOfUsers = other.numberOfUsers;
	if (numberOfUsers > 0)
	{
		users = new UserInfo[numberOfUsers];
		for (int i = 0; i < numberOfUsers; i++)
			users[i] = other.users[i];
	}
	else users = nullptr;

	return *this;
}

UserInfo UsersDatabase::operator[](int index)
{
	if (index >= 0 and index < numberOfUsers)
		return users[index];
	return UserInfo();
}
int UsersDatabase::getNumberOfUsers() const 
{ 
	return numberOfUsers; 
}
bool UsersDatabase::usernameIsAvailable(const char* username) const
{
	for (int i = 0; i < numberOfUsers; i++)
		if (!strcmp(username, users[i].getUsername()))
			return false;
	return true;
}

void UsersDatabase::addUser(const UserInfo user)
{
	if (!usernameIsAvailable(user.getUsername()))
		return;
	UserInfo* newUsers = new UserInfo[numberOfUsers + 1];
	for (int i = 0; i < numberOfUsers; i++)
		newUsers[i] = users[i];
	newUsers[numberOfUsers] = user;
	if (users != nullptr)
		delete[] users;
	numberOfUsers++;
	users = newUsers;
}
void UsersDatabase::removeUser(const UserInfo user)
{
	if (usernameIsAvailable(user.getUsername()))
		return;
	if (numberOfUsers == 1)
	{
		delete[] users;
		users = nullptr;
		numberOfUsers = 0;
		return;
	}

	UserInfo* newUsers = new UserInfo[numberOfUsers - 1];
	bool found = false;
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (users[i] == user)
			found = true;
		else if (!found)
			newUsers[i] = users[i];
		else
			newUsers[i - 1] = users[i];
	}
	delete[] users;
	numberOfUsers--;
	users = newUsers;
}

void UsersDatabase::print() const
{
	if (numberOfUsers == 0)
		cout << "No users in database\n";
	for (int i = 0; i < numberOfUsers; i++)
	{
		users[i].print(1);
		cout << endl;
	}
}

void UsersDatabase::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "UsersDatabase::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	f.write((char*)&numberOfUsers, sizeof(int));
	for (int i = 0; i < numberOfUsers; i++)
		users[i].writeToFile(f);
}
void UsersDatabase::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "UsersDatabase::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	if (users != nullptr)
		delete[] users;
	f.read((char*)&numberOfUsers, sizeof(int));
	users = new UserInfo[numberOfUsers];
	for (int i = 0; i < numberOfUsers; i++)
		users[i].readFromFile(f);
}