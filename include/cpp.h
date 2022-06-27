#pragma once

#include <string>
struct flags;

/**
 * @brief Function for creating cpp project.
 *
 * @param dir Direcotry where will the project be created.
 * @param languageFlags Flags for different options in the project.
 */
void makeCppProject(const std::string &dir, const flags &languageFlags);

/**
 * @brief Returns the cmake version in type of 3.16.3.
 */
std::string cmakeVersion();

/**
 * @brief Generates file main.cpp in the Direcotry dir with specified language options.
 *
 * @param dir Direcotry where to create the main.cpp file.
 * @param languageFlags Options for the main file creation.
 */
void generateMainFile(const std::string &dir, const flags &languageFlags);

/**
 * @brief Create '${dir}.cpp' and '${dir}.h' files.
 *
 * @param dir Location and name of the created files.
 */
void generateDirectoryNamedFiles(const std::string &dir);

/**
 * @brief Create CMakeLists.txt file according to specified options.
 *
 * @param dir Direcotry where to create the file.
 * @param languageFlags Options for the file creation.
 */
void generateCmakeFile(const std::string &dir, const flags &languageFlags);

/**
 * @brief Create build.sh and compile.sh files.
 *
 * @param dir Direcotry where to create the specified files.
 */
void generateBuildFiles(const std::string &dir);

