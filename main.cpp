#include "Header.h"

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printHelp(std::cout);
		return 0;
	}

	auto [opts, projectName] = deduceFlagOptions(argc, argv);

	if (opts.lang == flags::language::java) {
		std::clog << "Initialising makeJavaProject with " << projectName << "\n";
		makeJavaProject(projectName, opts);
	}
	else if (opts.lang == flags::language::cpp) {
		std::clog << "Initialising makeCppProject with " << projectName << "\n";
		makeCppProject(projectName, opts);
	}
	else {
		std::cerr << "Filetype does not exist\n";
		printHelp();
		return 1;
	}
	return 0;
}

