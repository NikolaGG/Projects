#ifndef VIDEO_TAG_HEADER_CLASS
#define VIDEO_TAG_HEADER_CLASS
#include "Tag.h"

class VideoTag :public Tag
{
private:
	char*videoLink;

private:
	virtual void loadHTML(const char*StrHTML);

	void copyFrom(const VideoTag &other);
	void clean();

public:
	VideoTag();

	//constructor for new Video Tag (not loaded from file)
	VideoTag(const char*descrStr,const char*videoLinkStr,unsigned Pos);

	//constructor for Hyperlink Video Tag from file (from HTML)
	VideoTag(const char*StrHTML, unsigned Pos);

	VideoTag(const VideoTag&other);
	VideoTag&operator=(const VideoTag&other);
	~VideoTag();

public:
	virtual char*getHTML()const;
	virtual VideoTag*clone();

};

#endif // !VIDEO_TAG_HEADER_CLASS
