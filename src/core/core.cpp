#include "core.h"
#include "flags.h"

#include "src/filetypes/cpp/CppProject.h"
#include "src/filetypes/java/JavaProject.h"
#include "src/filetypes/python/PythonProject.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <stdexcept>
#include <unistd.h>
#include <getopt.h>

std::ostream &printHelp(std::ostream &os)
{
	std::fstream helpFile(HELP_FILE, std::ios::in);
	while(helpFile.good()) {
		std::string line;
		std::getline(helpFile, line);
		os << line << std::endl;
	}
	return os;
}

void error(const std::string &msg)
{
	std::cerr << RED << msg << NORM << std::endl;
}

void printArgumets(const char **argv, const int size)
{
	int i = 0;
	for ( ; i < size; i++) {
		std::clog << "Argument " << i << ": " << argv[i] << '\n';
	}
}

void executeCommand(const std::string &command, const std::string &errorMessage)
{
	if (system(command.c_str()) != 0) {
		std::cerr << command << std::endl;
		error(errorMessage);
		exit(1);
	}
}

std::string shellInit()
{
	return std::string("#!") +  getenv("SHELL");
}

std::pair<flags, Project::Ptr> deduceFlagOptions(const int argc, char **argv)
{
	flags opts;
	int option;
	int false_option = 0;
	Project::Ptr newProject(nullptr);

	struct option long_options[] = {
		{"type",	required_argument,	0, 't'},
		{"qt5",		no_argument,		0, 'q'},
		{"rpi",		no_argument,		0, 90 },
		{"maven",	no_argument,		0, 'm'},
		{"opencv",	no_argument,		0, 'c'},
		{"no-git",	no_argument,		0, 'g'},
		{"help"	,	no_argument,		0, 'h'},
		{"list-completion",	no_argument,0, 91},
		{"list-languages",	no_argument,0, 92},
		{"aoc",		no_argument,		0, 'a'},
		{0,			0,					0,  0 }
	};

	std::string newDir(argv[1]);

	while((option = getopt_long(argc, argv, "t:qrmcgha", long_options, &false_option)) != -1){

		switch(option) {
			case 't': {
				std::string projectType = optarg;

				if(opts.lang != flags::language::none) {
					error("Not allowed to create project for multiple languages");
					printHelp();
					exit(1);
				}
				if(newDir[0] == '-') {
					error("Directory must be specified as a second argument.\n");
					printHelp();
					exit(2);
				}

				if (projectType == "java" || projectType == "j") {
					opts.lang = flags::language::java;
				}
				else if (projectType == "cpp" || projectType == "c++" || projectType == "c") {
					opts.lang = flags::language::cpp;
				}
				else if (projectType == "py" || projectType == "python") {
					opts.lang = flags::language::python;
				}
				break;
			}

			case 'q':
				opts.qt = true;
				break;

			case 90:
				opts.rasPi = true;
				break;

			case 'm':
				opts.maven = true;
				break;

			case 'c':
				opts.openCV = true;
				break;

			case 'g':
				opts.useGit = false;
				break;

			case 'h':
				opts.help = true;
				break;

			case 91:
				std::cout << COMPLETION_LIST << std::endl;
				exit(0);

			case 92:
				std::cout << LANGUAGES_LIST << std::endl;
				exit(0);

			case 'a': {
				opts.aoc = true;
				break;
			}

			default:
				std::perror("Getopt: "), opts.err = true;
		}
	}

	switch (opts.lang) {
		case flags::language::cpp:
			newProject.reset((Project*)new CppProject(newDir, opts));
			break;
		case flags::language::java:
			newProject.reset((Project*)new JavaProject(newDir, opts));
			break;
		case flags::language::python:
			newProject.reset((Project*)new PythonProject(newDir, opts));
			break;
		default:
			newProject.reset();
	}
	return {opts, newProject};
}

std::string indent::operator()()
{
	return m_indentation;
}

indent &indent::up()
{
	m_indentation += "\t";
	return *this;
}

indent &indent::down()
{
	if (m_indentation.size() == 0)
		return *this;

	m_indentation.pop_back();
	return *this;
}

