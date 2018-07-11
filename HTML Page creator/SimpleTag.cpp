#include "SimpleTag.h"

SimpleTag::SimpleTag(const char * descrStr, unsigned Pos) :Tag(descrStr, Pos)
{}

void SimpleTag::loadHTML(const char * StrHTML)
{
	//does nothing because the simple tag is already HTML
}

char * SimpleTag::getHTML() const
{
	char*temp = new char[strlen(descr) + 1];
	strcpy_s(temp,strlen(descr)+1 ,descr);
	return temp;
}

SimpleTag * SimpleTag::clone()
{
	return new SimpleTag(*this);
}
