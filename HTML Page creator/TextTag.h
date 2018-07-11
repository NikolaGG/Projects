#ifndef TEXT_TAG_CLASS_HEADER
#define TEXT_TAG_CLASS_HEADER
#include"Tag.h"
class TextTag:public Tag

{
private:
	char*text;

private:
	virtual void loadHTML(const char*StrHTML);

	void copyFrom(const TextTag &other);
	void clean();

public:
	TextTag();

	//constructor for new Text Tag
	TextTag(const char*descrStr, const char*textStr, unsigned Pos);

	//constructor for Text Tag loaded from file (from HTML)
	TextTag(const char*StrHTML, unsigned Pos);

	TextTag(const TextTag& other);
	TextTag&operator=(const TextTag& other);
	~TextTag();

public:
	virtual char*getHTML()const;
	virtual TextTag*clone();

};

#endif // !TEXT_TAG_CLASS_HEADER
