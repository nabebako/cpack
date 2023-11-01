#pragma once

#include "args/command.hpp"
#include "args/flags.hpp"

#include <vector>
#include <string>
#include <filesystem>

namespace Cpack
{	
	class Options
	{
	public:

		Cpack::command::cmdType cmd = Cpack::command::cmdType::none;
		std::vector<std::filesystem::path> cmdArgs = {};

		// Should not be specify in config.
		bool help = false;

		std::vector<std::filesystem::path> ignoreFiles = {};
		std::vector<std::filesystem::path> startDir = {};
		std::filesystem::path output = "dist/app";
		std::string compiler = "g++";

		Options(std::vector<std::string> args);
	};
}