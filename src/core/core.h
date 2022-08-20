#pragma once

#include "colors.h"
#include "flags.h"
#include "Project.h"

#include <iostream>
#include <memory>
#include <string>

#define INITIALIZE_DIR_ERROR "Directory could not be initialized. It already exists."

/**
 * @brief Prints help to the console.
 *
 * @param os Output stream where will be the help printed.
 */
std::ostream &printHelp(std::ostream &os = std::cerr);

/**
 * @brief Prints red error message to the console to std::cerr stream.
 * This funciton adds new line automaicly to the end of the message.
 *
 * @param msg Message to be displaied.
 */
void error(const std::string &msg);

/**
 * @brief Prints arguments to the console.
 *
 * @param argv Args to be printed.
 * @param size Size of the array of arguments.
 */
void printArgumets(const char **argv, const int size);

/**
 * @brief Executes the supplied command. If the command failes the errorMessage will be printed.
 *
 * @param command Command to execute.
 * @param errorMessage Error message to be printed in case of an error.
 */
void executeCommand(const std::string &command, const std::string &errorMessage = "");

/**
 * @brief Get the initialization line of current shell type.
 */
std::string shellInit();

/**
 * @brief Generating flags based on your input options.
 *
 * @param argc Number of commandline arguments.
 * @param argv Commandline arguments.
 * @return Pair of generated flags from commandline optoins and a project name..
 */
std::pair<flags, std::shared_ptr<Project>> deduceFlagOptions(int argc, char **argv);

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

