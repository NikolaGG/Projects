#include "HyperlinkTag.h"

void HyperlinkTag::loadHTML(const char * StrHTML)
{
	descr = getTagAfterStr(StrHTML,descrTagConst);
	text = getBetweenBrackets(StrHTML);
	link = getTagAfterStr(StrHTML,linkTagConst);
}


void HyperlinkTag::copyFrom(const HyperlinkTag & other)
{
	Tag::copyFrom(other);
	text = new char[strlen(other.text) + 1];
	if (!text)
		throw std::bad_alloc();
	strcpy_s(text, strlen(other.text) + 1,other.text);
	link = new char[strlen(other.link) + 1];
	if (!link)
		throw std::bad_alloc();
	strcpy_s(link, strlen(other.link) + 1, other.link);
}

void HyperlinkTag::clean()
{
	if (text != nullptr)
	{
		delete[] text;
		text = nullptr;
	}
	if (link != nullptr)
	{
		delete[] link;
		link = nullptr;
	}
	Tag::clean();
}

HyperlinkTag::HyperlinkTag():Tag(),text(nullptr),link(nullptr)
{}

HyperlinkTag::HyperlinkTag(const char * descrStr, const char * textStr, const char * linkStr, unsigned Pos)
	                      :Tag(descrStr,Pos), text(nullptr), link(nullptr)
{
	try
	{
	text = new char[strlen(textStr)+1];
	link = new char[strlen(linkStr)+1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory in HyperlinkTag constructor.\n";
	}
	strcpy_s(text,strlen(textStr)+1,textStr);
	strcpy_s(link,strlen(linkStr)+1,linkStr);
}

HyperlinkTag::HyperlinkTag(const char * StrHTML, unsigned Pos)
{
	pos = Pos;
	try
	{
		loadHTML(StrHTML);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for HyperlinkTag constructor(from HTML).\n";
	}
}

HyperlinkTag::HyperlinkTag(const HyperlinkTag & other): text(nullptr), link(nullptr)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for HyperlinkTag in copy constructor.\n";
	}
}

HyperlinkTag & HyperlinkTag::operator=(const HyperlinkTag & other)
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
			std::cerr << "Could not alocate memory for HyperlinkTag in operator =.\n";
		}
	}
	return *this;
}

HyperlinkTag::~HyperlinkTag()
{
	clean();
}



char * HyperlinkTag::getHTML() const
{
	//<a href="(link)" descr="(descr)">(text)</a>
	//<a href="https://www.facebook.com/Д-р-Радева-890574957631210/" descr="help">wanna help?</a>
	char buff[MAX_TAG_LENGTH];
	strcpy_s(buff, strlen("<") + 1, "<");
	strcat_s(buff,hyperLinkTagConst);
	strcat_s(buff," href=\"");
	strcat_s(buff,link);
	strcat_s(buff, "\" descr=\"");
	strcat_s(buff, descr);
	strcat_s(buff, "\">");
	strcat_s(buff,text);
	strcat_s(buff,"</a>");

	char*HTML = new char[strlen(buff) + 1];
	strcpy_s(HTML, strlen(buff) + 1, buff);

	return HTML;
}

HyperlinkTag * HyperlinkTag::clone()
{
	return new HyperlinkTag(*this);
}
