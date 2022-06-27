#pragma once

#include <string>
struct flags;

/**
 * @brief Function for creating cpp project.
 *
 * @param dir Direcotry where will the project be created.
 * @param languageFlags Flags for different optins in the project.
 */
void makeCppProject(const std::string &dir, const flags &languageFlags);

