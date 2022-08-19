#pragma once

/**
 * @class flags
 * @brief Flags supported by the program for generating projects.
 * Parameters are language, qt, openCV, maven, typeFlag, err.
 * @p language is struct of programming language 'java' and 'cpp'
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

	language lang;

	// Cpp flags
	bool qt;
	bool openCV;
	bool rasPi;

	// Java flags
	bool maven;

	// True if an error occured.
	bool err;

	// Wether to use git as a version control system.
	bool useGit;

	// True if help/h flag specified. In this case all other flags are ignored.
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

