bool isLeapYear(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 != 0)
		return false;
	return true;
}

int numberOfDaysInMonth(int month, int year)
{
	switch (month)
	{
	case 2:
		if (isLeapYear(year))
			return 29;
		return 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}

class Date
{
	int year;
	int month;
	int day;
	void copyFrom(const Date& other);
public:
	Date();
	Date(const Date& other);
	Date(int, int, int);
	Date& operator=(const Date& other);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

	void print();
	void read(ifstream& f);
	void write(ofstream& f);
};

Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

Date::Date(int year, int month, int day)
{
	if (year <= 0)
		year = 2000;
	this->year = year;
	if (month <= 0 or month > 12)
		month = 1;
	this->month = month;
	if (day <= 0 or day > numberOfDaysInMonth(month, year))
		day = 1;
	this->day = day;
}

Date::Date(const Date& other)
{
	copyFrom(other);
}

Date& Date::operator=(const Date& other)
{
	copyFrom(other);
	return *this;
}

void Date::copyFrom(const Date& other)
{
	year = other.year;
	month = other.month;
	day = other.day;
}

void Date::setDay(int day)
{
	if (day <= 0 or day > numberOfDaysInMonth(month, year))
		day = 1;
	this->day = day;
}

void Date::setMonth(int month)
{
	if (month <= 0 or month > 12)
		month = 1;
	this->month = month;
}

void Date::setYear(int year)
{
	if (year <= 0)
		year = 2000;
	this->year = year;
}

void Date::print()
{
	cout << setfill('0');
	cout << setw(4) << year;
	cout << "-";
	cout << setw(2) << month;
	cout << "-";
	cout << setw(2) << day;
}

void Date::read(ifstream& f)
{
	f.read((char*)&year, sizeof(int));
	f.read((char*)&month, sizeof(int));
	f.read((char*)&day, sizeof(int));
}

void Date::write(ofstream& f)
{
	f.write((char*)&year, sizeof(int));
	f.write((char*)&month, sizeof(int));
	f.write((char*)&day, sizeof(int));
}