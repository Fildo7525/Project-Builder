#include "PythonProject.h"

#include "core.h"

#include <fstream>

PythonProject::PythonProject(const std::string &dir, const flags &languageFlags)
: Project(dir, languageFlags)
{
}

void PythonProject::generate()
{
	executeCommand("mkdir " + m_dir);
	makeMainFiles();
	makeBuildFiles();
}

void PythonProject::makeMainFiles()
{
	std::string command = "cd " + m_dir + " && touch main.py";
	std::ofstream file(m_dir + "/main.py");
	file << "print('Hello world!')" << std::endl;
	executeCommand(command, "Command: " + command + " could not be executed");
}

void PythonProject::makeBuildFiles()
{
	std::string command = "cd " + m_dir + " && touch run && chmod 744 run";
	executeCommand(command);

	std::ofstream file(m_dir + "/run");
	file << shellInit() << "\n\n"
		<< "python main.py\n";
	file.close();
}

