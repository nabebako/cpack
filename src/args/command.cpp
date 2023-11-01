#include "args/command.hpp"
#include "args/flags.hpp"
#include "args/options.hpp"
#include "log/logging.hpp"
#include "system/action.hpp"
#include "system/filehandler.hpp"
#include "system/filetracker.hpp"

#include <thread>

namespace fs = std::filesystem;

namespace Cpack::command
{
	cmdInfo get(const std::vector<std::string> &args)
	{
		cmdType cmd = cmdType::none;
		std::vector<std::string> cmdArgs;
		int start = -1;
		int end = -1;

		for (size_t i = 0; i < args.size(); i++)
		{
			// if command has been found
			if (cmd != cmdType::none)
			{
				auto f = flag::lookup.find(args[i]);

				// checks if a flag
				if (f != flag::lookup.end())
				{
					end = i + 1;
					break;
				}
				
				cmdArgs.push_back(args[i]);
			}
			else
			{
				auto comd = commandLookup.find(args[i]);

				// checks if command
				if (comd != commandLookup.end())
				{
					cmd	= comd->second;
					start = i;
					end = i + 1;
				}
			}
		}

		return {cmd, cmdArgs, start, end};
	}
	
	int compile(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		std::string headerPaths;
		int status = 0;

		for (auto &file: files.srcFiles())
			status += Cpack::system::compile(file, config.compiler, config.startDir);

		return status;
	}

	int link(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		return Cpack::system::link(files.objFiles(), config.compiler, config.output);
	}

	int build(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		std::string headerPaths;
		int status = compile(files, config);

		// if no error during compile stage then link
		if (status == 0)
			return link(files, config);

		return status;
	}

	int test(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		// idk how to impliment test
		return 1;
	}

	int watch(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		int status = build(files, config);

		// change later
		const int ms = 500;

		while (1)
		{
			// sleep so that it won't run all the time.
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));

			// std::filesystem::file_time_type;

			// watch for file change then recompile and rebuild.
			// check if the file exist before getting last write time.
			for (auto &file: files.cppFiles())
			{
				auto lwt = std::filesystem::last_write_time(file);
				// serialize file_time_type to .mem file.
				lwt.time_since_epoch();

			}	
		}
		return 1;
	}

	int run(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		// 1. build
		// 2. run
	}

	int init(Cpack::system::Filehandler &files, const Cpack::Options &config)
	{
		// init project structure
	}
}