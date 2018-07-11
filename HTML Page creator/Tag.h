#ifndef TAG_CLASS_HEADER
#define TAG_CLASS_HEADER
#include<iostream>
#include"Helper.h"
class Tag
{
protected:
	//basic data
	//every tag has a desription and a position
	char*descr;
	unsigned pos;

protected:
	 void copyFrom(const Tag&other);
	 void clean();

	//eEvery tag can load its information from HTM text
	virtual void loadHTML(const char*StrHTML) = 0;

	//every tag has a (description or a link...) and this method will extract
	//that from the HTML
	virtual char*getTagAfterStr(const char * StrHTML, const char*Str);
	//most of the text is in between >...< brackets
	virtual char *getBetweenBrackets(const char*StrHTML);

public:
	//BIG FOUR
	Tag();
	Tag(const char*descrStr, unsigned Pos);
	Tag(const Tag&other);
	Tag&operator=(const Tag&other);
	virtual~Tag();

public:
	//get and set methods
	virtual const char*getDescription()const;
	virtual const unsigned getPos()const;
	
	virtual void setPos(const unsigned p);
	virtual void setDescription(const char*descrStr);


	//every type of Tag should be able to produce HTML
	virtual char*getHTML()const = 0;
	virtual Tag*clone() = 0;
};

#endif // !TAG_CLASS_HEADER
