#pragma once
#include "TaxData.hpp"
#include "MapData.hpp"

class StageData {
private:
	TaxData Tax;
	MapData Map;
public:
	StageData() = default;
	StageData();
};
