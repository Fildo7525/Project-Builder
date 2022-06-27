#include "core.h"

#include <iostream>
#include <unistd.h>

std::ostream &printHelp(std::ostream &os)
{
	return os << "The snippert is incorrect. Use it as buildProject <projectname> -t<language> [options]\n"
				<< "\tsupported languages:\n\t\tcpp:\t-tc\n\t\tjava:\t-tj\n\n"
				<< "\toptions for C++:\n\t\tQT5:\t-q\n\t\tOpenCV:\t-c\n"
				<< "\toptions for Java:\n\t\tMaven:\t-m"
	<< std::endl;
}

void printArgumets(char **argv, int size)
{
	int i = 0;
	for ( ; i < size; i++) {
		std::clog << "Argument " << i << ": " << argv[i] << '\n';
	}
}

std::string shellInit()
{
	return std::string("#!") +  getenv("SHELL");
}

flags deduceFlagOptions(int argc, char **argv)
{
	flags opts;
	int option;

	while((option = getopt(argc, argv,"qcmt:")) != -1){
		std::string newDir(argv[0]);
		switch(option){
			case 't': {
				std::string oarg(optarg);
				// std::cout << "OPTION t Marked\n";
				// printArgumets(argv);
				if(opts.typeFlag)
					std::cerr << RED << "Not allowed for multiple languages\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0) {
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] <-t language>\n"
							<< "Options:\n\t-q QT5 included (C++)\n\t-c OpenCV includec (C++)\n\t-m maven build system (Java)\n\n"
							<< "if language is not specified in particular option than it's ignored"<< NORM << std::endl, exit(2);
				}

				if(oarg == "java" || oarg == "j")
					opts.lang = flags::language::java, opts.typeFlag = true;
				else if(oarg == "cpp" || oarg == "c++" || oarg == "c")
					opts.lang = flags::language::cpp, opts.typeFlag = true;
				break;
			}

			case 'q':
				// std::clog << "QT marked\n";
				opts.qt = true;
				break;

			case 'c':
				opts.openCV = true;
				break;

			case 'm':
				std::cout << "setting m to true\n";
				opts.maven = true;
				break;

			default:
				std::perror("Getopt: "), opts.err = true;
		}
	}
	return opts;
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

