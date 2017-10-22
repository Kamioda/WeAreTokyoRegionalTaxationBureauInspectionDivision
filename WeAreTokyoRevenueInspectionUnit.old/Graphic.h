#pragma once
#include <string>
#include <tchar.h>

struct Color {
	Color() = default;
	Color(const int red, const int green, const int blue);
	Color(const std::string& code);
	unsigned int color_handle;
};

namespace BasicColor {
	const Color black = Color(0, 0, 0);
	const Color red = Color(255, 0, 0);
	const Color green = Color(0, 255, 0);
	const Color blue = Color(0, 0, 255);
	const Color yellow = Color(255, 255, 0);
	const Color magenta = Color(255, 0, 255);
	const Color cyan = Color(0, 255, 255);
	const Color white = Color(255, 255, 255);
}

namespace Graphic {
	inline void clear();
	inline void print();
}

class String {
private:
	int handle;
public:
	String() = default;
	String(const std::string& font_name, const int size, const int thick, const int font_type = -1);
	~String();
	void print(const int x, const int y, const Color string_color, const std::string& str);
	void format_print(const int x, const int y, const Color string_color, const TCHAR* str, ...);
	static void print_nohandle(const int x, const int y, const Color string_color, const std::string& str);
	static void format_print_nohandle(const int x, const int y, const Color string_color, const TCHAR* str, ...);
	class FontType {
	public:
		static constexpr int default_font = -1;
		static constexpr int edge = 0x01;
		static constexpr int antialiasing = 0x02;
		static constexpr int antialiasing_4x4 = 0x12;
		static constexpr int antialiasing_8x8 = 0x22;
		static constexpr int antialiasing_edge = 0x03;
		static constexpr int antialiasing_edge_4x4 = 0x13;
		static constexpr int antialiasing_edge_8x8 = 0x23;
	};
};

class Picture {
private:
	int GHandle;
public:
	Picture() = default;
	Picture(const std::string& filepath);
	Picture(const int GHandle);
	~Picture();
	Picture& operator = (const std::string& filepath);
	Picture& operator = (const int GHandle);
	void print(const int x, const int y, bool trans);
	void print(const int x1, const int y1, const int x2, const int y2, bool trans);
};

class Box {
	int width, height;
	Color color;
	bool fill;
public:
	Box() = default;
	Box(const int width, const int height, const Color color, bool trans);
	void print(const int x, const int y);
};
