class Destination
{
	char city[64];
	char country[64];
	void copyFrom(const Destination& other);
public:
	Destination();
	Destination(const Destination& other);
	Destination& operator=(const Destination& other);
	void setCity(const char*);
	void setCountry(const char*);
	void print();

	void read(ifstream& f);
	void write(ofstream& f);
};
void Destination::copyFrom(const Destination& other)
{
	strcpy_s(city, other.city);
	strcpy_s(country, other.country);
}

void Destination::setCity(const char* city)
{
	if (city[0] < 'A' or city[0]>'Z')
	{
		strcpy_s(this->city, "Unknown");
		return;
	}
	int cityLen = strlen(city);
	for (int i = 0; i < cityLen; i++)
	{
		if ((city[i] < 'a' or city[i]>'z') and (city[i] < 'A' or city[i]>'Z'))
		{
			strcpy_s(this->city, "Unknown");
			return;
		}
	}
	strcpy_s(this->city, city);
}
void Destination::setCountry(const char* country)
{
	if (country[0] < 'A' or country[0]>'Z')
	{
		strcpy_s(this->country, "Unknown");
		return;
	}
	int countryLen = strlen(country);
	for (int i = 0; i < countryLen; i++)
	{
		if ((country[i] < 'a' or country[i]>'z') and (country[i] < 'A' or country[i]>'Z'))
		{
			strcpy_s(this->country, "Unknown");
			return;
		}
	}
	strcpy_s(this->country, country);
}

Destination::Destination()
{
	setCity("...");
	setCountry("...");
}
Destination::Destination(const Destination& other)
{
	copyFrom(other);
}
Destination& Destination::operator=(const Destination& other)
{
	copyFrom(other);
	return *this;
}

void Destination::print()
{
	cout << city << ", " << country << endl;
}

void Destination::read(ifstream& f)
{
	f.read(city, 64);
	f.read(country, 64);
}

void Destination::write(ofstream& f)
{
	f.write(city, 64);
	f.write(country, 64);
}