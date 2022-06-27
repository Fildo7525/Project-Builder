#include "core.h"
#include "include/Header.h"

int main(int argc, char ** argv)
{
	if(argc < 2){
		printHelp(std::cout);
		return 0;
	}

	flags opts = deduceFlagOptions(argc, argv);

	int idx = 2;

	if (opts.lang == flags::language::java) {
		if (opts.maven) {
			idx++;
		}
		std::clog << "Initialising javaCreation with index " << idx << "\n";
		makeJavaProject(argv[idx], opts.maven);
	}
	else if (opts.lang == flags::language::cpp) {
		if (opts.qt) {
			idx++;
		}
		if (opts.openCV) {
			idx++;
			std::clog << "Argument 3 OpenCV: " << argv[idx] << '\n';
		}
		makeCppProject(argv[idx], opts);
	}
	else {
		std::cerr << "Filetype does not exist\n";
		printHelp();
		return 1;
	}
	return 0;
}

