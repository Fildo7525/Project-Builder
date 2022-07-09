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
		none,
	};

	language lang;

	// Cpp flags
	bool qt;
	bool openCV;

	// Java flags
	bool maven;

	// True if an error occured.
	bool err;

	// True if help/h flag specified. In this case all other flags are ignored.
	bool help;

	/**
	 * @brief Constructor
	 */
	flags()
	: lang(language::none)
	, qt(false)
	, openCV(false)
	, maven(false)
	, err(false)
	, help(false) { }
};

