class Image
{
	char type[5];
	char* name;
	void copyFrom(const Image& other);
public:
	Image();
	Image(const Image& other);
	~Image();
	Image& operator=(const Image& other);
	void setName(const char*);
	void setType(const char*);
	void setImage(const char*);

	void print();

	void read(ifstream& f);
	void write(ofstream& f);
};
void Image::copyFrom(const Image& other)
{
	if (&other != this)
	{
		setName(other.name);
		setType(other.type);
	}
}
void Image::setName(const char* name)
{
	int nameLen = strlen(name);
	delete[] this->name;
	this->name = new char[nameLen + 1];
	for (int i = 0; i <= nameLen; i++)
	{
		this->name[i] = name[i];
	}
}
void Image::setType(const char* type)
{
	if (strcmp(type, "png") and strcmp(type, "jpeg"))
	{
		strcpy_s(this->type, "jpeg");
		return;
	}
	strcpy_s(this->type, type);
}
void Image::setImage(const char* photo)
{
	char photoName[64];
	int i;
	for (i = 0; photo[i] != '.' and i < 64; i++)
	{
		photoName[i] = photo[i];
	}
	photoName[i] = '\0';
	setName(photoName);
	i++;
	char photoType[5];
	int j;
	for (j = 0; j < 4 and photo[i] != '\0'; j++)
	{
		photoType[j] = photo[i];
		i++;
	}
	photoType[j] = '\0';
	cout << "photo type: " << photoType << endl;
	setType(photoType);
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
Image::~Image()
{
	delete[] name;
}
Image& Image::operator=(const Image& other)
{
	copyFrom(other);
	return *this;
}

void Image::print()
{
	cout << name << "." << type << endl;
}

void Image::read(ifstream& f)
{
	int nameLen = 1;
	f.read(type, 5);
	f.read((char*)&nameLen, sizeof(int));
	f.read(name, nameLen);
}
void Image::write(ofstream& f)
{
	int nameLen = strlen(name) + 1;
	f.write(type, 5);
	f.write((char*)&nameLen, sizeof(int));
	f.write(name, nameLen);
}