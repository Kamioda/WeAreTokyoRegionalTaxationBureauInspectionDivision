#ifndef __PROPERTIESDATA_HPP__
#define __PROPERTIESDATA_HPP__
#include <string>

class PropertiesData {
public:
	PropertiesData() = default;
	PropertiesData(const std::string Tag, const std::string Data) : Tag(Tag), Data(Data) {}
	std::string Tag, Data;
};
#endif
