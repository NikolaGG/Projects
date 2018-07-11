#include "TagCollection.h"

TagCollection::TagCollection() :fileName(nullptr), collection(nullptr), size(DEFAULT_HTML_SIZE), capacity(DEFAULT_HTML_SIZE*2)
{
	fileName = new char[strlen(GENERIC_HTML_FILE_NAME)+1];
	strcpy_s(fileName, strlen(GENERIC_HTML_FILE_NAME) + 1,GENERIC_HTML_FILE_NAME);

	collection = new Tag*[capacity];

	collection[0] = new SimpleTag("<!DOCTYPE html>", 0);
	collection[1] = new SimpleTag("<html>", 1);
	collection[2] = new SimpleTag("<head> </head>", 2);
	collection[3] = new SimpleTag("<body>", 3);
	
}

TagCollection::TagCollection(const char * fileNameStr) :fileName(nullptr), collection(nullptr), size(0), capacity(0)
{
	fileName = new char[strlen(fileNameStr)+1];
	strcpy_s(fileName, strlen(fileNameStr) + 1,fileNameStr);
	if (isValidFile())
	{
		loadInfoFromFile();
	}
	else
	{
		size = DEFAULT_HTML_SIZE;
		capacity = 2 * DEFAULT_HTML_SIZE;
		collection = new Tag*[capacity];

		collection[0] = new SimpleTag("<!DOCTYPE html>", 0);
		collection[1] = new SimpleTag("<html>", 1);
		collection[2] = new SimpleTag("<head> </head>", 2);
		collection[3] = new SimpleTag("<body>", 3);

	}
}

TagCollection::TagCollection(const TagCollection & other)
{
	copyFrom(other);
}

TagCollection & TagCollection::operator=(const TagCollection & other)
{
	if (this != &other)
	{
		clean();
		copyFrom(other);
	}
	return *this;
}

TagCollection::~TagCollection()
{
	clean();
}

void TagCollection::moveTo(unsigned pos, const char * descr)
{
	pos += DEFAULT_HTML_SIZE;
	if (isValidPos(pos))
	{
		Tag*temp = getTag(descr);
		if (temp != nullptr)
		{
		remove(descr);
		shiftRight(pos);
		collection[pos] = temp;
		}
		else
		{
			std::cout << "No such tag description.\n";
		}
	}
	else
	{
		std::cout << "Invalid position!\n";
	}
}

void TagCollection::remove(const char * descr)
{
	Tag**newCollection = new Tag*[capacity];
	size_t j = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(descr,collection[i]->getDescription())!=0)
		{
			newCollection[j] = collection[i];
			j++;
		}
	}
	delete[]collection;
	size--;
	collection = newCollection;
}

void TagCollection::addTag(Tag * newTag)
{
	if (newTag == nullptr)
		throw std::invalid_argument("null pointer passed");
	if (size >= capacity)
		resize();

	newTag->setPos(size);
	collection[size] = newTag;
	size++;

}

void TagCollection::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		char*temp = collection[i]->getHTML();
		std::cout << temp << std::endl;
		delete[] temp;
	}
	std::cout << "</body>" << std::endl;
	std::cout << "</html>" << std::endl;
	return;
}

void TagCollection::save() const
{
	std::ofstream ofs;
	ofs.open(fileName, std::ios::trunc);
	if (!ofs.is_open())
	{
		std::cerr << "Could not openfile to write to.\n";
	}
	for (size_t i = 0; i < size; ++i)
	{
		char*temp = collection[i]->getHTML();
		ofs << temp << std::endl;
		delete[] temp;
	}
	ofs << "</body>" << std::endl;
	ofs << "</html>" << std::endl;
	ofs.close();
}

bool TagCollection::isValidFile() const
{
	std::ifstream ifs;
	ifs.open(fileName);
	if (!ifs.is_open())
	{
		return false;
	}
	ifs.close();
	return true;
}

bool TagCollection::isValidPos(unsigned pos) const
{
	if (pos>=3 && pos <=size)
	{
		return true;
	}
	return false;
}

Tag * TagCollection::getTag(const char * descr) const
{
	Tag*temp = nullptr;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(descr,collection[i]->getDescription())==0)
		{
			temp = collection[i];
			return temp;
		}
	}
	return temp;
}

unsigned TagCollection::getFileSize() const
{
	char buff[MAX_TAG_LENGTH];
	std::ifstream ifs;
	ifs.open(fileName);
	if (!ifs.is_open())
	{
		std::cerr << "Could not open file in getFileSize function.\n";
	}
	unsigned cnt = 0;
	while (!ifs.eof())
	{
		ifs.getline(buff, MAX_TAG_LENGTH);
		cnt++;
	}
	ifs.close();
	//-2 for last two tags
	return cnt - 3;
}


void TagCollection::shiftRight(unsigned pos)
{
	if (isValidPos(pos))
	{
		unsigned write = size;
		unsigned read = size - 1;
		while (read >= pos)
		{
			collection[write--] = collection[read--];
		}
	}
	else
	{
		std::cout << "invalid position!\n";
	}
	size++;
}

void TagCollection::loadInfoFromFile()
{
	size = getFileSize();
	capacity = size*2;

	collection = new Tag*[capacity];

	std::ifstream ifs;
	ifs.open(fileName);
	if (!ifs.is_open())
	{
		std::cerr << "Could not open file to load info from.\n";
	}
	for (size_t i = 0; i < size; ++i)
	{
		char*temp = new char[MAX_TAG_LENGTH];
		ifs.getline(temp,MAX_TAG_LENGTH);
		if (temp[1]=='h'&&(temp[2]>='0'&&temp[2]<='9'))
		{
			collection[i] = new TitleTag(temp,i);
		}
		else if (temp[1] == 'p')
		{
			collection[i] = new TextTag(temp, i);
		}
		else if (temp[1] == 'a')
		{
			collection[i] = new HyperlinkTag(temp, i);
		}
		else if (temp[1] == 'i')
		{
			if (temp[2]=='m')
			{
				collection[i] = new ImageTag(temp, i);
			}
			else if (temp[2] == 'f')
			{
				collection[i] = new VideoTag(temp, i);
			}
		}
		else
		{
			collection[i] = new SimpleTag(temp, i);
		}

		delete[]temp;
	}
	ifs.close();
}

void TagCollection::copyFrom(const TagCollection & other)
{
	fileName = new char[strlen(other.fileName)+1];
	strcpy_s(fileName,strlen(other.fileName)+1,other.fileName);
	size = other.size;
	capacity = other.capacity;
	collection = new Tag*[other.capacity];
	for (size_t i = 0; i < other.size; ++i)
	{
		collection[i] = other.collection[i]->clone();
	}

}

void TagCollection::clean()
{
	if (fileName != nullptr)
	{
		delete[]fileName;
		fileName = nullptr;
	}
	if (collection != nullptr)
	{
		for (size_t i = 0; i < size; ++i)
		{
			delete collection[i];
		}
		delete[] collection;
		collection = nullptr;
	}
	size = 0;
	capacity = 0;
}

void TagCollection::resize()
{
	Tag**newCollection = new Tag*[capacity*2];
	capacity *= 2;
	for (size_t i = 0; i < size; ++i)
	{
		newCollection[i] = collection[i];
	}
	delete[] collection;
	collection = newCollection;
}
