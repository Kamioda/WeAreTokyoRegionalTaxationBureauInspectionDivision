#include"DxLib.h"
#include<string>

void start_criminal_investigation(const int x, const int y, const unsigned int color, const std::string& tax_name) {
	DrawString(x, y, "東京国税局査察部です。", color);
	DrawFormatString(x, y, color, "%s法違反の嫌疑で、ただいまから強制調査を行います。", tax_name.c_str());
}