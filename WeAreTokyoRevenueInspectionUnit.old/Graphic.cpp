#include "Graphic.h"
#include "DxLib.h"
#include <stdarg.h>

Color::Color(const int red, const int green, const int blue) {
	this->color_handle = GetColor(red, green, blue);
}

Color::Color(const std::string& code) {
	if (code.size() != 7 || '#' != code.at(0)) throw std::runtime_error("色コードが不正です。");
	auto change_str_to_num = [code](const size_t start) {
		return std::stoi(std::string(code.begin() + start, code.begin() + start + 1), nullptr, 16);
	};
	this->color_handle = GetColor(change_str_to_num(1), change_str_to_num(3), change_str_to_num(5));
}

String::String(const std::string& font_name, const int size, const int thick, const int font_type) {
	this->handle = CreateFontToHandle(font_name.c_str(), size, thick, font_type);
	if (this->handle == -1) throw std::runtime_error("failed create font handle");
}

String::~String() {
	DeleteFontToHandle(this->handle);
}

void String::print(const int x, const int y, const Color string_color, const std::string & str) {
	DrawStringToHandle(x, y, str.c_str(), string_color.color_handle, this->handle);
}

void String::format_print(const int x, const int y, const Color string_color, const TCHAR * str, ...) {
	va_list list;
	va_start(list, str);
	DrawFormatStringToHandle(x, y, string_color.color_handle, this->handle, str, list);
	va_end(list, str);
	delete list;
}

void String::print_nohandle(const int x, const int y, const Color string_color, const std::string& str) {
	DrawString(x, y, str.c_str(), string_color.color_handle);
}

void String::format_print_nohandle(const int x, const int y, const Color string_color, const TCHAR* str, ...) {
	va_list list;
	va_start(list, str);
	DrawFormatString(x, y, string_color.color_handle, str, list);
	va_end(list, str);
	delete list;
}

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

Picture::Picture(const std::string& filepath) {
	if (FALSE == PathFileExistsA(filepath.c_str())) throw std::runtime_error("グラフィックが存在しません。");
	this->GHandle = LoadGraph(filepath.c_str());
}

Picture::Picture(const int GHandle) : GHandle(GHandle) {}

Picture::~Picture() {
	DeleteGraph(this->GHandle);
}

Picture& Picture::operator = (const std::string& filepath) {
	return Picture(filepath);
}

Picture& Picture::operator = (const int GHandle) {
	this->GHandle = GHandle;
	return *this;
}

void Picture::print(const int x, const int y, bool trans) {
	DrawGraph(x, y, this->GHandle, trans ? TRUE : FALSE);
}

void Picture::print(const int x1, const int y1, const int x2, const int y2, bool trans) {
	DrawExtendGraph(x1, y1, x2, y2, this->GHandle, trans ? TRUE : FALSE);
}

Box::Box(const int width, const int height, const Color color, bool fill) : width(width), height(height), color(color), fill(fill) {}

void Box::print(const int x, const int y) {
	DrawBox(x, y, x + this->width, y + this->height, this->color.color_handle, this->fill ? TRUE : FALSE);
}

void Graphic::clear() { ClearDrawScreen(); }

void Graphic::print() { ScreenFlip(); }
