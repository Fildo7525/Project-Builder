#include "BuildProject.h"

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printHelp(std::cout);
		return 0;
	}

	auto [opts, projectName] = deduceFlagOptions(argc, argv);

	switch (opts.lang) {
		case flags::language::cpp:
			makeCppProject(projectName, opts);
			break;
		case flags::language::java:
			makeJavaProject(projectName, opts);
			break;
		default:
			std::cerr << "Filetype does not exist\n";
			printHelp();
			return 1;
	}

	return 0;
}

