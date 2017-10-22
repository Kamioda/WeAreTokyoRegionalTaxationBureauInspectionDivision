#pragma once
#include <string>

class TaxData {
private:
	TaxData(const std::string TaxName, const std::string TaxEvacuee, const std::string Surcharge, const std::string DelayTax);
	TaxData(const std::string TaxName, const std::string TaxEvacuee, const int Surcharge, const int DelayTax);
public:
	TaxData() = default;
	TaxData(const std::string TaxDataFilePath);
	std::string TaxName;
	std::string TaxEvacuee;
	int Surcharge;
	int DelayTax;
};
