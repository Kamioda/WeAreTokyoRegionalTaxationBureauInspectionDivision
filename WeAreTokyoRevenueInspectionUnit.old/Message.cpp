#include "SystemInfo.h"
#include "Message.h"
#include "Common.h"

Message::Message(const CaughtTax tax, const Color string_color, const String str)
	: tax(tax), string_color(string_color), str(str) {}

void Message::confirm(const int x, const int y, Key &key, const std::string& message) {
	while (loop() && !key.choose()) {
		Graphic::clear();
		this->str.print(x, y, this->string_color, message);
		Graphic::print();
	}
}

void Message::start_criminal_investigation(const int x, const int y, Key &key) {
	while (loop() && !key.choose()) {
		Graphic::clear();
		this->str.print(x, y, this->string_color, "東京国税局査察部です。");
		this->str.print(x, y + string_size, this->string_color, this->tax.tax_name + "法違反の嫌疑で、ただいまより強制調査を行います。");
	}
}

/*
void game_start(const int x, const int y, const unsigned int color, const CaughtTax tax, const std::string& message, Key &key) {
	confirm_target_name(x, y, color, tax.target_name, key);
	confirm_us(x, y, color, message, key);
	start_criminal_investigation(x, y, color, tax.tax_name, key);
}

void print_message_window() {

}

void print_discovered_item(const int x, const int y, const std::string item_name) {
	DrawString(x, y, item_name.c_str(), GetColor(255, 255, 255));
}
*/