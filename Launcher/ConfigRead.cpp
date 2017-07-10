#include "ApplicationDirectory.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <Windows.h>
#include <codecvt>
#include <stdexcept>
#include <utility>

std::string WStringToString(std::wstring oWString) {
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, (char *)NULL, 0, NULL, NULL);
	char* cpMultiByte = new char[iBufferSize];
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	delete[] cpMultiByte;
	return oRet;
}

#define wide_to_multi_str WStringToString

static std::string get_text_from_json(boost::property_tree::ptree& p, const std::string& tag) {
	auto target = p.get_optional<std::string>(tag);
	if (!target) throw std::runtime_error("json reading failed");
	static_assert(sizeof(wchar_t) == 2, "In function 'read json data' : Please check usage of 'std::codecvt_utf8_utf16'");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	auto str = convert.from_bytes(target.get());
	return wide_to_multi_str(str);
}

static int get_int_from_json(boost::property_tree::ptree& p, const std::string& tag) {
	auto target = p.get_optional<int>(tag);
	if (!target) throw std::runtime_error("json reading failed");
	return target.get();
}

std::string get_text_from_config_file(const std::string tag) {
	boost::property_tree::ptree pt;
	boost::property_tree::json_parser::read_json(directory.change_full_path(".\\config\\config.lcr"), pt);
	return get_text_from_json(pt.get_child("config"), tag);
}

int get_int_from_config_file(const std::string tag) {
	boost::property_tree::ptree pt;
	boost::property_tree::json_parser::read_json(directory.change_full_path(".\\config\\config.lcr"), pt);
	return get_int_from_json(pt.get_child("config"), tag);
}
