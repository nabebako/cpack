#include "args/options.hpp"
#include "log/logging.hpp"

#include <algorithm>

#include <iostream>
#include <regex>

namespace Cpack
{
	Options::Options(std::vector<std::string> args)
	{
		auto cmdInfo = command::get(args);
		cmd = cmdInfo.cmd;

		for (auto &arg: cmdInfo.args)
			cmdArgs.emplace_back(arg);

		auto cmdIndsFlags = flag::getCmdInds(args);

		if (cmd == command::cmdType::none && cmdIndsFlags.size() == 0)
		{
			logging::defaultMessage();
			exit(0);
		}

		auto flags = flag::get(args);

		for (auto &[flag, flagArgs]: flags)
		{
			switch (flag)
			{
			case flag::type::ignore:

				for (auto &files: flagArgs)
					ignoreFiles.emplace_back(files);
				
				break;

			case flag::type::compiler:
			
				compiler = flagArgs[0];
				break;

			case flag::type::startDir:

				for (auto &dir: flagArgs)
					startDir.emplace_back(dir);

				break;

			case flag::type::output:

				output = flagArgs[0];
				break;

			case flag::type::help:

				help = true;
				break;
			
			default:
				break;
			}
		}

		if (startDir.size() > 1)
			startDir.erase(startDir.begin(), startDir.begin() + 1);
	}
}