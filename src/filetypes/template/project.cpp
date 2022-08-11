#include "project.h"
#include "core.h"

#include <fstream>

Project::Project(const std::string &dir, const flags &languageFlags)
	: m_dir(dir)
	, m_languageFlags(languageFlags)
{
}

std::string Project::projectName()
{
	return m_dir;
}

void Project::initializeGit()
{
	std::ofstream file(projectName() + "/.gitignore");
	file << "build/\nbuild.sh\ncompile.sh\n.cache\n\n";
	file.close();

	executeCommand("cd " + projectName() + " && git init && git add * --ignore-errors; git commit -m \"Initial commit\"");
}

