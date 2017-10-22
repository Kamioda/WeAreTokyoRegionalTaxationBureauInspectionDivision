#pragma once
#include <string>

class ApplicationDirectory {
private:
	void change_current_directory();
	void update_current_directory();
#ifdef UNICODE
	std::wstring default_directory;
	std::wstring current_directory;
#else
	std::string default_directory;
	std::string current_directory;
#endif
public:
	ApplicationDirectory();
	void restore_current_directory(bool change_application_work_directory);
	bool current_directory_is_default_directory();
#ifdef UNICODE
	ApplicationDirectory(const std::wstring default_directory);
	void change_current_directory(const std::wstring after_changed_directory, bool change_application_work_directory = true);
	std::wstring get_default_directory();
	std::wstring get_current_directory();
	std::wstring change_full_path(std::wstring filepath, bool use_default_directory = false);
#else
	ApplicationDirectory(const std::string default_directory);
	void change_current_directory(const std::string after_changed_directory, bool change_application_work_directory = true);
	std::string get_default_directory();
	std::string get_current_directory();
	std::string change_full_path(std::string filepath, bool use_default_directory = false);
#endif
};
