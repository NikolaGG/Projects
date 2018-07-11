#include "VideoTag.h"

void VideoTag::loadHTML(const char * StrHTML)
{
	descr = getTagAfterStr(StrHTML, descrTagConst);
	videoLink = getTagAfterStr(StrHTML, videoConst);
}

void VideoTag::copyFrom(const VideoTag & other)
{
	Tag::copyFrom(other);
	videoLink = new char[strlen(other.videoLink) + 1];
	if (!videoLink)
		throw std::bad_alloc();
	strcpy_s(videoLink,strlen(other.videoLink)+1,other.videoLink);
}

void VideoTag::clean()
{
	if (videoLink != nullptr)
	{
		delete[]videoLink;
		videoLink = nullptr;
	}
	Tag::clean();
}

VideoTag::VideoTag():Tag(),videoLink(nullptr)
{}

VideoTag::VideoTag(const char * descrStr, const char * videoLinkStr, unsigned Pos) : Tag(descrStr,Pos), videoLink(nullptr)
{
	try
	{
	videoLink = new char[strlen(videoLinkStr) + 1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for Video tag constructor.\n";
	}
	strcpy_s(videoLink,strlen(videoLinkStr)+1,videoLinkStr);
}

VideoTag::VideoTag(const char * StrHTML, unsigned Pos)
{
	pos = Pos;
	try
	{
	loadHTML(StrHTML);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for Video tag constructor.\n";
	}
}

VideoTag::VideoTag(const VideoTag & other)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory in video tag copy constructor.\n";
	}
}

VideoTag & VideoTag::operator=(const VideoTag & other)
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
			std::cerr << "Could not alocate memory in video tag operator =.\n";
		}
	}
	return *this;
}

VideoTag::~VideoTag()
{
	clean();
}

char * VideoTag::getHTML() const
{
	//<iframe src="(videoLink)" descr="(descr)"></iframe>
	//<iframe src="https://www.youtube.com/embed/f4Mc-NYPHaQ" descr="wanna break"></iframe>
	char buff[MAX_TAG_LENGTH];
	strcpy_s(buff, strlen("<") + 1, "<");
	strcat_s(buff,videoTagConst);
	strcat_s(buff," src=\"");
	strcat_s(buff,videoLink);
	strcat_s(buff,"\" descr=\"");
	strcat_s(buff,descr);
	strcat_s(buff,"\">< / ");
	strcat_s(buff,videoTagConst);
	strcat_s(buff,">");

	char*HTML = new char[strlen(buff) + 1];
	strcpy_s(HTML, strlen(buff) + 1, buff);

	return HTML;
}

VideoTag * VideoTag::clone()
{
	return new VideoTag(*this);
}
