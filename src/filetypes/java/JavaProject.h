#pragma once

#include "core.h"

#include <string>

#define DEFAULT_PACKAGE_LOCATION "com.example"

/**
 * @class JavaProject
 * @brief Class creating java project.
 */
class JavaProject : private Project
{
public:
	// Constructor
	JavaProject(const std::string &dir, const flags &languageFlags)
		: Project(dir, languageFlags)
	{
	}

	// Overriden funciton from interface Project.
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
	// Location of the package of Main.java in Java style.
	std::string m_packageLocation;

	// Location of the package of Main.java in Linux/GNU style.
	std::string m_slashedPackedLocation;
};
