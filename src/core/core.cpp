#include "core.h"

#include <unistd.h>
#include <getopt.h>

std::ostream &printHelp(std::ostream &os)
{
	return os << "The snippert is incorrect. Use it as\n\nbuildProject <projectname> --type/-t <language> [options]\n\n"
				<< "\tsupported languages:\n\t\tcpp:\t--type c / cpp / c++\n\t\tjava:\t--type j / java\n\n"
				<< "\toptions for C++:\n\t\tQT5:\t--qt5 / -q\n\t\tOpenCV:\t--opencv / -c\n"
				<< "\toptions for Java:\n\t\tMaven:\t--maven / -m"
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
		{0,			0,				   0,  0 }
	};

	while((option = getopt_long(argc, argv,"qcmt:", long_options, &false_option)) != -1){
		std::string newDir(argv[0]);

		switch(option){
			case 't': {
				std::string projectType = optarg;

				if(opts.typeFlag)
					std::cerr << RED << "Not allowed for multiple languages\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0) {
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] <-t language>\n"
							<< "Options:\n\t-q QT5 included (C++)\n\t-c OpenCV includec (C++)\n\t-m maven build system (Java)\n\n"
							<< "if language is not specified in particular option than it's ignored"<< NORM << std::endl, exit(2);
				}

				if(projectType == "java" || projectType == "j")
					opts.lang = flags::language::java, opts.typeFlag = true;
				else if(projectType == "cpp" || projectType == "c++" || projectType == "c")
					opts.lang = flags::language::cpp, opts.typeFlag = true;
				break;
			}

			case 'q':
				opts.qt = true;
				break;

			case 'c':
				opts.openCV = true;
				break;

			case 'm':
				opts.maven = true;
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

