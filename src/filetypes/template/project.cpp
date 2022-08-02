#include "project.h"

Project::Project(const std::string &dir, const flags &languageFlags)
	: m_dir(dir)
	, m_languageFlags(languageFlags)
{
}

std::string Project::projectName()
{
	return m_dir;
}

