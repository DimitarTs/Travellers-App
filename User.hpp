class User : public UserInfo, public FriendList, public ListOfVisits
{
public:
	/*User();
	User(const User& other);
	User& operator=(const User& other);*/

	void print() const;

	Destination inputNewVisit();

	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
	void printFriendsCommentsOn(const Destination dest) const;
	void saveDatabase() const;
	void loadDatabase();
};
//User::User():UserInfo(), FriendList(), ListOfVisits() {}
//User::User(const User& other) : UserInfo(other), FriendList(other), ListOfVisits(other) {}
//User& User::operator=(const User& other)
//{
//	UserInfo::operator=(other);
//	FriendList::operator=(other);
//	ListOfVisits::operator=(other);
//	return *this;
//}

void User::print() const
{
	//cout << "Username: " << getUsername() << "\nE-Mail: " << getEmail() << "\n\n";
	UserInfo::print(1);
	cout << "\n\n";
	FriendList::print();
	cout << "\n";
	ListOfVisits::print();
}

Destination User::inputNewVisit()
{
	Visit addition;
	addition.input();
	addVisit(addition);
	saveDatabase();
	return addition;
}

void User::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "User::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	UserInfo::writeToFile(f);
	FriendList::writeToFile(f);
	ListOfVisits::writeToFile(f);
}
void User::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "User::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	UserInfo::readFromFile(f);
	FriendList::readFromFile(f);
	ListOfVisits::readFromFile(f);
}

void User::printFriendsCommentsOn(const Destination dest) const
{
	for (int i = 0; i < FriendList::getNumberOfFriends(); i++)
	{
		int len = strlen(getFriend(i)) + 4;
		char* filename = new char[len];
		strcpy(filename, getFriend(i));
		strcat(filename, ".db");
		User current;
		ifstream f;
		f.open(filename, ios::binary);
		current.readFromFile(f);
		f.close();
		int numberOfVisits = current.getNumberOfVisits();
		for (int i = 0; i < numberOfVisits; i++)
		{
			if (!strcmp(current[i].getCity(), dest.getCity()) and !strcmp(current[i].getCountry(), dest.getCountry()))
			{
				if (current[i].getComment() != nullptr)
					cout << current.getUsername() << ": " << current[i].getComment() << endl;
			}
		}
		delete[] filename;
	}
}

void User::saveDatabase() const
{
	int len = strlen(getUsername()) + 4;
	char* filename = new char[len];
	strcpy(filename, getUsername());
	strcat(filename, ".db");
	ofstream g;
	g.open(filename, ios::binary | ios::trunc);
	writeToFile(g);
	g.close();
	delete[] filename;
}
void User::loadDatabase()
{
	int len = strlen(getUsername()) + 4;
	char* filename = new char[len];
	strcpy(filename, getUsername());
	strcat(filename, ".db");
	ifstream g;
	g.open(filename, ios::binary);
	readFromFile(g);
	g.close();
	delete[] filename;
}