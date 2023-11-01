#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <filesystem>
#include <functional>

namespace Cpack::system
{
	class Filehandler;
}

namespace Cpack
{
	class Options;
}

namespace Cpack::command
{
	enum class cmdType
	{
		none, init, compile, link, build, test, watch, run
	};

	const std::map<std::string, cmdType> commandLookup
	{
		{"init", 		cmdType::init},
		{"i", 			cmdType::init},
		{"compile", 	cmdType::compile},
		{"cmp", 		cmdType::compile},
		{"link", 		cmdType::link},
		{"build", 		cmdType::build},
		{"b", 			cmdType::build},
		{"test", 		cmdType::test},
		{"watch", 		cmdType::watch},
		{"w", 			cmdType::watch},
		{"run", 		cmdType::run},
	};

	const std::map<cmdType, std::string> cmdStr
	{
		{cmdType::init,		"init"},
		{cmdType::compile,	"compile"},
		{cmdType::link,		"link"},
		{cmdType::build,	"build"},
		{cmdType::test,		"test"},
		{cmdType::watch,	"watch"},
		{cmdType::run,		"run"},
	};

	struct cmdInfo
	{
		cmdType cmd;
		std::vector<std::string> args;
		int startI;
		int endI;
	};
	

	// returns the command type and index of args.
	cmdInfo get(const std::vector<std::string> &args);


	// cmd to run
	int compile(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int link(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int build(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int test(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int watch(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int run(Cpack::system::Filehandler &files, const Cpack::Options &config);

	int init(Cpack::system::Filehandler &files, const Cpack::Options &config);

	const std::map<cmdType, std::function<int(Cpack::system::Filehandler &, const Cpack::Options &)>> mapCmdFunc
	{
		{cmdType::compile,		compile},
		{cmdType::link,			link},
		{cmdType::build, 		build},
		{cmdType::test, 		test},
		{cmdType::watch, 		watch},
		{cmdType::run, 			run},
		{cmdType::init, 		init},
	};
}