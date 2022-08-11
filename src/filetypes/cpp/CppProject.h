/**
 * @file
 * @brief C++ project class generator.
 */

#pragma once

#include "Project.h"

/**
 * @class CppProject
 * @brief Class creating cpp project.
 *
 * Overrides 'generate' function from Project class.
 * This class generates main.cpp file which includes ./src/${directory}.cpp and ./src/${directory}.h
 * As pointed out, the header and source files are generated in separated directory named 'src'.
 * There is clreated a library 'lib' using cmake and added to the main cmake in the root direcotry.
 * Additional two files are generated to ease the compilation. Both script files will have shebang generated according to the environment variable
 * ${SEHLL}. The files are 'build.sh' and 'compile.sh'
 * As the names say the build will build the project and than run the executable stored in 'build' folder.
 * On the other hand the 'compile.sh' will just compile the project and store the makefile and execute make in build directory.
 * The project sturcture will than look something like this:<br>
 <pre>
  project +
          | - src +
          |       | - project.cpp
          |       | - project.h
          | - main.cpp
          | - CMakeLists.txt
          | - build.sh
          | - compile.sh
 </pre>
 * Based on the flags the project can support Qt5, OpenCV and Raspbery Pi
 * You are able to decide wether you want to initailse git repositary.
 */
class CppProject : private Project
{
public:
	/**
	 * @brief Consturctor
	 *
	 * @param directory The relative path to the directory that is to be created.
	 * @param options Already set options based on the command line arguments.
	 */
	CppProject(const std::string &directory, const flags &options);

	/**
	 * @brief Overriden funciton from Project class
	 *
	 * Calls private member functions and generates the Cpp project.
	 */
	void generate() override;

	/**
	 * @brief Sets ros2 arguments.
	 *
	 * @param rosArguments Arguments that will be forwarded to ros2 command.
	 */
	void initializeRosArguments(const std::string &rosArguments);

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

private:
	// arguments passed to ros2 command.
	std::string m_rosArguments;
};

