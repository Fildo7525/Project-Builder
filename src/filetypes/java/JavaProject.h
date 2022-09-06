/**
 * @file
 * @brief Java project class generator.
 */

#pragma once

#include "core.h"

#include <string>

#define DEFAULT_PACKAGE_LOCATION "com.example"

/**
 * @class JavaProject
 * @brief Class creating java project.
 *
 * Overrides generate funciton. Creates package based on the user input after inputting the command. The package name is stored in java (dotted notation) and also in GNU/Linux (slashed notation). Generates Main.java file with supported class and funciton. Based on the flags the porject can have a builder tool maven or without builder. In the first case and in the second case the shell scripts will be created with accurate shebang. The same as with other projects compile.sh compiles the project and build.sh builds and executes the program. It doesn't matter wether you specified the maven option. The scripts will be generated accordingly.
 */
class JavaProject : private Project
{
public:
	/// Constructor
	JavaProject(const std::string &dir, const flags &languageFlags);

	/// Overriden funciton from interface Project.
	void generate() override;

private:

	/**
	* @brief Retrieve unix relative path from java package style.
	*/
	std::string pathFromJavaPackagePath();

	/**
	* @brief Returns pair of [Linux type path, java package path]
	*/
	void linuxAndJavaPaths();

	/**
	* @brief Generates Main.java in specified direcotry.
	*/
	void generateMainFile();

	/**
	* @brief Generates pom.xml if maven build system is specified.
	*/
	void generatePomXML();

	/**
	* @brief Generates build.sh and compile.sh.
	*/
	void generateBuildFiles();

private:
	/// Location of the package of Main.java in Java style.
	std::string m_packageLocation;

	/// Location of the package of Main.java in Linux/GNU style.
	std::string m_slashedPackedLocation;
};

