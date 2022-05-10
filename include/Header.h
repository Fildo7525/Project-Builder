#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <getopt.h>
#include <vector>

#define GREEN "\033[32;2m"
#define GREEN_BOLD "\033[32;1m"
#define GREEN_BOLD_ITALICS "\033[32;1;3m"
#define	RED "\033[31;2m"
#define ORANGE "\033[48:2:255:165;1m"
#define NORM "\033[0;0m"

#define DEFAULT_PACKAGE_LOCATION "com.example"

void printArgumets(char **argv, int size);

struct flags {
	enum class language {
		java, cpp
	};

	language lang;
	bool qt;
	bool openCV;
	bool maven;
	bool typeFlag;
	bool err;

	flags()
	: lang()
	, qt(false)
	, openCV(false)
	, maven(false)
	, typeFlag(false)
	, err(false) { }
};

void javaCreation(std::string dir, bool maven);
void cppCreation(const std::string&, const flags &languageFlags);

std::vector<std::string> packageDeduction(const std::string &packagePath);
std::string replaceDots(const std::string &packagePath);
