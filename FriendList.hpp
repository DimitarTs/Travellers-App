class FriendList
{
	int numberOfFriends;
	char** friends;
public:
	FriendList();
	FriendList(const FriendList&);
	~FriendList();
	FriendList& operator=(const FriendList&);

	bool isFriend(const char*) const;
	bool isFriend(const UserInfo) const;

	void addFriend(const char*);
	void addFriend(const UserInfo);
	void removeFriend(const char*);
	void removeFriend(const UserInfo);

	const char* getFriend(int index) const
	{
		if (index < 0 or index >= numberOfFriends)
			index = 0;
		return friends[index];
	}
	int getNumberOfFriends() const { return numberOfFriends; }

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
FriendList::FriendList() : numberOfFriends(0), friends(nullptr) {}
FriendList::FriendList(const FriendList& other): numberOfFriends(other.numberOfFriends)
{
	if (numberOfFriends > 0)
	{
		friends = new char* [numberOfFriends];
		for (int i = 0; i < numberOfFriends; i++)
		{
			friends[i] = new char[strlen(other.friends[i]) + 1];
			strcpy(friends[i], other.friends[i]);
		}
	}
	else friends = nullptr;
}
FriendList::~FriendList()
{
	if (friends != nullptr)
	{
		for (int i = 0; i < numberOfFriends; i++)
			delete[] friends[i];
		delete[] friends;
	}
}
FriendList& FriendList::operator=(const FriendList& other)
{
	if (this == &other)
		return *this;
	if (friends != nullptr)
	{
		for (int i = 0; i < numberOfFriends; i++)
			delete[] friends[i];
		delete[] friends;
	}

	numberOfFriends = other.numberOfFriends;
	if (numberOfFriends > 0)
	{
		friends = new char* [numberOfFriends];
		for (int i = 0; i < numberOfFriends; i++)
		{
			friends[i] = new char[strlen(other.friends[i]) + 1];
			strcpy(friends[i], other.friends[i]);
		}
	}
	else friends = nullptr;

	return* this;
}

bool FriendList::isFriend(const char* other) const
{
	for (int i = 0; i < numberOfFriends; i++)
		if (!strcmp(friends[i], other))
			return true;
	return false;
}
bool FriendList::isFriend(const UserInfo other) const
{
	return isFriend(other.getUsername());
}

void FriendList::addFriend(const char* other)
{
	if (isFriend(other))
		return;
	char** newFriends = new char* [numberOfFriends + 1];
	for (int i = 0; i < numberOfFriends; i++)
		newFriends[i] = friends[i];
	newFriends[numberOfFriends] = new char[strlen(other) + 1];
	strcpy(newFriends[numberOfFriends], other);
	numberOfFriends++;
	delete[] friends;
	friends = newFriends;
}
void FriendList::addFriend(const UserInfo other)
{
	addFriend(other.getUsername());
}
void FriendList::removeFriend(const char* other)
{
	if (!isFriend(other))
		return;
	if (numberOfFriends == 1)
	{
		delete[] friends[0];
		delete[] friends;
		friends = nullptr;
		numberOfFriends = 0;
		return;
	}

	bool found = false;
	char** newFriends = new char* [numberOfFriends - 1];
	for (int i = 0; i < numberOfFriends; i++)
	{
		if (!strcmp(other, friends[i]))
		{
			found = true;
			delete[] friends[i];
		}
		else if (!found)
			newFriends[i] = friends[i];
		else
		{
			newFriends[i - 1] = friends[i];
		}
	}
	delete[] friends;
	friends = newFriends;
	numberOfFriends--;
}
void FriendList::removeFriend(const UserInfo other)
{
	removeFriend(other.getUsername());
}


void FriendList::print() const
{
	if (numberOfFriends > 0)
		cout << "Friends:\n";
	else
		cout << "No friends\n";
	for (int i = 0; i < numberOfFriends; i++)
	{
		cout << "   " << friends[i] << endl;
	}
}

void FriendList::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "FriendList::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	f.write((char*)&numberOfFriends, sizeof(int));
	for (int i = 0; i < numberOfFriends; i++)
	{
		int len = strlen(friends[i]) + 1;
		f.write((char*)&len, sizeof(int));
		f.write(friends[i], len);
	}
}
void FriendList::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "FriendList::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	if (friends != nullptr)
	{
		for (int i = 0; i < numberOfFriends; i++)
			delete[] friends[i];
		delete[] friends;
	}
	f.read((char*)&numberOfFriends, sizeof(int));
	if (numberOfFriends > 0)
	{
		friends = new char* [numberOfFriends];
		for (int i = 0; i < numberOfFriends; i++)
		{
			int len = 0;
			f.read((char*)&len, sizeof(int));
			friends[i] = new char[len];
			f.read(friends[i], len);
		}
	}
	else friends = nullptr;
}