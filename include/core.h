#pragma once

#include "flags.h"
#include "colors.h"

#include <iostream>
#include <string>

/**
 * @brief Prints help to the console.
 *
 * @param os Output stream where will be the help printed.
 */
std::ostream &printHelp(std::ostream &os = std::cerr);

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
 * @return Pair of generated flags from commandline optoins and a project name..
 */
std::pair<flags, std::string> deduceFlagOptions(int argc, char **argv);

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

