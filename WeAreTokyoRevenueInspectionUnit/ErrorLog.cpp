#include "ApplicationDirectory.hpp"
#include "EnvironmentVariable.hpp"
#include <fstream>
#include <chrono>

static inline void AddErrorLog(const char* ErrorLog, const std::string FilePath) {
	std::ofstream ofs(FilePath + "watriuex.log", std::ios::out | std::ios::app);
	ofs << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << " : " << ErrorLog << std::endl;
	ofs.close();
}

void AddErrorLog(const char* ErrorMessage, const ApplicationDirectory& App) {
	const std::string LogPath = App.GetDefaultDirectory() + "\\";
}

void AddErrorLog(const char* ErrorMessage) {
	const std::string LogPath = EnvironmentVariableA("ProgramData").Get() + "\\Kamioda Games\\Kamioda puzzle\\WeAreTokyoRevenueInspectionUnit\\";
}
