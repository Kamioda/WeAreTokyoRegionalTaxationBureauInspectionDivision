#pragma once
#include "TaxDataRead.h"
#include "Graphic.h"
#include "KeyConfig.h"

class Message {
private:
	CaughtTax tax;
	Color string_color;
	String str;
	inline void confirm(const int x, const int y, Key &key, const std::string& message);
	inline void start_criminal_investigation(const int x, const int y, Key &key);
public:
	Message() = default;
	Message(const CaughtTax tax, const Color string_color, const String str);
	void game_start(const int x, const int y, Key &key);
};
