#include "system/filehandler.hpp"
#include "log/logging.hpp"
#include "helper.hpp"

#include <regex>
#include <string.h>
#include <fstream>

namespace fs = std::filesystem;

typedef std::vector<std::filesystem::path> dirs;

namespace Cpack::system
{
	Filehandler::Filehandler(const Options &option):
		m_startDir(option.startDir), m_outDir(option.output), m_cFiles({}), m_cppFiles({})
	{
		if (option.cmdArgs.size() == 0)
		{
			for (auto &startDir: m_startDir)
			{
				if (!fs::exists(startDir))
				{
					bool shouldIgnore = false;

					for (const auto &file: fs::recursive_directory_iterator(startDir))
					{
						shouldIgnore = false;

						for (auto &exclude: option.ignoreFiles)
							if (exclude == file.path())
								shouldIgnore = true;

						if (!shouldIgnore && file.path().extension().string() == ".cpp")
							m_srcFiles[file] = std::chrono::duration_cast<std::chrono::milliseconds>(fs::last_write_time(file).time_since_epoch());
					}
				}
				else
				{
					Cpack::logging::error("args","no such file or directory " + startDir.string());
					exit(1);
				}
			}
		}
		else
		{
			for (auto &file: option.cmdArgs)
			{
				if (fs::exists(file) && file.extension().string() == ".cpp")
				{
					m_srcFiles[file] = std::chrono::duration_cast<std::chrono::milliseconds>(fs::last_write_time(file).time_since_epoch());
				}
				else
				{
					Cpack::logging::error("args", "no such file " + file.string());
				}
			}
		}

		this->writeMem();
	}

	const void Filehandler::createCpackDir()
	{
		if (!fs::exists(ROOT)) 				fs::create_directory(ROOT);
		if (!fs::exists(COMPILED)) 			fs::create_directory(COMPILED);
		if (!fs::exists(HEADERS)) 			fs::create_directory(HEADERS);
		if (!fs::exists(ASSETS)) 			fs::create_directory(ASSETS);
		if (!fs::exists(VENDORS)) 			fs::create_directory(VENDORS);
		if (!fs::exists(MODULES)) 			fs::create_directory(MODULES);
		if (!fs::exists(CACHE)) 			fs::create_directory(CACHE);
	}

	const std::vector<std::filesystem::path> Filehandler::objFiles()
	{
		std::vector<std::filesystem::path> files;

		for (auto [file, wt]: m_srcFiles)
			files.push_back(".cpack/bin" / file.parent_path() / (file.filename().string() + ".o"));

		return files;
	}

	const std::vector<std::filesystem::path> Filehandler::srcFiles()
	{
		std::vector<std::filesystem::path> files;

		for (auto [file, wt]: m_srcFiles)
			files.push_back(file);
		
		return files;
	}

	const std::vector<std::filesystem::path> Filehandler::modsrcFiles()
	{
		std::vector<std::filesystem::path> files;

		for (auto [file, wt]: m_srcFiles)
			// might need to convert nanoseconds to miliseconds 
			if (fs::exists(file) && fs::last_write_time(file).time_since_epoch() != wt)
				files.push_back(file);
				
		return files;
	}

	const void Filehandler::writeMem()
	{
		std::ofstream memFile(".cpack/.mem");

		for (auto [file, wt]: m_srcFiles)
			memFile << file.string() << ":" << wt.count() << "\n";

		memFile.close();
	}

	void Filehandler::readMem()
	{
		if (fs::exists(".cpack/.mem"))
		{
			std::ifstream memFile(".cpack/.mem");
			std::string content;
			char buffer[100];

			while (memFile.getline(buffer, sizeof(buffer)))
			{
				content = buffer;
				m_srcFiles[fs::path(content.substr(0, content.find(':')))] = std::chrono::milliseconds(std::stoi(content.substr(content.find(':') + 1)));
			}

			memFile.close();
		}
	}
}