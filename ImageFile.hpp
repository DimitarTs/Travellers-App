class Image
{
	char type[5];
	char* name;
	void copyFrom(const Image& other);
public:
	Image();
	Image(const Image& other);
	Image(const char*);
	~Image();
	Image& operator=(const Image& other);
	bool setName(const char*);
	bool setType(const char*);
	bool setImage(const char*);

	bool operator==(const Image& other) const;

	void print() const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};
void Image::copyFrom(const Image& other)
{
	if (&other != this)
	{
		setName(other.name);
		setType(other.type);
	}
}
bool Image::setName(const char* name)
{
	for (int i = 0; name[i] != '\0'; i++)
		if ((name[i] < 'a' or name[i]>'z')
			and (name[i] < 'A' or name[i]>'Z')
			and name[i] != '_')
			return false;
	if (strlen(name) < 1)
		return false;

	int nameLen = strlen(name);
	delete[] this->name;
	this->name = new char[nameLen + 1];
	for (int i = 0; i <= nameLen; i++)
	{
		this->name[i] = name[i];
	}
}
bool Image::setType(const char* type)
{
	if (strcmp(type, "png") and strcmp(type, "jpeg"))
	{
		strcpy_s(this->type, "jpeg");
		return false;
	}
	strcpy_s(this->type, type);
	return true;
}
bool Image::setImage(const char* image)
{
	char photoName[64];
	int i;
	for (i = 0; image[i] != '.' and i < 64 and image[i]!='\0'; i++)
	{
		photoName[i] = image[i];
	}
	photoName[i] = '\0';
	if (!setName(photoName))
		return false;
	if (image[i] != '.')
	{
		setType("jpeg");
		return true;
	}
	i++;
	char photoType[5];
	int j;
	for (j = 0; j < 4 and image[i] != '\0'; j++)
	{
		photoType[j] = image[i];
		i++;
	}
	photoType[j] = '\0';
	if (!setType(photoType))
		return false;
}

Image::Image()
{
	name = nullptr;
	setName("unknown");
	setType("jpeg");
}
Image::Image(const Image& other)
{
	copyFrom(other);
}
Image::Image(const char* image): name(nullptr)
{
	setImage(image);
}
Image::~Image()
{
	delete[] name;
}
Image& Image::operator=(const Image& other)
{
	copyFrom(other);
	return *this;
}

bool Image::operator==(const Image& other) const
{
	if (strcmp(type, other.type))
		return false;
	if (name == nullptr or other.name == nullptr)
	{
		if (name != nullptr or other.name != nullptr)
			return false;
		return true;
	}
	if (strcmp(name, other.name))
		return false;
	return true;
}

void Image::print() const
{
	cout << name << "." << type;
}

void Image::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "Image::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	int len = strlen(name) + 1;
	f.write((char*)&len, sizeof(int));
	f.write(name, len);
	f.write(type, 5);
}
void Image::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "Image::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	
	if (name != nullptr)
	{	
		delete[] name;
	}
	int len = 0;
	f.read((char*)&len, sizeof(int));
	name = new char[len];
	f.read(name, len);
	f.read(type, 5);
}