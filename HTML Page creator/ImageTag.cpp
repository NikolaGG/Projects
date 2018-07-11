#include "ImageTag.h"

void ImageTag::loadHTML(const char * StrHTML)
{
	descr = getTagAfterStr(StrHTML, descrTagConst);
	imageName = getTagAfterStr(StrHTML, videoConst);

}

void ImageTag::copyFrom(const ImageTag & other)
{
	Tag::copyFrom(other);
	imageName = new char[strlen(other.imageName) + 1];
	if (!imageName)
		throw std::bad_alloc();
	strcpy_s(imageName, strlen(other.imageName) + 1, other.imageName);
}

void ImageTag::clean()
{
	if (imageName != nullptr)
	{
		delete[]imageName;
		imageName = nullptr;
	}
	Tag::clean();
}

ImageTag::ImageTag():Tag(),imageName(nullptr)
{}

ImageTag::ImageTag(const char * descrStr, const char * imageNameStr, unsigned Pos):Tag(descrStr,Pos),imageName(nullptr)
{
	try
	{
		imageName = new char[strlen(imageNameStr)+1];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for Image tag constructor.\n";
	}
	strcpy_s(imageName,strlen(imageNameStr)+1,imageNameStr);
}

ImageTag::ImageTag(const char * StrHTML, unsigned Pos)
{
	pos = Pos;
	loadHTML(StrHTML);
}

ImageTag::ImageTag(const ImageTag & other)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Could not alocate memory for Image tag copy constructor.\n";
	}
}

ImageTag & ImageTag::operator=(const ImageTag & other)
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
			std::cerr << "Could not alocate memory for Image tag operator =.\n";
		}
	}
	return *this;
}

ImageTag::~ImageTag()
{
	clean();
}

char * ImageTag::getHTML() const
{
	//<img src="(imageName)" descr="(descr)">
	//<img src="party.jpg" descr="yolo">
	char buff[MAX_TAG_LENGTH];
	strcpy_s(buff, strlen("<") + 1, "<");
	strcat_s(buff,imageTagConst);
	strcat_s(buff," src=\"");
	strcat_s(buff, imageName);
	strcat_s(buff, "\" descr=\"");
	strcat_s(buff, descr);
	strcat_s(buff,"\">");

	char*HTML = new char[strlen(buff) + 1];
	strcpy_s(HTML, strlen(buff) + 1, buff);

	return HTML;
}

ImageTag * ImageTag::clone()
{
	return new ImageTag(*this);
}
