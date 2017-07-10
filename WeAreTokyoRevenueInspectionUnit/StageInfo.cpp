#include "StageInfo.h"
#include "EnvironmentVariable.hpp"
#include "PropertiesRead.hpp"
#include "ErrorLog.h"
#include <fstream>

namespace StageFileTag {
	constexpr const char* TaxName = "tax";
	constexpr const char* SurchargeTaxAmount = "surcharge";
	constexpr const char* DelayTax = "delay";
	constexpr const char* AdditionalTaxName = "naddtax";
	constexpr const char* AdditionalTaxAmount = "aaddtax";
}

ReadStageData::ReadStageData(const std::string& StageInfoListFilePath, const ApplicationDirectory& App) {
	std::vector<std::string> FilePathList;
	std::ifstream ifs(App.ChangeFullPath(StageInfoListFilePath, true));
#ifdef RIDAISAI
	const std::string StageInstallPath = App.GetDefaultDirectory() + "\\Stage\\";
#else
	const std::string StageInstallPath = EnvironmentVariableA("ProgramData").Get() + "\\Kamioda Games\\Kamioda puzzle\\WeAreTokyoRevenueInspectionUnit\\";
#endif
	for (std::string s; std::getline(ifs, s); FilePathList.emplace_back(':' == s.at(1) ? s : StageInstallPath + s)) {}
	ifs.close();
	// ファイル拡張子は.triustageだけど実態は.propertiesファイル
	for (auto& i : FilePathList) {
		try {
			PropertiesRead prop(i);
			this->StageInfo.emplace_back(
				prop.GetData(StageFileTag::TaxName),
				prop.GetData(StageFileTag::SurchargeTaxAmount),
				prop.GetData(StageFileTag::DelayTax),
				prop.GetData(StageFileTag::AdditionalTaxName),
				prop.GetData(StageFileTag::AdditionalTaxAmount)
			);
		}
		catch (const std::exception &er) {
			AddErrorLog(er.what(), App);
		}
	}
}
 