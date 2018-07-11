#include "TextTag.h"

void TextTag::loadHTML(const char * StrHTML)
{
	descr = getTagAfterStr(StrHTML, descrTagConst);
	text = getBetweenBrackets(StrHTML);
}

void TextTag::copyFrom(const TextTag & other)
{
	Tag::copyFrom(other);
	text = new char[strlen(other.text) + 1];
	if (!text)
		throw std::bad_alloc();
	strcpy_s(text, strlen(other.text) + 1, other.text);

}

void TextTag::clean()
{
	if (text != nullptr)
	{
		delete[] text;
		text = nullptr;
	}
	Tag::clean();
}

TextTag::TextTag():Tag(),text(nullptr)
{}

TextTag::TextTag(const char * descrStr, const char * textStr, unsigned Pos):Tag(descrStr,Pos),text(nullptr)
{
	try
	{
		text = new char[strlen(textStr) + 1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory in TextTag constructor.\n";
	}
	strcpy_s(text, strlen(textStr) + 1, textStr);

}

TextTag::TextTag(const char * StrHTML, unsigned Pos)
{
	pos = Pos;
	try
	{
		loadHTML(StrHTML);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for TextTag constructor(from HTML).\n";
	}
}

TextTag::TextTag(const TextTag & other)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory in Text Tag copy constructor.\n";
	}
}

TextTag & TextTag::operator=(const TextTag & other)
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
			std::cerr << "Could not alocate memory in Text Tag operator=.\n";
		}
	}
	return *this;
}

TextTag::~TextTag()
{
	clean();
}

char * TextTag::getHTML() const
{
	//<p descr="(descr)">(text)</p>
	//<p descr="before">The life before FMI: </p>

	char buff[MAX_TAG_LENGTH];
	strcpy_s(buff, strlen("<") + 1, "<");
	strcat_s(buff, textTagConst);
	strcat_s(buff," descr=\"");
	strcat_s(buff, descr);
	strcat_s(buff, "\">");
	strcat_s(buff, text);
	strcat_s(buff,"</p>");

	char*HTML = new char[strlen(buff) + 1];
	strcpy_s(HTML, strlen(buff) + 1, buff);

	return HTML;
	
}

TextTag * TextTag::clone()
{
	return new TextTag(*this);
}
