#pragma once
#include<string>
class Ini {
public:
	Ini(const std::string& filepath_or_name);
	bool is_now_created() const;
	void edit(std::string const& section, std::string const& key, std::string const& str);
	int getnum(std::string const& section, std::string const& key, const int default_num);
	std::string getString(std::string const& section, std::string const& key, std::string const& default_str);
private:
	void create_UTF16_file();
	std::string filefullpath;
	bool was_no_exist;
};
