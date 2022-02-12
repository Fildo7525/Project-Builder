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
#define NORM "\033[0;0m"

#define DEFAULT_PACKAGE_LOCATION "com.example"

void printArgunets(char **argv);

struct flags {
	enum class language {
		java, cpp
	};

	language t;
	bool q;
	bool typeFlag;
	bool err;

	flags() : t(), q(false), typeFlag(false), err(false) { }
};

void javaCreation(std::string);
void cppCreation(const std::string&, bool qt);

std::vector<std::string> packageDeduction(const std::string &packagePath);
std::string replaceDots(const std::string &packagePath);
