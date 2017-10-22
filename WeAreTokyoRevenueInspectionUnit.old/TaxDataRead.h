#pragma once
#include "ApplicationDirectory.h"
#include <string>
#include <vector>

struct CaughtTax {
	CaughtTax(const std::string target_name, const std::string tax_name, const unsigned int payable_tax,
		const unsigned int already_paid, bool intended, const int evidence, const std::string map_path,
		const std::string item_path)
		:target_name(target_name), tax_name(tax_name), payable_tax(payable_tax), already_paid(already_paid),
		intended(intended), evidence(evidence), map_path(map_path), item_path(item_path) {}
	std::string target_name; // ’EÅÒ‚Ì–¼‘O
	std::string tax_name; // Å‹à‚Ì–¼‘O
	std::string who_are_you;
	unsigned int payable_tax, // –{Å‚Ì‡Œv
		already_paid; // x•¥‚¢Ï‚İ
	bool intended; // ˆÓ}‚µ‚½‚à‚Ì‚©
	int evidence; // ’EÅ‚ÌØ‹’‚Ì”
	std::string map_path;
	std::string item_path;
};

std::vector<CaughtTax> read_xml_criminal_investigation_case(ApplicationDirectory directory);
