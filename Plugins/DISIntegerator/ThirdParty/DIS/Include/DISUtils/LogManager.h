#pragma once
#include <fstream>
#include <mutex>
#include <string>
class CLogManager
{
public:
	static CLogManager& getInstance();
	void log(std::string category, std::string message);
	void ReleaseLogManager();
private:
	CLogManager();
	~CLogManager();
	CLogManager(const CLogManager&) = delete;
	CLogManager& operator=(const CLogManager&) = delete;

	std::ofstream logFile;
	std::mutex logMutex;

	std::string getCurrentTime();
};

