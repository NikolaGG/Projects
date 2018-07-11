#include "TitleTag.h"

void TitleTag::copyFrom(const TitleTag & other)
{
	Tag::copyFrom(other);
	title = new char[strlen(other.title) + 1];
	if (!title)
		throw std::bad_alloc();
	strcpy_s(title, strlen(other.title) + 1,other.title);
	size = other.size;
}

void TitleTag::clean()
{
	if (title != nullptr)
	{
	delete[]title;
	title = nullptr;
	}
	Tag::clean();
	size = 0;
}

TitleTag::TitleTag() :Tag(), title(nullptr), size(0)
{}

TitleTag::TitleTag(const char * descrStr, const char * titleStr, unsigned Size, unsigned Pos):Tag(descrStr,Pos),size(Size)
{
	try
	{
		title = new char[strlen(titleStr) + 1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for TitleTag constructor.\n";
	}
	strcpy_s(title,strlen(titleStr)+1,titleStr);
}

TitleTag::TitleTag(const char * StrHTML, unsigned Pos) :Tag(), title(nullptr), size(0)
{
	pos = Pos;
	try
	{
	loadHTML(StrHTML);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for TitleTag constructor(from HTML).\n";
	}
}

TitleTag::TitleTag(const TitleTag & other) :Tag(), title(nullptr), size(0)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for TitleTag in copy constructor.\n";
	}
}

TitleTag & TitleTag::operator=(const TitleTag & other)
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
			std::cerr << "Could not alocate memory for TitleTag in operator=.\n";
		}
	}
	return *this;
}

TitleTag::~TitleTag()
{
	clean();
}

void TitleTag::loadHTML(const char * StrHTML)
{
	descr = getTagAfterStr(StrHTML,descrTagConst);
	title = getBetweenBrackets(StrHTML);
	size = getSizeFromHTML(StrHTML);
}

unsigned TitleTag::getSizeFromHTML(const char * StrHTML)
{
	//<h(size) descr="(descr)">(title)</h(size)>
	//<h1 descr="main heading">HTML PAGE CREATOR</h1>
	unsigned size = strlen(StrHTML)+1;
	for (size_t i = 0; i < size; ++i)
	{
		if (StrHTML[i] == '<'&&StrHTML[i+1] == 'h')
		{
			if (isNumber(StrHTML[i+2]))
			{
				unsigned x = charToUnsigned(StrHTML[i + 2]);
				return x;
			}
		}
	}
	return 1;
}


char * TitleTag::getHTML() const
{
	//<h(size) descr="(descr)">(title)</h(size)>
	//<h1 descr="main heading">HTML PAGE CREATOR</h1>
	char buff[MAX_TAG_LENGTH];
	strcpy_s(buff,strlen("<")+1,"<");
	strcat_s(buff,titleTagConst);
	strcat_s(buff, intToStr(size));
	strcat_s(buff," descr=\"");
	strcat_s(buff,descr);
	strcat_s(buff,"\">");
	strcat_s(buff,title);
	strcat_s(buff,"</");
	strcat_s(buff,titleTagConst);
	strcat_s(buff, intToStr(size));
	strcat_s(buff,">");

	char*HTML = new char[strlen(buff) + 1];
	strcpy_s(HTML, strlen(buff) + 1, buff);

	return HTML;
}

TitleTag * TitleTag::clone()
{
	return new TitleTag(*this);
}
