#include "Visit.hpp"
#include "UserInfo.hpp"

class ListOfVisits
{
	int numberOfVisits;
	Visit* visits;
public:
	ListOfVisits();
	ListOfVisits(const ListOfVisits&);
	~ListOfVisits();
	ListOfVisits& operator=(const ListOfVisits&);

	void addVisit(const Visit);
	void removeVisit(int);

	int getNumberOfVisits() { return numberOfVisits; }
	Visit operator[](int index)
	{
		if (index >= 0 and index < numberOfVisits)
			return visits[index];
		return Visit();
	}

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
ListOfVisits::ListOfVisits() : numberOfVisits(0), visits(nullptr) {}
ListOfVisits::ListOfVisits(const ListOfVisits& other) : numberOfVisits(other.numberOfVisits), visits(nullptr)
{
	if (numberOfVisits > 0)
	{
		visits = new Visit[numberOfVisits];
		for (int i = 0; i < numberOfVisits; i++)
		{
			visits[i] = other.visits[i];
		}
	}
}
ListOfVisits::~ListOfVisits()
{
	if (visits != nullptr)
		delete[] visits;
}
ListOfVisits& ListOfVisits::operator=(const ListOfVisits& other)
{
	if (this == &other)
		return *this;
	numberOfVisits = other.numberOfVisits;
	if (visits != nullptr)
		delete[] visits;
	if (numberOfVisits > 0)
	{
		visits = new Visit[numberOfVisits];
		for (int i = 0; i < numberOfVisits; i++)
			visits[i] = other.visits[i];
	}
	else visits = nullptr;
	return *this;
}

void ListOfVisits::addVisit(const Visit visit)
{
	Visit* newVisits = new Visit[numberOfVisits + 1];
	for (int i = 0; i < numberOfVisits; i++)
	{
		newVisits[i] = visits[i];
	}
	newVisits[numberOfVisits] = visit;
	numberOfVisits++;
	if (visits != nullptr)
		delete[] visits;
	visits = newVisits;
}
void ListOfVisits::removeVisit(int index)
{
	if (index < 0 or index >= numberOfVisits)
		return;
	if (numberOfVisits == 1)
	{
		delete[] visits;
		visits = nullptr;
		numberOfVisits = 0;
		return;
	}

	Visit* newVisits = new Visit[numberOfVisits - 1];
	for (int i = 0; i < numberOfVisits; i++)
	{
		if (i < index)
			newVisits[i] = visits[i];
		else if (i > index) 
			newVisits[i - 1] = visits[i];
	}
	numberOfVisits--;
	delete[] visits;
	visits = newVisits;
}

void ListOfVisits::print() const
{
	for (int i = 0; i < numberOfVisits; i++)
	{
		cout << "Visit #" << i + 1 << " :\n";
		visits[i].print();
		cout << endl;
	}
}

void ListOfVisits::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "ListOfVisits::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	f.write((char*)&numberOfVisits, sizeof(int));
	for (int i = 0; i < numberOfVisits; i++)
		visits[i].writeToFile(f);
}
void ListOfVisits::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "ListOfVisits::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	if (visits != nullptr)
		delete[] visits;
	f.read((char*)&numberOfVisits, sizeof(int));
	if (numberOfVisits > 0)
	{
		visits = new Visit[numberOfVisits];
		for (int i = 0; i < numberOfVisits; i++)
			visits[i].readFromFile(f);
	}
	else
		visits = nullptr;
}