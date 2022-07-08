#pragma once

#include "flags.h"

#include <string>

/**
 * @brief Function that creates java project.
 *
 * @param dir Directory where will the project be created.
 * @param maven Wheather the project should use maven or not.
 */
void makeJavaProject(const std::string &dir, const flags &languageFlags);

/**
 * @brief Retrieve unix relative path from java package style.
 *
 * @param packagePath Java package style (e.g.: com.example -> com/example).
 */
std::string pathFromJavaPackagePath(const std::string &packagePath);

/**
 * @brief Returns pair of [Linux type path, java package path]
 */
std::pair<std::string, std::string> linuxAndJavaPaths();

/**
 * @brief Generates Main.java in specified direcotry.
 *
 * @param dir Directory where the Main.java be created.
 * @param slashedPackedLocation Linux path location.
 * @param packageLocation Java path location.
 */
void generateMainFile(const std::string &dir, const std::string &slashedPackedLocation, const std::string &packageLocation);

/**
 * @brief Generates pom.xml if maven build system is specified.
 *
 * @param dir directory where it will be created.
 * @param packageLocation Java packae path.
 */
void generatePomXML(const std::string &dir, const std::string &packageLocation);

/**
 * @brief Generates build.sh and compile.sh.
 *
 * @param dir Pathe for compilation.
 * @param slashedPackedLocation Linux relative path for compilation.
 * @param packageLocation Java package style path for compilation.
 * @param maven Bool indicating build type.
 */
void generateBuildFiles(const std::string &dir, const std::string &slashedPackedLocation, const std::string &packageLocation, bool maven);

#define DEFAULT_PACKAGE_LOCATION "com.example"

