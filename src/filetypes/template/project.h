#pragma once

#include "flags.h"

#include <string>

class Project
{
public:
	Project(const std::string &dir, const flags &languageFlags);
	virtual ~Project() = default;

	virtual void generate() = 0;

	virtual std::string projectName();

protected:
	std::string m_dir;
	flags m_languageFlags;
};

