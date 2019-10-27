#ifndef _FILE_MANAGER_
#define _FILE_MANAGER_

#include <mutex>

class FileManager
{
public:

	/// create new file with content, if fails return false
	bool prepareFile(std::string p_path, std::string p_content);
	void showAvailableFiles();

private:
	std::mutex m_mutex;
	std::vector<std::string> m_availableFiles;
};

#endif // _FILE_MANAGER_