#include "SystemInfo.h"
#include "ScreenShot.h"
#include "DxLib.h"
#include <chrono>
constexpr int shot_jpeg = 0;
constexpr int shot_png = 1;
constexpr int shot_bmp = 2;

ScreenShot::ScreenShot(ApplicationDirectory directory, Ini ini) {
	this->save_extension = ini.getnum("other", "shot", 0);
}

std::string ScreenShot::choose_filename(const std::string extension) {
	return std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + extension;
}

void ScreenShot::jpeg() {
	SaveDrawScreenToJPEG(0, 0, window_width, window_height, choose_filename(".jpg").c_str(), 100);
}

void ScreenShot::png() {
	SaveDrawScreenToPNG(0, 0, window_width, window_height, choose_filename(".png").c_str(), 0);
}

void ScreenShot::bmp() {
	SaveDrawScreenToBMP(0, 0, window_width, window_height, choose_filename(".bmp").c_str());
}

void ScreenShot::capture() {
	switch (this->save_extension) {
		case shot_jpeg:
			return this->jpeg();
		case shot_png:
			return this->png();
		case shot_bmp:
			return this->bmp();
		default:
			return;
	}
}
