#include "BuildProject.h"

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printHelp(std::cout);
		return 0;
	}

	auto [opts, projectName] = deduceFlagOptions(argc, argv);

	if (opts.help || opts.err) {
		printHelp(std::cout);
		return 0;
	}

	if (!projectName) {
		error("Language is not supported by this program\n");
		printHelp();
		return 1;
	}

	projectName->generate();
	if (opts.useGit) {
		projectName->initializeGit();
	}

	return 0;
}

