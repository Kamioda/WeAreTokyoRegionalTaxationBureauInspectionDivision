#ifndef __PROPERTIESREAD_HPP__
#define __PROPERTIESREAD_HPP__
#include "PropertiesData.hpp"
#include <vector>

class PropertiesRead {
private:
	std::vector<PropertiesData> List;
public:
	PropertiesRead(const std::string FilePath, const std::string Encode = "Shift-JIS");
	// 指定されたタグのデータを取得します。
	// データが存在しない場合、例外がスローされます。
	std::string GetData(const std::string Tag) const;
	// 保存されているタグとデータの組みを返します。
	std::vector<PropertiesData> GetData() const;
};
#endif
