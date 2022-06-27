#pragma once

#include "flags.h"
#include "colors.h"

#include <string>

/**
 * @brief Prints arguments to the console.
 *
 * @param argv Args to be printed.
 * @param size Size of the array of arguments.
 */
void printArgumets(char **argv, int size);

/**
 * @brief Get actual type of your shell.
 */
std::string shellInit();

/**
 * @brief Generating flags based on your input options.
 *
 * @param argc Number of commandline arguments.
 * @param argv Commandline arguments.
 * @return Generated flags.
 */
flags deduceFlagOptions(int argc, char **argv);

/**
 * @class indent
 * @brief Class represents the indentation of the code.
 */
class indent
{
public:
	/**
	 * @brief Returns the indentation.
	 */
	std::string operator() ();

	/**
	 * @brief Increases the indentation.
	 */
	indent &up();

	/**
	 * @brief Decreases the indentation
	 */
	indent &down();

private:
	/// Indentation string.
	std::string m_indentation;
};
