/**
 * @file flags.h
 * @brief Contains flags mapping command line arguments.
 */

#pragma once

#include <cstdlib>
#include <string>

#define COMPLETION_LIST "--type -t -a --aoc --qt5 -q --rpi --maven -m --opencv -c --no-git -g --help -h --list-completion --list-languages"
#define LANGUAGES_LIST "cpp java python"
#define HELPER_DIR std::string(std::getenv("HOME")) + "/.local/share/projectBuilder/helpers"
#define HELP_FILE HELPER_DIR"/helptext.help"

/**
 * @class flags
 * @brief Flags supported by the program for generating projects.
 * Parameters are language, qt, openCV, maven, typeFlag, err.
 */
struct flags
{
	enum class language
	{
		java,
		cpp,
		python,
		none,
	};

	/**
	 * @brief language is enum class of programming language 'java', 'cpp', 'python' or none (default)
	 */
	language lang;

	// C++ Flags
	/// Dedicated C++ flag: True if you want to define cpp project and link it with Qt5.
	bool qt;
	/// Dedicated C++ flag: True if you want to define cpp project and link it with OpenCV.
	bool openCV;
	/// Dedicated C++ flag: True if you want to define cpp project and link it with WiringPi.
	bool rasPi;

	// Java flags
	/// Dedicated C++ flag: Wether you want to use maven build system or not.
	bool maven;

	// GENERAL FLAGS
	/// True if an error occurred.
	bool err;
	/// Wether to use git as a version control system
	bool useGit;
	/// True if help/h flag specified. In this case all other flags are ignored.
	bool help;
	/// Advent of code.
	bool aoc;

	/**
	 * @brief Constructor
	 */
	flags()
		: lang(language::none)
		, qt(false)
		, openCV(false)
		, rasPi(false)
		, maven(false)
		, err(false)
		, useGit(true)
		, help(false)
		, aoc(false) { }
};

