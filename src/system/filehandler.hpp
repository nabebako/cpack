#pragma once

#include "args/options.hpp"

#include <map>
#include <vector>
#include <filesystem>
#include <chrono>

namespace Cpack::system
{
	class Filehandler
	{
	private:

		std::vector<std::filesystem::path> m_startDir;
		std::filesystem::path m_outDir;

		// remove distinction between c and cpp files.
		std::map<std::filesystem::path, std::chrono::milliseconds> m_srcFiles;
		std::vector<std::filesystem::path> m_cFiles;
		std::vector<std::filesystem::path> m_cppFiles;
		std::vector<std::filesystem::path> m_objFiles;
		std::vector<std::filesystem::path> m_headerFiles;

	public:

		Filehandler(const Options &option);

		// Make sure .cpack path exists.
		static const void createCpackDir();

		// Make sure out dir exists
		inline const void createOutDir()
		{
			if (!std::filesystem::exists(m_outDir)) std::filesystem::create_directory(m_outDir);
		}

		inline const void createErrDir()
		{
			if (!std::filesystem::exists("error")) std::filesystem::create_directory("error");
		}

		// Setter for outpath
		inline void setOutDir(const std::string &path)
		{
			m_outDir = std::filesystem::path(path);
		}

		// Setter for startPath
		inline void setStartDir(const std::vector<std::filesystem::path> &paths)
		{
			m_startDir = paths;
		}
		
		// Add startPath
		inline void addStartDir(const std::string &path)
		{
			m_startDir.emplace_back(path);
		}

		const std::vector<std::filesystem::path> cFiles() { return m_cFiles; };
		const std::vector<std::filesystem::path> cppFiles() { return m_cppFiles; };

		// Get obj files to link, computed from m_srcFiles
		const std::vector<std::filesystem::path> objFiles();

		// Get all source files.
		const std::vector<std::filesystem::path> srcFiles();

		// Get only modified source files.
		const std::vector<std::filesystem::path> modsrcFiles();

		const void writeMem();
		void readMem();
	};	
}
