/**
 * @file
 * @brief Python project generation class.
 */

#pragma once

#include "Project.h"

/**
 * @class PythonProject
 * @brief Class creating python3 project
 *
 * Overrides generate function. This class doesn't do much. There are created main.py file and generator shell scripts. Shebangs are defined based on your actual SHELL environment variable.
 */
class PythonProject : private Project
{
public:
	/// Constructor
	PythonProject(const std::string &dir, const flags &languageFlags);

	/**
	 * @brief Overriden funciton from Project.
	 */
	void generate() override;

private:
	/**
	 * @brief Creates main.py in specified directory.
	 */
	void makeMainFiles();

	/**
	 * @brief Creates build.sh in specified direcoty.
	 */
	void makeBuildFiles();
};

