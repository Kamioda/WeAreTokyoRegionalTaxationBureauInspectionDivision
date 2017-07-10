#include "Convert.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include <codecvt>
#include <stdexcept>

static std::string get_text_from_node(boost::property_tree::ptree& p, const std::string& path) {
	boost::optional<std::string> target_node = p.get_optional<std::string>(path);
	if (!target_node) throw std::runtime_error("xmlÇÃ\"" + path + "\"nodeÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ");
	static_assert(sizeof(wchar_t) == 2, "In function 'read_xml' : Please check usage of 'std::codecvt_utf8_utf16'");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	auto str = convert.from_bytes(target_node.get());
	return WStringToString(str);
}

static int get_int_data_from_node(boost::property_tree::ptree& p, const std::string& path) {
	boost::optional<int> target_node = p.get_optional<int>(path);
	if (!target_node) throw std::runtime_error("xmlÇÃ\"" + path + "\"nodeÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ");
	return target_node.get();
}

static unsigned int get_uint_data_from_node(boost::property_tree::ptree& p, const std::string& path) {
	boost::optional<unsigned int> target_node = p.get_optional<unsigned int>(path);
	if (!target_node) throw std::runtime_error("xmlÇÃ\"" + path + "\"nodeÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ");
	return target_node.get();
}

#include "TaxDataRead.h"

std::vector<CaughtTax> read_xml_criminal_investigation_case(ApplicationDirectory directory) {
	std::vector<CaughtTax> arr;
	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml(directory.change_full_path(".\\Tax\\CriminalInvestigationCase.xml"), pt);
	for (std::pair<std::string, boost::property_tree::ptree> i : pt.get_child("casedatabook")) {
		arr.emplace_back(
			CaughtTax(
				get_text_from_node(i.second, "targetname"),
				get_text_from_node(i.second, "taxname"),
				get_uint_data_from_node(i.second, "payable"),
				get_uint_data_from_node(i.second, "alreadypaid"),
				1 == get_int_data_from_node(i.second, "intended"),
				get_int_data_from_node(i.second, "evidence"),
				get_text_from_node(i.second, "map"),
				get_text_from_node(i.second, "item")
			)
		);
	}
	return arr;
}
