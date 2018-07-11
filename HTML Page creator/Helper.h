#ifndef HELPER_CLASS_HEADER
#define HELPER_CLASS_HEADER
namespace
{
	const unsigned DEFAULT_HTML_SIZE = 4;
	const unsigned MAX_TAG_LENGTH = 1024;

	const char GENERIC_HTML_FILE_NAME[] = "genericHTML.txt";

	const char titleTagConst[] = "h";
	const char textTagConst[] = "p";
	const char hyperLinkTagConst[] = "a";
	const char videoTagConst[] = "iframe";
	const char imageTagConst[] = "img";
	const char descrTagConst[] = "descr=";
	const char linkTagConst[] = "href=";
	const char videoConst[] = "src=";

	bool isNumber(char x)
{
	if (x >= '0'&&x <= '9')
	{
		return true;
	}
	return false;
}
	char* intToStr(unsigned x)
{
	if (x > 9)
	{
		return "1";
	}
	if (x == 0)
		return "0";
	if (x == 1)
		return "1";
	if (x == 2)
		return "2";
	if (x == 3)
		return "3";
	if (x == 4)
		return "4";
	if (x == 5)
		return "5";
	if (x == 6)
		return "6";
	if (x == 7)
		return "7";
	if (x == 8)
		return "8";
	if (x == 9)
		return "9";
	return "1";
}
	unsigned charToUnsigned(char x)
{
	return x - '0';

}
}


#endif // !HELPER_CLASS_HEADER
