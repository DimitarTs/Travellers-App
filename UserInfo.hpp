class UserInfo
{
	char* username;
	char* password;
	char* email;
	bool validateUsername(const char* username)
	{

	}
	bool validatePassword(const char* password)
	{

	}
	bool validateEmail(const char* email)
	{

	}
public:
	UserInfo();
	UserInfo(const UserInfo& other);
	UserInfo(const char*, const char*, const char*);
	~UserInfo();
	UserInfo& operator=(const UserInfo&);
	bool operator==(const UserInfo& other);

	bool setUsername(const char*);
	bool setPassword(const char*);
	bool setEmail(const char*);

	const char* getUsername() const;
	const char* getPassword() const;
	const char* getEmail() const;

	void print(bool oneRow = false) const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
UserInfo::UserInfo()
{
	username = new char[8];
	strcpy(username, "unknown");

	password = new char[8];
	strcpy(password, "unknown");

	email = new char[8];
	strcpy(email, "unknown");
}
UserInfo::UserInfo(const UserInfo& other)
{
	username = new char[strlen(other.username) + 1];
	strcpy(username, other.username);

	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);

	email = new char[strlen(other.email) + 1];
	strcpy(email, other.email);
}
UserInfo::UserInfo(const char* username, const char* password, const char* email)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);

	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);

	this->email = new char[strlen(email) + 1];
	strcpy(this->email, email);
}
UserInfo::~UserInfo()
{
	delete[] username;
	delete[] password;
	delete[] email;
}
UserInfo& UserInfo::operator=(const UserInfo& other)
{
	if (this == &other)
		return *this;

	delete[] username;
	username = new char[strlen(other.username) + 1];
	strcpy(username, other.username);

	delete[] password;
	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);

	delete[] email;
	email = new char[strlen(other.email) + 1];
	strcpy(email, other.email);
	
	return *this;
}

bool UserInfo::operator==(const UserInfo& other)
{
	if (strcmp(username, other.username))
		return false;
	if (strcmp(password, other.password))
		return false;
	if (strcmp(email, other.email))
		return false;
	return true;
}

bool UserInfo::setUsername(const char* username)
{
	for (int i = 0; username[i] != '\0'; i++)
		if (    (username[i] < 'a' or username[i]>'z')
			and (username[i] < 'A' or username[i]>'Z')
			and (username[i] < '0' or username[i]>'9'))
			return false;
	if (strlen(username) < 1)
		return false;
	delete[] this->username;
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
	return true;
}
bool UserInfo::setPassword(const char* password)
{
	if (strlen(password) < 1)
		return false;
	delete[] this->password;
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
	return true;
}
bool UserInfo::setEmail(const char* email)
{
	for (int i = 0; email[i] != '\0'; i++)
		if (    (email[i] < 'a' or email[i]>'z')
			and (email[i] < 'A' or email[i]>'Z')
			and (email[i] < '0' or email[i]>'0')
			and  email[i] != '@'
			and  email[i] != '.')
			return false;
	if (strlen(email) < 1)
		return false;
	delete[] this->email;
	this->email = new char[strlen(email) + 1];
	strcpy(this->email, email);
	return true;
}

const char* UserInfo::getUsername() const
{
	return username;
}
const char* UserInfo::getPassword() const
{
	return password;
}
const char* UserInfo::getEmail() const
{
	return email;
}

void UserInfo::print(bool oneRow) const
{
	cout << username;
	if (oneRow)
		cout << " ";
	else cout << endl;
	cout << password;
	if (oneRow)
		cout << " ";
	else cout << endl;
	cout << email;
	if (!oneRow)
		cout << endl;
}

void UserInfo::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "UserInfo::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	int len = 0;
	len = strlen(username) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(username, len);

	len = strlen(password) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(password, len);

	len = strlen(email) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(email, len);
}
void UserInfo::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "UserInfo::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	delete[] username;
	delete[] password;
	delete[] email;
	
	int len = 0;
	
	f.read((char*)&len, sizeof(int));
	username = new char[len];
	f.read(username, len);

	f.read((char*)&len, sizeof(int));
	password = new char[len];
	f.read(password, len);

	f.read((char*)&len, sizeof(int));
	email = new char[len];
	f.read(email, len);
}