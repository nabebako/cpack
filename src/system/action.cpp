#include "system/action.hpp"
#include "log/logging.hpp"

#include <fstream>
#include <regex>

namespace fs = std::filesystem;

namespace Cpack::system
{
	int compile(const fs::path &file, const std::string &compiler, const std::vector<fs::path> &headers)
	{
		std::string cmdStr(compiler + " -c " + file.string() + " -o .cpack/bin/" + file.stem().string() + ".o ");

		for (auto dir: headers)
			cmdStr.append("-I " + dir.string() + " ");

		cmdStr.append("2> error/" + file.stem().string() + ".err");

		int status = std::system(cmdStr.c_str());

		if (status == 0)
		{
			logging::log("compile", file.string());
		}
		else
		{
			logging::error("compile", file.string());
		}

		return status;
	}

	int link(const std::vector<fs::path> &files, const std::string &compiler, const fs::path &outdir)
	{
		std::string cmdStr(compiler + " ");

		if (files.size() == 0)
		{
			return 1;
		}

		for (auto file: files)
			cmdStr.append("\"" + file.string() + "\" ");
		
		cmdStr.append("-o " + outdir.string() + " 2> error/link.err");

		int status = std::system(cmdStr.c_str());

		if (status == 0)
		{
			logging::log("link", outdir.string());
		}
		else
		{
			logging::error("link", outdir.string());
		}

		return status;
	}

	std::vector<std::filesystem::path> getDependices(const std::filesystem::path &file)
	{
		std::ifstream rf(file);
		std::string line;
		char buffer[200];

		while (rf.getline(buffer, sizeof(buffer)))
		{
			line = buffer;
			std::regex_match(buffer, std::regex("#include\\s\"(.*)\""));
		}
		
	}
}
