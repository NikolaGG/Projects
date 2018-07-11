#ifndef IMAGE_TAG_CLASS_HEADER
#define IMAGE_TAG_CLASS_HEADER
#include"Tag.h"

class ImageTag :public Tag
{
private:
	char*imageName;

private:
	virtual void loadHTML(const char*StrHTML);

	void copyFrom(const ImageTag &other);
	void clean();

public:
	ImageTag();

	//constructor for new Video Tag (not loaded from file)
	ImageTag(const char*descrStr, const char*imageNameStr, unsigned Pos);

	//constructor for Hyperlink Video Tag from file (from HTML)
	ImageTag(const char*StrHTML, unsigned Pos);

	ImageTag(const ImageTag&other);
	ImageTag&operator=(const ImageTag&other);
	~ImageTag();

public:
	virtual char*getHTML()const;
	virtual ImageTag*clone();

};

#endif // !IMAGE_TAG_CLASS_HEADER
