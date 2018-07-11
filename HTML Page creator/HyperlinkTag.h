#ifndef HYPERLINK_TAG_CLASS_HEADER
#define HYPERLINK_TAG_CLASS_HEADER
#include"Tag.h"

class HyperlinkTag :public Tag
{
private:
	char*text;
	char*link;

private:
	virtual void loadHTML(const char*StrHTML);

	void copyFrom(const HyperlinkTag &other);
	void clean();
public:
	HyperlinkTag ();

	//constructor for new Hyperlink Tag (not loaded from file)
	HyperlinkTag(const char*descrStr, const char*textStr, const char*linkStr, unsigned Pos);
	
	//constructor for Hyperlink Tag loaded from file (from HTML)
	HyperlinkTag(const char*StrHTML, unsigned Pos);
	
	HyperlinkTag(const HyperlinkTag &other);
	HyperlinkTag&operator=(const HyperlinkTag &other);
	~HyperlinkTag ();

public:
	virtual char*getHTML()const;
	virtual HyperlinkTag*clone();

};

#endif // !HYPERLINK_TAG_CLASS_HEADER
