#ifndef SIMPLE_TAG_CLASS_HEADER
#define SIMPLE_TAG_CLASS_HEADER
#include"Tag.h"

class SimpleTag :public Tag
{
//the simple tag is already HTML
//has no other data no need for big FOUR
private:
	virtual void loadHTML(const char*StrHTML);

public:
	SimpleTag(const char*descrStr,unsigned Pos);

public:
	virtual char*getHTML()const;
	virtual SimpleTag*clone();

};



#endif // !SIMPLE_TAG_CLASS_HEADER
