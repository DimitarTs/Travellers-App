class UsersDatabase;

class Destination
{
	char* city;
	char* country;
	void copyFrom(const Destination& other);
public:
	Destination();
	Destination(const Destination& other);
	Destination(const char*, const char*);
	Destination& operator=(const Destination& other);
	~Destination();

	bool operator==(const Destination& other) const;

	void printRatings(const UsersDatabase) const;

	void setCity(const char*);
	void setCountry(const char*);
	void setDestination(const char*, const char*);

	const char* getCity() const;
	const char* getCountry() const;

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
Destination::Destination()
{
	country = new char[8];
	strcpy(country, "unknown");

	city = new char[8];
	strcpy(city, "unknown");
}
Destination::Destination(const Destination& other)
{
	int cityLen = strlen(other.city);
	this->city = new char[cityLen + 1];
	strcpy(this->city, other.city);

	int countryLen = strlen(other.country);
	this->country = new char[countryLen + 1];
	strcpy(this->country, other.country);
}
Destination::Destination(const char* city, const char* country)
{
	int cityLen = strlen(city);
	this->city = new char[cityLen + 1];
	strcpy(this->city, city);

	int countryLen = strlen(country);
	this->country = new char[countryLen + 1];
	strcpy(this->country, country);
}
Destination::~Destination()
{
	delete[] city;
	delete[] country;
}
Destination& Destination::operator=(const Destination& other)
{
	if (this == &other)
		return *this;
	setCity(other.city);
	setCountry(other.country);
	return *this;
}
bool Destination::operator==(const Destination& other) const
{
	if (strcmp(city, other.city))
		return false;
	if (strcmp(country, other.country))
		return false;
	return true;
}

void Destination::copyFrom(const Destination& other)
{
	if (this == &other)
		return;
	setCity(other.city);
	setCountry(other.country);
}

void Destination::setCity(const char* city)
{
	delete[] this->city;
	int cityLen = strlen(city);
	this->city = new char[cityLen + 1];
	strcpy(this->city, city);
}
void Destination::setCountry(const char* country)
{
	delete[] this->country;
	int countryLen = strlen(country);
	this->country = new char[countryLen + 1];
	strcpy(this->country, country);
}
void Destination::setDestination(const char* city, const char* country)
{
	setCity(city);
	setCountry(country);
}

const char* Destination::getCity() const
{
	return this->city;
}
const char* Destination::getCountry() const
{
	return this->country;
}

void Destination::print() const
{
	cout << city << ", " << country;
}

void Destination::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "Destination::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	int len = 0;
	len = strlen(city) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(city, len);

	len = strlen(country) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(country, len);
}
void Destination::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "Destination::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	delete[] city;
	delete[] country;
	
	int len = 0;

	f.read((char*)&len, sizeof(int));
	city = new char[len];
	f.read(city, len);

	f.read((char*)&len, sizeof(int));
	country = new char[len];
	f.read(country, len);
}