#include "Tag.h"

void Tag::copyFrom(const Tag & other)
{
	descr = new char[strlen(other.descr) + 1];
	if (!descr)
		throw std::bad_alloc();
	strcpy_s(descr, strlen(other.descr) + 1, other.descr);
	pos = other.pos;
}

void Tag::clean()
{
	
	if (descr != nullptr)
	{
		delete[] descr;
		descr = nullptr;
		pos = 0;
	}
}

Tag::Tag() :descr(nullptr),pos(0)
{}

Tag::Tag(const char * descrStr, unsigned Pos) : descr(nullptr), pos(Pos)
{
	try
	{
	descr = new char[strlen(descrStr) + 1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for description in Tag constructor.\n";
	}
	strcpy_s(descr, strlen(descrStr) + 1,descrStr);
}

Tag::Tag(const Tag & other) :descr(nullptr)
{
	try
	{
	copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for Tag in copy constructor.\n";
	}
}

Tag & Tag::operator=(const Tag & other)
{
	if (this != &other)
	{
		clean();
		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Could not alocate memory for Tag in operator= constructor.\n";
		}
	}
	return *this;
}

Tag::~Tag()
{
	clean();
}

const char * Tag::getDescription() const
{
	return descr;
}

const unsigned Tag::getPos() const
{
	return pos;
}

void Tag::setPos(const unsigned p)
{
	pos = p;
}

void Tag::setDescription(const char * descrStr)
{
	if (descr != nullptr)
	{
		delete[]descr;
		descr = nullptr;
	}
	try
	{
		descr = new char[strlen(descrStr) + 1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory to set new description!\n";
	}
	strcpy_s(descr, strlen(descrStr) + 1, descrStr);
}


char * Tag::getTagAfterStr(const char * StrHTML,const char*Str)
{
	unsigned searcSize = strlen(Str);
	char *search = new char[searcSize+1];
	
	char buff[MAX_TAG_LENGTH];
	unsigned size = strlen(StrHTML) + 1;
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < searcSize; ++j)
		{
			search[j] = StrHTML[i + j];
		}
		search[searcSize] = '\0';
		if (strcmp(Str, search) == 0)
		{
			unsigned cnt = i;
			while (true)
			{
				if (StrHTML[cnt] == '"')
				{
					unsigned j = 0;
					unsigned cnt2 = cnt + 1;
					while (StrHTML[cnt2] != '"')
					{
						buff[j] = StrHTML[cnt2];
						++cnt2;
						++j;
					}
					buff[j] = '\0';
					break;
				}
				++cnt;
			}
		}
	}
	delete[] search;
	char*descrHTML = new char[strlen(buff) + 1];
	strcpy_s(descrHTML, strlen(buff) + 1, buff);
	return descrHTML;
}

char * Tag::getBetweenBrackets(const char * StrHTML)
{
	unsigned size = strlen(StrHTML) + 1;
	char buff[MAX_TAG_LENGTH];
	for (size_t i = 0; i < size; ++i)
	{
		if (StrHTML[i] == '>')
		{
			i++;
			unsigned cnt = 0;
			while (StrHTML[i] != '<')
			{
				buff[cnt] = StrHTML[i];
				cnt++;
				i++;
			}
			buff[cnt] = '\0';
			char * temp = new char[strlen(buff) + 1];
			strcpy_s(temp, strlen(buff) + 1, buff);
			return temp;
		}
	}
	return nullptr;
}
