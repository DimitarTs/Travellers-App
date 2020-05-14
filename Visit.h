#include "Destination.h"
#include "TimePeriod.h"
#include "ImageFile.h"

class Visit
{
	Destination destination;
	TimePeriod timePeriod;
	char comment[128];
	Image photos[5];
	int grade;
	int numberOfPhotos;
	void copyFrom(const Visit& other);
public:
	Visit();
	Visit(const Visit& other);
	Visit& operator=(const Visit& other);
	void setDestination(const char*, const char*);
	void setTimePeriod(int, int, int, int, int, int);
	void setComment(const char*);
	void setNumberOfPhotos(int);
	void setPhoto(int, const char*);
	void setGrade(int);
	void print();
	
	void read(ifstream& f);
	void write(ofstream& f);
};
Visit::Visit()
{
	strcpy_s(comment, "comment");
	grade = 2;
	numberOfPhotos = 0;
}
Visit::Visit(const Visit& other)
{
	copyFrom(other);
}
Visit& Visit::operator=(const Visit& other)
{
	copyFrom(other);
	return *this;
}

void Visit::setDestination(const char* city, const char* country)
{
	destination.setCity(city);
	destination.setCountry(country);
}
void Visit::setTimePeriod(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay)
{
	timePeriod.setStart(startYear, startMonth, startDay);
	timePeriod.setEnd(endYear, endMonth, endDay);
}
void Visit::setComment(const char* comment)
{
	strcpy_s(this->comment, comment);
}
void Visit::setNumberOfPhotos(int numberOfPhotos)
{
	this->numberOfPhotos = numberOfPhotos;
}
void Visit::setPhoto(int index, const char* photo)
{
	if(index < numberOfPhotos and index >= 0)
		photos[index].setImage(photo);
}
void Visit::setGrade(int grade)
{
	if (grade >= 1 and grade <= 5)
		this->grade = grade;
	else this->grade = 3;
}

void Visit::copyFrom(const Visit& other)
{
	destination = other.destination;
	timePeriod = other.timePeriod;
	strcpy_s(comment, other.comment);
	numberOfPhotos = other.numberOfPhotos;
	for (int i = 0; i < numberOfPhotos; i++)
	{
		photos[i] = other.photos[i];
	}
	grade = other.grade;
}

void Visit::print()
{
	cout << "\nVisit:\n";
	destination.print();
	timePeriod.print();
	cout << "\nGrade: " << grade << "/5" << endl;
	cout << "Comment: " << comment << endl;
	cout << "Photos(" << numberOfPhotos << "):\n";
	for (int i = 0; i < numberOfPhotos; i++)
	{
		cout << "PhotoIndex: " << i << endl;
		photos[i].print();
	}
	cout << "huh\n";
}

void Visit::read(ifstream& f)
{
	destination.read(f);
	timePeriod.read(f);
	f.read(comment, 128);
	f.read((char*)&numberOfPhotos, sizeof(int));
	for (int i = 0; i < numberOfPhotos; i++)
	{
		photos[i].read(f);
	}
	f.read((char*)&grade, sizeof(int));
}
void Visit::write(ofstream& f)
{
	destination.write(f);
	timePeriod.write(f);
	f.write(comment, 128);
	f.write((char*)&numberOfPhotos, sizeof(int));
	for (int i = 0; i < numberOfPhotos; i++)
	{
		photos[i].write(f);
	}
	f.write((char*)&grade, sizeof(int));
}