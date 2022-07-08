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
	};

	language lang;

	// Cpp flags
	bool qt;
	bool openCV;

	// Java flags
	bool maven;

	// Indicates if a language is set.
	bool typeFlag;
	// True if an error occured.
	bool err;

	/**
	 * @brief Constructor
	 */
	flags()
	: lang()
	, qt(false)
	, openCV(false)
	, maven(false)
	, typeFlag(false)
	, err(false) { }
};

