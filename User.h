class User
{
	char* username;
	char* password;
	char* email;
public:
	User();
	User(char*, char*, char*);
	User(User const&);
	~User();
	void setUsername(char*);
	void setPassword(char*);
	void setEmail(char*);
	char* getUsername();
	char* getPassword();
	char* getEmail();

	void input();
	void print();

	void read(ifstream& f);
	void write(ofstream& f);
};

User::User()
{
	username = nullptr;
	password = nullptr;
	email = nullptr;
}

User::User(char* username, char* password, char* email)
{
	int usernameLength = strlen(username);
	this->username = new char[usernameLength + 1];
	for (int i = 0; i < usernameLength; i++)
		this->username[i] = username[i];
	this->username[usernameLength] = '\0';

	int passwordLength = strlen(password);
	this->password = new char[passwordLength + 1];
	for (int i = 0; i < passwordLength; i++)
		this->password[i] = password[i];
	this->password[passwordLength] = '\0';

	int emailLength = strlen(email);
	this->email = new char[emailLength + 1];
	for (int i = 0; i < emailLength; i++)
		this->email[i] = email[i];
	this->email[emailLength] = '\0';
}

User::User(User const& other)
{
	setUsername(other.username);
	setPassword(other.password);
	setEmail(other.email);
}

void User::setUsername(char* username)
{
	delete[] this->username;
	int usernameLength = strlen(username);
	this->username = new char[usernameLength + 1];
	for (int i = 0; i < usernameLength; i++)
		this->username[i] = username[i];
	this->username[usernameLength] = '\0';
}

void User::setPassword(char* password)
{
	delete[] this->password;
	int passwordLength = strlen(password);
	this->password = new char[passwordLength + 1];
	for (int i = 0; i < passwordLength; i++)
		this->password[i] = password[i];
	this->password[passwordLength] = '\0';
}

void User::setEmail(char* email)
{
	delete[] this->email;
	int emailLength = strlen(email);
	this->email = new char[emailLength + 1];
	for (int i = 0; i < emailLength; i++)
		this->email[i] = email[i];
	this->email[emailLength] = '\0';
}

char* User::getUsername()
{
	int usernameLength = strlen(username);
	char* result = new char[usernameLength + 1];
	for (int i = 0; i < usernameLength; i++)
		result[i] = username[i];
	result[usernameLength] = '\0';
	return result;
}

char* User::getPassword()
{
	int passwordLength = strlen(password);
	char* result = new char[passwordLength + 1];
	for (int i = 0; i < passwordLength; i++)
		result[i] = password[i];
	result[passwordLength] = '\0';
	return result;
}

char* User::getEmail()
{
	int emailLength = strlen(email);
	char* result = new char[emailLength + 1];
	for (int i = 0; i < emailLength; i++)
		result[i] = email[i];
	result[emailLength] = '\0';
	return result;
}

void User::input()
{
	char username[30];
	cin.getline(username, 30);
	char password[30];
	cin.getline(password, 30);
	char email[30];
	cin.getline(email, 30);
	setUsername(username);
	setPassword(password);
	setEmail(email);
}

void User::print()
{
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
	cout << "Email: " << email << endl;
}

void User::read(ifstream& f)
{
	int usernameLen = 1;
	int passwordLen = 1;
	int emailLen = 1;

	f.read((char*)&usernameLen, sizeof(int));
	delete[] username;
	username = new char[usernameLen];
	f.read(username, usernameLen);

	f.read((char*)&passwordLen, sizeof(int));
	delete[] password;
	password = new char[passwordLen];
	f.read(password, passwordLen);

	f.read((char*)&emailLen, sizeof(int));
	delete[] email;
	email = new char[emailLen];
	f.read(email, emailLen);
}

void User::write(ofstream& f)
{
	int usernameLen = strlen(username) + 1;
	int passwordLen = strlen(password) + 1;
	int emailLen = strlen(email) + 1;
	f.write((char*)&usernameLen, sizeof(int));
	f.write(username, usernameLen);
	f.write((char*)&passwordLen, sizeof(int));
	f.write(password, passwordLen);
	f.write((char*)&emailLen, sizeof(int));
	f.write(email, emailLen);
}

User::~User()
{
	delete[] username;
	delete[] password;
	delete[] email;
}