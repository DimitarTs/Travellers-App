class ListOfDestinations
{
	int numberOfDestinations;
	Destination* destinations;
public:
	ListOfDestinations();
	ListOfDestinations(const ListOfDestinations&);
	~ListOfDestinations();
	ListOfDestinations& operator=(const ListOfDestinations&);

	Destination operator[](int index);

	int getNumberOfDestinations() const;

	void addDestination(const Destination);
	void removeDestination(const Destination);

	void print() const;
	void load(UsersDatabase database);
};

ListOfDestinations::ListOfDestinations() : numberOfDestinations(0), destinations(nullptr){}
ListOfDestinations::ListOfDestinations(const ListOfDestinations& other): numberOfDestinations(other.numberOfDestinations)
{
	if (numberOfDestinations > 0)
	{
		destinations = new Destination[numberOfDestinations];
		for (int i = 0; i < numberOfDestinations; i++)
		{
			destinations[i] = other.destinations[i];
		}
	}
	else destinations = nullptr;
}
ListOfDestinations::~ListOfDestinations()
{
	if (destinations != nullptr)
		delete[] destinations;
}
ListOfDestinations& ListOfDestinations::operator=(const ListOfDestinations& other)
{
	if (this == &other)
		return *this;
	if (destinations != nullptr)
		delete[] destinations;
	numberOfDestinations = other.numberOfDestinations;
	if (numberOfDestinations > 0)
	{
		destinations = new Destination[numberOfDestinations];
		for (int i = 0; i < numberOfDestinations; i++)
		{
			destinations[i] = other.destinations[i];
		}
	}
	else destinations = nullptr;
	return *this;
}

Destination ListOfDestinations::operator[](int index)
{
	if (index < 0 or index >= numberOfDestinations)
		index = 0;

	return destinations[index];
}

int ListOfDestinations::getNumberOfDestinations() const
{ 
	return numberOfDestinations; 
}

void ListOfDestinations::addDestination(const Destination dest)
{
	for (int i = 0; i < numberOfDestinations; i++)
		if (destinations[i] == dest)
			return;
	Destination* newDestinations = new Destination[numberOfDestinations + 1];
	for (int i = 0; i < numberOfDestinations; i++)
		newDestinations[i] = destinations[i];
	newDestinations[numberOfDestinations] = dest;
	if (destinations != nullptr)
		delete[] destinations;
	destinations = newDestinations;
	numberOfDestinations++;
}

void ListOfDestinations::removeDestination(const Destination dest)
{
	int index = -1;
	for (int i = 0; i < numberOfDestinations and index == -1; i++)
		if (destinations[i] == dest)
			index = i;
	if (index < 0)
		return;
	if (numberOfDestinations == 1)
	{
		delete[] destinations;
		destinations = nullptr;
		numberOfDestinations = 0;
		return;
	}

	Destination* newDestinations = new Destination[numberOfDestinations - 1];
	for (int i = 0; i < numberOfDestinations; i++)
	{
		if (i < index)
			newDestinations[i] = destinations[i];
		else if (i > index)
			newDestinations[i - 1] = destinations[i];
	}
	numberOfDestinations--;
	delete[] destinations;
	destinations = newDestinations;
}

void ListOfDestinations::print() const
{
	for (int i = 0; i < numberOfDestinations; i++)
	{
		destinations[i].print();
		cout << endl;
	}
}