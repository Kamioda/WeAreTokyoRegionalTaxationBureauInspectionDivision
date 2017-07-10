#pragma once
#include "ApplicationDirectory.hpp"
#include <vector>

struct StageData {
	StageData(const std::string& TaxName, const int SurchageTaxAmount, const int DelayTax, const std::string& AdditionalTaxName, const int AdditionalTaxAmount)
		: TaxName(TaxName), SurchageTaxAmount(SurchageTaxAmount), DelayTax(DelayTax), 
		AdditionalTaxName(AdditionalTaxName), AdditionalTaxAmount(AdditionalTaxAmount) {}
	std::string TaxName;
	int SurchageTaxAmount;
	int DelayTax;
	std::string AdditionalTaxName;
	int AdditionalTaxAmount;
};

class ReadStageData {
private:
	std::vector<StageData> StageInfo;
public:
	ReadStageData(const std::string& StageInfoListFilePath, const ApplicationDirectory& App);
};
