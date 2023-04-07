/**
 * @file
 * @brief Template for creating Filetype projects.
 */

#pragma once

#include "flags.h"

/**
 * @class Project
 * @brief Virtual class supporting creation of a project.
 */
class Project
{
public:
	/**
	 * @brief Constructor
	 */
	Project(const std::string &dir, const flags &languageFlags);

	/**
	 * @brief Destructor
	 */
	virtual ~Project() = default;

	/**
	 * @brief Pure virtual funciotn that generates the project.
	 * Must be implemented in all child classes. And should create everything for the project.
	 */
	virtual void generate() = 0;

	/**
	 * @brief Project name supported as a command line argument.
	 */
	virtual std::string projectName();

	/**
	 * @brief Initialize git repository with initial commit.
	 */
	void initializeGit();

protected:
	/// Directory from command line.
	std::string m_dir;

	/// Flags generated from command line arguments.
	flags m_languageFlags;
};

