#include "core.h"

#include <unistd.h>
#include <getopt.h>

std::ostream &printHelp(std::ostream &os)
{
	indent tabs;
	return os << tabs.up()() << "~ Help for Project-Builder ~\n\n"
			  << "Command execution:\n"
			  << tabs() << "buildProject <projectname> --type/-t <language> [options]\n\n"

			  << tabs() << "--help -h\tPrint this help\n"
			  << tabs() << "--no-git -g\tProhibit default git repozitory initialization\n"
			  << tabs() << "--type -t\tDefine project language\n\n"

			  << tabs() << "supported languages:\n"
			  << tabs.up()() << "cpp:\t--type c / cpp / c++\n"
			  << tabs()		 << "java:\t--type j / java\n\n" << tabs.down()()
			  << "options for C++:\n"
			  << tabs.up()() << "QT5:\t--qt5 / -q\n"
			  << tabs()		 << "OpenCV:\t--opencv / -c\n" << tabs.down()()
			  << "options for Java:\n"
			  << tabs.up()() << "Maven:\t--maven / -m"
	<< std::endl;
}

void printArgumets(char **argv, int size)
{
	int i = 0;
	for ( ; i < size; i++) {
		std::clog << "Argument " << i << ": " << argv[i] << '\n';
	}
}

void executeCommand(const std::string &command, const std::string &errorMessage)
{
	if (system(command.c_str()) != 0) {
		std::cerr << errorMessage << std::endl;
		exit(1);
	}
}

std::string shellInit()
{
	return std::string("#!") +  getenv("SHELL");
}

std::pair<flags, std::string> deduceFlagOptions(int argc, char **argv)
{
	flags opts;
	int option;
	int false_option = 0;

	struct option long_options[] = {
		{"type",	required_argument, 0, 't'},
		{"qt5",		no_argument,	   0, 'q'},
		{"maven",	no_argument,	   0, 'm'},
		{"opencv",	no_argument,	   0, 'c'},
		{"no-git",	no_argument,	   0, 'g'},
		{"help"	,	no_argument,	   0, 'h'},
		{0,			0,				   0,  0 }
	};

	while((option = getopt_long(argc, argv,"t:qmcgh", long_options, &false_option)) != -1){
		std::string newDir(argv[1]);

		switch(option){
			case 't': {
				std::string projectType = optarg;

				if(opts.lang != flags::language::none)
					std::cerr << RED << "Not allowed for multiple languages\n" << NORM << std::ends, exit(1);
				if(newDir[0] == '-') {
					std::cerr << RED << "Directory must be specified as a second argument.\n" << NORM << std::endl;
					printHelp();
					exit(2);
				}

				if(projectType == "java" || projectType == "j")
					opts.lang = flags::language::java;
				else if(projectType == "cpp" || projectType == "c++" || projectType == "c")
					opts.lang = flags::language::cpp;
				break;
			}

			case 'q':
				opts.qt = true;
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

			default:
				std::perror("Getopt: "), opts.err = true;
		}
	}
	return {opts, argv[argc-1]};
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

