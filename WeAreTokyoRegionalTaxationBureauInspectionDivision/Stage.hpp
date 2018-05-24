#pragma once
#include "Tax.hpp"
#include "KgDxGraphic.hpp"

struct StageFileInfo {
	std::basic_string<TCHAR> Title;
	std::basic_string<TCHAR> Author;
	std::basic_string<TCHAR> TaxName;
	Tax Surcharge;
	Tax DelayTax;
	int StageWidth;
	int StageHeight;
	int MapChipWidth;
	int MapChipHeight;
};

class Stage {
private:
	std::string Title;
	std::vector<std::vector<KgDxGraphic::NoExcept::Picture>> Graphics;
	int Width, Height;
};
