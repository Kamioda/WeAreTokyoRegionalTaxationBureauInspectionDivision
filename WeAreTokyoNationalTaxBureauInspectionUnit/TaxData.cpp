#include "TaxData.hpp"
#include "PropertiesRead.hpp"

TaxData::TaxData(const std::string TaxName, const std::string TaxEvacuee, const std::string Surcharge, const std::string DelayTax)
	: TaxData(TaxName, TaxEvacuee, std::stoi(Surcharge), std::stoi(DelayTax)) {}

TaxData::TaxData(const std::string TaxName, const std::string TaxEvacuee, const int Surcharge, const int DelayTax)
	: TaxName(TaxName), TaxEvacuee(TaxEvacuee), Surcharge(Surcharge), DelayTax(DelayTax) {}

TaxData::TaxData(const std::string TaxDataFilePath) {
	const PropertiesRead Prop(TaxDataFilePath);
	TaxData(Prop.GetData("TaxName"), Prop.GetData("TaxEvacuee"), Prop.GetData("Surcharge"), Prop.GetData("Delay"));
}
