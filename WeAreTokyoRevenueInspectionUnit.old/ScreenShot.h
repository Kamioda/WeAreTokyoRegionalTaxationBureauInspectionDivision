#pragma once
#include "ApplicationDirectory.h"
#include "Ini.h"

class ScreenShot {
private:
	int save_extension;
	std::string choose_filename(const std::string extension);
	void jpeg();
	void png();
	void bmp();
public:
	ScreenShot() = default;
	ScreenShot(ApplicationDirectory directory, Ini ini);
	void capture();
};
