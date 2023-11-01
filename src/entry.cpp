#include "cpack.hpp"

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <functional>

#include <printf.h>

int main(int argc, char const *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);

	Cpack::Options option(args);

	if (option.cmd != Cpack::command::cmdType::none)
		Cpack::logging::command(option.cmd);

	Cpack::system::Filehandler fh(option);

	Cpack::command::mapCmdFunc.at(option.cmd)(fh, option);

	return 0;
}
