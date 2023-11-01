#include "args/flags.hpp"
#include "log/logging.hpp"

#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace Cpack::flag
{
	std::map<type, std::vector<std::string>> get(const std::vector<std::string> &args)
	{
		std::map<type, std::vector<std::string>> flags;

		int flagArgsLeft = 0;
		type currentFlag = type::none;

		for (size_t i = 0; i < args.size(); i++)
		{
			auto flag = lookup.find(args[i]);

			// check weather it's a flag
			if (flag != lookup.end())
			{
				if (flagArgsLeft > 0)
				{
					logging::error(("not enough argument for flag " + flag->first).c_str());
					exit(1);
				}

				flagArgsLeft = argsLookup.at(flag->second);
				currentFlag = flag->second;
				flags[flag->second] = {};
			}
			// if a flag has not been found yet
			else if (currentFlag == type::none)
			{
				continue;
			}
			// if not a flag
			else
			{
				if (flagArgsLeft == -1)
				{
					flags[currentFlag].push_back(args[i]);
				}
				else if (flagArgsLeft > 0)
				{
					flags[currentFlag].push_back(args[i]);
					flagArgsLeft--;
				}
				else
				{
					logging::error("too much argument for flag [insert flag name here]");
					exit(1);
				}
			}
		}

		if (flagArgsLeft > 0)
		{
			logging::error("not enough argument for flag [insert flag name here]");
			exit(1);
		}
		
		return flags;
	}

	std::vector<type> getCmdInds(const std::vector<std::string> &args)
	{
		std::vector<type> flagsList;

		for (size_t i = 0; i < args.size(); i++)
		{
			auto flag = lookupCmdInds.find(args[i]);

			if (flag != lookupCmdInds.end())
				flagsList.push_back(flag->second);
		}

		return flagsList;
	}
}