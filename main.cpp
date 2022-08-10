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
		std::ofstream file(projectName->projectName() + "/.gitignore");
		file << "build/\nbuild.sh\ncompile.sh\n.cache\n\n";
		file.close();
		executeCommand("cd " + projectName->projectName() + " && git init && git add * --ignore-errors; git commit -m \"Initial commit\"");
	}

	return 0;
}

