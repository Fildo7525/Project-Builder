#pragma once

#include "Project.h"

class PythonProject : private Project
{
public:
	// Constructor
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

