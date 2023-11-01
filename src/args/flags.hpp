#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

namespace Cpack::flag
{
	enum class type
	{
		none, ignore, compiler, startDir, output, help, dumpError
	};

	const std::map<std::string, type> lookup
	{
		{"-h", 				type::help},
		{"--help", 			type::help},
		{"-i", 				type::ignore},
		{"--ignore", 		type::ignore},
		{"-c", 				type::compiler},
		{"--compiler", 		type::compiler},
		{"-s", 				type::startDir},
		{"--start-dir",		type::startDir},
		{"-o",				type::output},
		{"--output",		type::output},
		{"--dump-error",	type::dumpError}
	};
	const std::map<std::string, type> lookupCmdInds
	{
		{"-h", 				type::help},
		{"--help", 			type::help},
	};
	
	const std::map<type, int> argsLookup
	{
		{type::none, 	 	 0},
		{type::help, 	 	 0},
		{type::dumpError, 	 0},
		{type::compiler, 	 1},
		{type::output,		 1},
		{type::ignore,		-1},
		{type::startDir,	-1},
	};

	std::map<type, std::vector<std::string>> get(const std::vector<std::string> &args);

	std::vector<type> getCmdInds(const std::vector<std::string> &args);
}