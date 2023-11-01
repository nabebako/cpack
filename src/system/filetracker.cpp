#include "system/filetracker.hpp"
#include "log/logging.hpp"

#include <fstream>

namespace fs = std::filesystem;

namespace Cpack::system
{
	FileTracker::FileTracker(const std::vector<std::filesystem::path> &files):
	m_filesWT({})
	{
		for (auto &file: files)
		{
			if (fs::exists(file))
			{
				m_filesWT[file] = std::chrono::duration_cast<std::chrono::milliseconds>(fs::last_write_time(file).time_since_epoch());
			}
			else
			{
				Cpack::logging::error("no such file " + file.string());
			}
		}
	}

	void FileTracker::serialize()
	{
		std::ofstream memFile(".cpack/.mem");

		for (auto &[file, wt]: m_filesWT)
			memFile << file << ":" << wt.count() << "\n";

		memFile.close();
	}

	void FileTracker::readMemo()
	{
		if (fs::exists(".cpack/.mem"))
		{
			std::ifstream memFile(".cpack/.mem");
			std::string content;
			char buffer[100];

			while(memFile.getline(buffer, sizeof(buffer)))
			{
				content = buffer;
				m_filesWT[fs::path(content.substr(0, content.find(':')))] = std::chrono::milliseconds(std::stoi(content.substr(content.find(':') + 1)));
			}

			memFile.close();
		}
	}
}