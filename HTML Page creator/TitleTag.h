#ifndef TITLE_TAG_CLASS_HEADER
#define TITLE_TAG_CLASS_HEADER
#include"Tag.h"

class TitleTag :public Tag
{
private:
	unsigned size;
	char*title;

private:
	virtual void loadHTML(const char*StrHTML);

	unsigned getSizeFromHTML(const char*StrHTML);

	void copyFrom(const TitleTag&other);
	void clean();

public:
	TitleTag();

	//constructor for new Title Tag (not loaded from file)
	TitleTag(const char*descrStr,const char*titleStr,unsigned Size, unsigned Pos);

	//constructor for Title Tag loaded from file (from HTML)
	TitleTag(const char*StrHTML,unsigned Pos);

	TitleTag(const TitleTag&other);
	TitleTag&operator=(const TitleTag&other);
	~TitleTag();

public:
	virtual char*getHTML()const;
	virtual TitleTag*clone();

};

#endif // !TITLE_TAG_CLASS_HEADER
