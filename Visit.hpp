#include "Destination.hpp"

class Visit: public Destination, public TimePeriod
{
	double grade;
	char* comment;
	int numberOfImages;
	Image* images;
	void copyFrom(const Visit& other);
public:
	Visit();
	Visit(const Visit& other);
	~Visit();
	Visit& operator=(const Visit& other);

	void setGrade(double);
	void setComment(const char*);
	void removeComment();
	void addImage(const Image);
	bool addImage(const char*);
	void removeImage(const Image);
	void removeImage(const char*);
	
	void input()
	{
		if (comment != nullptr)
			delete[] comment;
		if (images != nullptr)
			delete[] images;
		numberOfImages = 0;

		char inputLine[1024];
		int index = 0;
		cout << "Destination: (City, Country) ";
		cin.getline(inputLine, 1024);
		char city[64];
		char country[64];
		extractWord(inputLine, city, index, 64, false, ',');
		setCity(city);
		index++;
		extractWord(inputLine, country, index, 64);
		setCountry(country);

		cout << "Time Period: (yyyy-mm-dd) (yyyy-mm-dd)\n";
		bool validTimePeriod = false;
		int sYear, sMonth, sDay, eYear, eMonth, eDay;
		while (!validTimePeriod)
		{
			bool validDate = true;
			do
			{
				validDate = true;

				cin >> sYear;
				cin.get();
				cin >> sMonth;
				if (sMonth > 12 or sMonth < 1)
					validDate = false;
				cin.get();
				cin >> sDay;
				if (validDate and (sDay > numberOfDaysInMonth(sMonth, sYear) or sDay < 1))
					validDate = false;

				if(!validDate)
					cout << "Invalid date!\n";
			} while (!validDate);

			do
			{
				validDate = true;

				cin >> eYear;
				cin.get();
				cin >> eMonth;
				if (eMonth > 12 or eMonth < 1)
					validDate = false;
				cin.get();
				cin >> eDay;
				if (validDate and (eDay > numberOfDaysInMonth(eMonth, eYear) or eDay < 1))
					validDate = false;

				if (!validDate)
					cout << "Invalid date!\n";
			} while (!validDate);

			if (sYear > eYear)
				validTimePeriod = false;
			else if (sYear == eYear and sMonth > eMonth)
				validTimePeriod = false;
			else if (sYear == eYear and sMonth == eMonth and sDay > eDay)
				validTimePeriod = false;
			else validTimePeriod = true;

			if (!validTimePeriod)
				cout << "Invalid time period! End date should be after start date\n";
		}
		
		setTimePeriod(sYear, sMonth, sDay, eYear, eMonth, eDay);

		cout << "Grade: (1-5) ";
		cin >> grade;
		while (grade < 1 or grade > 5)
		{
			cout << "Invalid grade\n";
			cout << "Grade: (1-5) ";
			cin >> grade;
		}

		cout << "Comment: (Can be left blank) ";
		cin.get();
		cin.getline(inputLine, 1024);
		index = 0;
		char check[64];
		extractWord(inputLine, check, index, 64);
		if (strcmp(check, ""))
		{
			setComment(inputLine);
		}

		cout << "Number of photos: ";
		int count;
		cin >> count;
		cin.get();
		for (int i = 0; i < count; i++)
		{
			char image[64];
			cin.getline(image, 64);
			if (!addImage(image))
			{
				cout << "Invalid file name.\n";
				i--;
			}
		}
	}

	double getGrade() const
	{
		return grade;
	}
	const char* getComment() const { return comment; }

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};

Visit::Visit(): Destination(), TimePeriod(), grade(0), comment(nullptr), numberOfImages(0), images(nullptr) {}
Visit::Visit(const Visit& other): Destination(other), TimePeriod(other), grade(other.grade), numberOfImages(other.numberOfImages)
{
	if (other.comment != nullptr)
	{
		int commentLen = strlen(other.comment);
		comment = new char[commentLen + 1];
		strcpy(comment, other.comment);
	}
	else comment = nullptr;
	if (numberOfImages > 0)
	{
		images = new Image[numberOfImages];
		for (int i = 0; i < numberOfImages; i++)
			images[i] = other.images[i];
	}
	else images = nullptr;
}
Visit::~Visit()
{
	if(comment != nullptr)
		delete[] comment;
	if(images != nullptr)
		delete[] images;
}
Visit& Visit::operator=(const Visit& other)
{
	copyFrom(other);
	return *this;
}

void Visit::copyFrom(const Visit& other)
{
	if (this == &other)
		return;
	Destination::operator=(other);
	TimePeriod::operator=(other);
	grade = other.grade;
	setComment(other.comment);
	numberOfImages = other.numberOfImages;
	if(images != nullptr)
		delete[] images;
	if (numberOfImages > 0)
	{
		images = new Image[numberOfImages];
		for (int i = 0; i < numberOfImages; i++)
			images[i] = other.images[i];
	}
}

void Visit::setGrade(double grade)
{
	this->grade = grade;
}
void Visit::setComment(const char* comment)
{
	if(this->comment != nullptr)
		delete[] this->comment;
	if (comment != nullptr)
	{
		int commentLen = strlen(comment);
		this->comment = new char[commentLen + 1];
		strcpy(this->comment, comment);
	}
	else this->comment = nullptr;
}
void Visit::removeComment()
{
	if (comment != nullptr)
	{
		delete[] comment;
		comment = nullptr;
	}
}
void Visit::addImage(const Image image)
{
	Image* newImages = new Image[numberOfImages + 1];
	for (int i = 0; i < numberOfImages; i++)
		newImages[i] = images[i];
	newImages[numberOfImages] = image;
	if (images != nullptr)
		delete[] images;
	images = newImages;
	numberOfImages++;
}
bool Visit::addImage(const char* image)
{
	Image addition;
	if (!addition.setImage(image))
		return false;
	Image* newImages = new Image[numberOfImages + 1];
	for (int i = 0; i < numberOfImages; i++)
		newImages[i] = images[i];
	newImages[numberOfImages] = addition;
	if (images != nullptr)
		delete[] images;
	images = newImages;
	numberOfImages++;
	return true;
}
void Visit::removeImage(const Image image)
{
	if (numberOfImages == 0)
		return;
	if (numberOfImages == 1)
	{
		if (images[0] == image)
		{
			delete[] images;
			numberOfImages = 0;
		}
		return;
	}
	Image* newImages = new Image[numberOfImages - 1];
	bool found = false;
	for (int i = 0; i < numberOfImages; i++)
	{
		if (images[i] == image)
			found = true;
		else if (!found)
		{
			newImages[i] = images[i];
		}
		else
		{
			newImages[i - 1] = images[i];
		}
	}
	if (found)
	{
		numberOfImages--;
		delete[] images;
		images = newImages;
	}
	else
	{
		delete[] newImages;
	}
}
void Visit::removeImage(const char* image)
{
	removeImage(Image(image));
}

void Visit::print() const
{
	Destination::print();
	cout << endl;
	TimePeriod::print(1);
	cout << endl;
	cout << "Grade: " << grade << endl;
	if(comment != nullptr)
		cout << "Comment:\n" << comment << endl;
	if (numberOfImages > 0)
	{
		cout << "Photos:\n";
		for (int i = 0; i < numberOfImages; i++)
		{
			images[i].print();
			cout << endl;
		}
	}
}

void Visit::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "Visit::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	Destination::writeToFile(f);
	TimePeriod::writeToFile(f);
	f.write((char*)&grade, sizeof(double));
	int len = 0;
	if (comment != nullptr)
	{
		len = strlen(comment) + 1;
		f.write((char*)&len, sizeof(int));
		f.write(comment, len);
	}
	else
		f.write((char*)&len, sizeof(int));
	f.write((char*)&numberOfImages, sizeof(int));
	for (int i = 0; i < numberOfImages; i++)
		images[i].writeToFile(f);
}
void Visit::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "Visit::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	if (comment != nullptr)
		delete[] comment;
	if (images != nullptr)
		delete[] images;
	Destination::readFromFile(f);
	TimePeriod::readFromFile(f);
	f.read((char*)&grade, sizeof(double));

	int len = 0;
	f.read((char*)&len, sizeof(int));
	if (len > 0)
	{
		comment = new char[len];
		f.read(comment, len);
	}
	else comment = nullptr;
	f.read((char*)&numberOfImages, sizeof(int));
	images = new Image[numberOfImages];
	for (int i = 0; i < numberOfImages; i++)
		images[i].readFromFile(f);
}