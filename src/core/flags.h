/**
 * @file flags.h
 * @brief Containes flags mapping command line arguments.
 */

#pragma once

/**
 * @class flags
 * @brief Flags supported by the program for generating projects.
 * Parameters are language, qt, openCV, maven, typeFlag, err.<br>
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
	/// True if an error occured.
	bool err;
	/// Wether to use git as a version control system
	bool useGit;
	/// True if help/h flag specified. In this case all other flags are ignored.
	bool help;

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
	, help(false) { }
};

