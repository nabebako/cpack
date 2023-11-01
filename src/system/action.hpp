#pragma once

#include "args/options.hpp"
#include "system/filehandler.hpp"

namespace Cpack::system
{
	int compile(const std::filesystem::path &file, const std::string &compiler, const std::vector<std::filesystem::path> &headerPathsStr);
	int link(const std::vector<std::filesystem::path> &files, const std::string &compiler, const std::filesystem::path &outdir);

	std::vector<std::filesystem::path> getDependices(const std::filesystem::path &file);
}
