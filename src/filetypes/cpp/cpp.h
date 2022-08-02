#pragma once

#include "project.h"

/**
 * @class CppProject
 * @brief Class creating cpp project.
 */
class CppProject : private Project
{
public:
	// Consturctor
	CppProject(const std::string &directory, const flags &options);

	// Overriden funciton from Project class
	void generate() override;

private:

	/**
	 * @brief Function for creating cpp project.
	 */
	void makeCppProject();

	/**
	 * @brief Returns the cmake version in type of 3.16.3.
	 */
	std::string cmakeVersion();

	/**
	 * @brief Generates file main.cpp in the Direcotry dir with specified language options.
	 */
	void generateMainFile();

	/**
	 * @brief Create '${dir}.cpp' and '${dir}.h' files.
	 */
	void generateDirectoryNamedFiles();

	/**
	 * @brief Create CMakeLists.txt file according to specified options.
	 */
	void generateCmakeFile();

	/**
	 * @brief Create build.sh and compile.sh files.
	 */
	void generateBuildFiles();
};

