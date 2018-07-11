#ifndef TAG_COLLECTION_CLASS_HEADER
#define TAG_COLLECTION_CLASS_HEADER
#include <fstream>

#include"TitleTag.h"
#include"SimpleTag.h"
#include"HyperlinkTag.h"
#include"ImageTag.h"
#include"TextTag.h"
#include"VideoTag.h"


class TagCollection
{
private:
	char*fileName;
	Tag**collection;
	unsigned size;
	unsigned capacity;

private:
	bool isValidFile()const;
	bool isValidPos(unsigned pos)const;

	Tag*getTag(const char *descr)const;

	unsigned getFileSize()const;

	void shiftRight(unsigned pos);
	void loadInfoFromFile();
	void copyFrom(const TagCollection&other);
	void clean();
	void resize();

public:
	TagCollection();
	TagCollection(const char*fileNameStr);
	TagCollection(const TagCollection &other);
	TagCollection&operator=(const TagCollection &other);
	~TagCollection();

public:
	void moveTo(unsigned pos,const char*descr);
	void remove(const char* descr);
	void addTag(Tag* newTag);
	void print()const;
	void save()const;
};

#endif // !TAG_COLLECTION_CLASS_HEADER
