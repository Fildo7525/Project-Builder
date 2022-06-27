#include "core.h"
#include "include/Header.h"

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printHelp(std::cout);
		return 0;
	}

	flags opts = deduceFlagOptions(argc, argv);

	int projectNameIdx = 2;

	if (opts.lang == flags::language::java) {
		if (opts.maven) {
			projectNameIdx++;
		}
		std::clog << "Initialising javaCreation with index " << projectNameIdx << "\n";
		makeJavaProject(argv[projectNameIdx], opts);
	}
	else if (opts.lang == flags::language::cpp) {
		if (opts.qt) {
			projectNameIdx++;
		}
		if (opts.openCV) {
			projectNameIdx++;
			std::clog << "Argument 3 OpenCV: " << argv[projectNameIdx] << '\n';
		}
		makeCppProject(argv[projectNameIdx], opts);
	}
	else {
		std::cerr << "Filetype does not exist\n";
		printHelp();
		return 1;
	}
	return 0;
}

