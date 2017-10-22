#include "Win32API.hpp"
#include "D:/Users/AinoMegumi/BitBucket/Kamioda Games/CommonSourceCode/Split.hpp"
#include "PropertiesRead.hpp"
#include <fstream>
#include <array>

static inline std::array<std::string, 2> SplitData(const std::string& str, char sep) {
	const std::vector<std::string> Data = SplitA(str, sep);
	if (Data.size() != 2) throw std::runtime_error("サイズが間違っています。");
	return{ Data[0], Data[1] };
}

static inline std::array<std::wstring, 2> SplitData(const std::wstring& str, wchar_t sep) {
	const std::vector<std::wstring> Data = SplitW(str, sep);
	if (Data.size() != 2) throw std::runtime_error("サイズが間違っています。");
	return{ Data[0], Data[1] };
}

PropertiesRead::PropertiesRead(const std::string FilePath, const std::string Encode) {
	if (!FileExists(FilePath)) throw std::ios_base::failure(FilePath + " : file is not exist");
	if (Encode == "UTF-8" || Encode == "UTF-16") {
		std::wifstream ifs(FilePath);
		for (std::wstring str; std::getline(ifs, str);) {
			if (L'#' == str.at(0)) continue;
			const std::array<std::wstring, 2> Temp = SplitData(str, L'=');
			this->List.emplace_back(WStringToString(Temp[0]), WStringToString(Temp[1]));
		}
		ifs.close();
	}
	else {
		std::ifstream ifs(FilePath);
		for (std::string str; std::getline(ifs, str);) {
			if ('#' == str.at(0)) continue;
			const std::array<std::string, 2> Temp = SplitData(str, '=');
			this->List.emplace_back(Temp[0], Temp[1]);
		}
		ifs.close();
	}
}

std::string PropertiesRead::GetData(const std::string Tag) const {
	for (const PropertiesData i : this->List) if (i.Tag == Tag) return i.Data;
	throw std::runtime_error("当該タグとそれに対応するデータがありません。");
}

std::vector<PropertiesData> PropertiesRead::GetData() const {
	return this->List;
}
