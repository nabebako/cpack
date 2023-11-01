#pragma once

#include <map>
#include <filesystem>
#include <vector>

namespace Cpack::system
{
	class FileTracker
	{
	private:

		std::map<std::filesystem::path, std::chrono::milliseconds> m_filesWT;


	public:

		FileTracker(const std::vector<std::filesystem::path> &files);

		void serialize();
		void readMemo();
	};
} 
