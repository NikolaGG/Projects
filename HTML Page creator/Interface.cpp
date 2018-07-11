#include "Interface.h"

Interface::Interface():curent()
{

}

Interface::Interface(const char * name) : curent(name)
{
}

Interface::~Interface()
{
}

void Interface::menu()
{
	while (true)
	{
		char *name = new char[MAX_TAG_LENGTH];
		std::cout << "Enter file name: \n";
		std::cin.getline(name, MAX_TAG_LENGTH);
		TagCollection newCurrent(name);
		curent = newCurrent;
		while (true)
		{
			std::cout << "Commands : [add] | [remove] | [print] | [move to] | [load] | [save] | [exit]\n";

			char*command = new char[MAX_TAG_LENGTH];
			std::cin.getline(command, MAX_TAG_LENGTH);


			if (strcmp(command, "add") == 0)
			{
				add();
			}
			if (strcmp(command, "remove") == 0)
			{
				remove();
			}
			if (strcmp(command, "print") == 0)
			{
				print();
			}
			if (strcmp(command, "move to") == 0)
			{
				moveTo();
			}
			if (strcmp(command, "load") == 0)
			{
				save();
				delete[]command;
				break;
			}
			if (strcmp(command, "save") == 0)
			{
				save();
			}
			if (strcmp(command, "exit") == 0)
			{
				save();
				delete[]command;
				return;
			}
			delete[]command;
		}

		delete[] name;
	}
}

void Interface::add()
{
	unsigned pick;
	std::cout << "1.Headline Tag\n";
	std::cout << "2.Text Tag\n";
	std::cout << "3.Video Tag\n";
	std::cout << "4.Image Tag\n";
	std::cout << "5.Link Tag\n";
	std::cout << "Pick tag type[number]:\n";
	std::cin >> pick;
	std::cin.ignore();
	char*descr = new char[MAX_TAG_LENGTH];
	std::cout << "Description:\n";
	std::cin.getline(descr, MAX_TAG_LENGTH);
	if (pick == 1)
	{
		unsigned headerSize;
		std::cout << "Enter heading size.\n";
		std::cin >> headerSize;
		std::cin.ignore();
		char * title = new char[MAX_TAG_LENGTH];
		std::cout << "Enter title.\n";
		std::cin.getline(title, MAX_TAG_LENGTH);
		curent.addTag(new TitleTag(descr, title, headerSize, 0));
		delete[]title;
	}
	if (pick == 2)
	{
		std::cout << "Enter text.\n";
		char * text = new char[MAX_TAG_LENGTH];
		std::cin.getline(text, MAX_TAG_LENGTH);
		curent.addTag(new TextTag(descr, text, 0));
		delete[]text;

	}
	if (pick == 3)
	{
		std::cout << "Enter videolink.\n";
		char * text = new char[MAX_TAG_LENGTH];
		std::cin.getline(text, MAX_TAG_LENGTH);
		curent.addTag(new VideoTag(descr, text, 0));
		delete[]text;
	}
	if (pick == 4)
	{
		std::cout << "Enter Image location.\n";
		char * text = new char[MAX_TAG_LENGTH];
		std::cin.getline(text, MAX_TAG_LENGTH);
		curent.addTag(new ImageTag(descr, text, 0));
		delete[]text;
	}
	if (pick == 5)
	{
		std::cout << "Enter text.\n";
		char * text = new char[MAX_TAG_LENGTH];
		std::cin.getline(text, MAX_TAG_LENGTH);
		std::cout << "Enter Link.\n";
		char*linkStr = new char[MAX_TAG_LENGTH];
		std::cin.getline(linkStr, MAX_TAG_LENGTH);
		curent.addTag(new HyperlinkTag(descr, text, linkStr, 0));
		delete[]text;
		delete[]linkStr;
	}
	delete[]descr;
}

void Interface::remove()
{
	char*descr = new char[MAX_TAG_LENGTH];
	std::cout << "Description:\n";
	std::cin.getline(descr, MAX_TAG_LENGTH);
	curent.remove(descr);
	delete[]descr;
}

void Interface::print()
{
	curent.print();
}

void Interface::moveTo()
{
	unsigned pos;
	std::cout << "Position:\n";
	std::cin >> pos;
	std::cin.ignore();
	char*descr = new char[MAX_TAG_LENGTH];
	std::cout << "Description:\n";
	std::cin.getline(descr, MAX_TAG_LENGTH);
	curent.moveTo(pos, descr);
	delete[]descr;
}

void Interface::save()
{
	curent.save();
}

