#ifndef INTERFACE_CLASS_HEADER
#define INTERFACE_CLASS_HEADER
#include"TagCollection.h"

class Interface
{
private:
	TagCollection curent;

private:
	void add();
	void remove();
	void print();
	void moveTo();
	void save();
	
public:
	Interface();
	Interface(const char*name);
	Interface(const Interface &other) = delete;
	Interface&operator=(const Interface &other) = delete;
	~Interface();

public:
	void menu();

};


#endif // !INTERFACE_CLASS_HEADER
