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

	switch (opts.lang) {
		case flags::language::cpp:
			makeCppProject(projectName, opts);
			break;
		case flags::language::java:
			makeJavaProject(projectName, opts);
			break;
		default:
			error("Filetype does not exist\n");
			printHelp();
			return 1;
	}

	if (opts.useGit) {
		executeCommand("cd " + projectName + " && git init");
	}

	return 0;
}

