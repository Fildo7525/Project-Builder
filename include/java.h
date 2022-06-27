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

#define DEFAULT_PACKAGE_LOCATION "com.example"

