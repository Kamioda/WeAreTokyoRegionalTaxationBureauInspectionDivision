#include "KeyConfig.h"
#include "Ini.h"
#include "DxLib.h"
#include <vector>
#include <stdexcept>

// 「東京国税局査察部です」で使用可能なキー一覧
const std::vector<std::pair<std::string, int>> config_list = {
	// 記号、文字等操作キー
	{ "Backspace", KEY_INPUT_BACK }, { "Tab", KEY_INPUT_TAB }, { "Enter", KEY_INPUT_RETURN }, { "LeftShift", KEY_INPUT_LSHIFT }, 
	{ "RightShift", KEY_INPUT_RSHIFT },	{ "LeftCtrl", KEY_INPUT_LCONTROL },	{ "RightCtrl", KEY_INPUT_RCONTROL }, { "Esc", KEY_INPUT_ESCAPE },
	{ "Space", KEY_INPUT_SPACE }, { "PageUp", KEY_INPUT_PGUP },	{ "PageDown", KEY_INPUT_PGDN },	{ "End", KEY_INPUT_END }, { "Home", KEY_INPUT_HOME },
	{ "←", KEY_INPUT_LEFT }, { "↑", KEY_INPUT_UP }, { "→", KEY_INPUT_RIGHT }, { "↓", KEY_INPUT_DOWN }, { "Insert", KEY_INPUT_INSERT },
	{ "Delete", KEY_INPUT_DELETE },	{ "-", KEY_INPUT_MINUS }, { "YEN", KEY_INPUT_YEN },	{ "^", KEY_INPUT_PREVTRACK }, { ".", KEY_INPUT_PERIOD },
	{ "/", KEY_INPUT_SLASH }, { "LeftAlt", KEY_INPUT_LALT }, { "RightAlt", KEY_INPUT_RALT }, { ";", KEY_INPUT_SEMICOLON }, { ":", KEY_INPUT_COLON },
	{ "[", KEY_INPUT_LBRACKET }, { "]", KEY_INPUT_RBRACKET }, { "@", KEY_INPUT_AT }, { "BackSlash", KEY_INPUT_BACKSLASH }, { ",", KEY_INPUT_COMMA },
	{ "半角/全角", KEY_INPUT_KANJI }, { "変換", KEY_INPUT_KANJI }, { "無変換", KEY_INPUT_NOCONVERT }, { "カタカナ/ひらがな", KEY_INPUT_KANA },
	{ "アプリケーション", KEY_INPUT_APPS }, { "PrintScreen", KEY_INPUT_SYSRQ }, { "PauseBreak", KEY_INPUT_PAUSE }, { "LeftWindows", KEY_INPUT_LWIN },
	{ "RightWindows", KEY_INPUT_RWIN },	

	// Numパッド数字キー
	{ "Num0", KEY_INPUT_NUMPAD0 }, { "Num1", KEY_INPUT_NUMPAD1 }, { "Num2", KEY_INPUT_NUMPAD2 }, { "Num3", KEY_INPUT_NUMPAD3 },
	{ "Num4", KEY_INPUT_NUMPAD4 }, { "Num5", KEY_INPUT_NUMPAD5 }, { "Num6", KEY_INPUT_NUMPAD6 }, { "Num7", KEY_INPUT_NUMPAD7 },
	{ "Num8", KEY_INPUT_NUMPAD8 }, { "Num9", KEY_INPUT_NUMPAD9 },
	
	// Numパッド演算子キー
	{ "NumAsterisk", KEY_INPUT_MULTIPLY }, { "NumPlus", KEY_INPUT_ADD }, { "NumMinus", KEY_INPUT_SUBTRACT }, { "NumPeriod", KEY_INPUT_DECIMAL },
	{ "NumSlash", KEY_INPUT_DIVIDE }, { "NumEnter", KEY_INPUT_NUMPADENTER }, 
	
	// ファンクションキー
	{ "F1", KEY_INPUT_F1 }, { "F2", KEY_INPUT_F2 }, { "F3", KEY_INPUT_F3 },
	{ "F4", KEY_INPUT_F4 },	{ "F5", KEY_INPUT_F5 },	{ "F6", KEY_INPUT_F6 },	
	{ "F7", KEY_INPUT_F7 },	{ "F8", KEY_INPUT_F8 },	{ "F9", KEY_INPUT_F9 },
	{ "F10", KEY_INPUT_F10 }, {"F11", KEY_INPUT_F11} ,{ "F12", KEY_INPUT_F12 },
	
	// アルファベットキー
	{ "A", KEY_INPUT_A }, { "B", KEY_INPUT_B }, { "C", KEY_INPUT_C }, { "D", KEY_INPUT_D }, { "E", KEY_INPUT_E }, { "F", KEY_INPUT_F },
	{ "G", KEY_INPUT_G }, { "H", KEY_INPUT_H }, { "I", KEY_INPUT_I }, { "J", KEY_INPUT_J }, { "K", KEY_INPUT_K }, { "L", KEY_INPUT_L },
	{ "M", KEY_INPUT_M }, { "N", KEY_INPUT_N }, { "O", KEY_INPUT_O }, { "P", KEY_INPUT_P }, { "Q", KEY_INPUT_Q }, { "R", KEY_INPUT_R },
	{ "S", KEY_INPUT_S }, { "T", KEY_INPUT_T }, { "U", KEY_INPUT_U }, { "V", KEY_INPUT_V }, { "W", KEY_INPUT_W }, { "X", KEY_INPUT_X }, 
	{ "Y", KEY_INPUT_Y }, { "Z", KEY_INPUT_Z },
	
	// 数字キー
	{ "0", KEY_INPUT_0 }, { "1", KEY_INPUT_1 },	{ "2", KEY_INPUT_2 }, { "3", KEY_INPUT_3 },	{ "4", KEY_INPUT_4 }, { "5", KEY_INPUT_5 },
	{ "6", KEY_INPUT_6 }, { "7", KEY_INPUT_7 },	{ "8", KEY_INPUT_8 }, { "9", KEY_INPUT_9 }
};

bool is_num(const std::string& str) {
	try {
		std::stoi(str);
		return true;
	}
	catch (std::exception) {
		return false;
	}
}

int change_key_data(const std::string& keyString, const int default_key) {
	if (is_num(keyString)) return std::stoi(keyString);
	else {
		for (std::pair<std::string, int> i : config_list) if (keyString == i.first) return i.second;
		return default_key;
	}
}

Key::Key(ApplicationDirectory directory) {
	this->directory = directory;
	this->buffer_format();
	this->load_config();
}

void Key::buffer_format() {
	this->buffer.fill(0);
}

void Key::load_config() {
	Ini ini(this->directory.change_full_path(".\\System\\key.ini", true));
	this->up_key = change_key_data(ini.getString("key", "up", "↑"), KEY_INPUT_UP);
	this->down_key = change_key_data(ini.getString("key", "up", "↓"), KEY_INPUT_DOWN);
	this->left_key = change_key_data(ini.getString("key", "left", "→"), KEY_INPUT_RIGHT);
	this->right_key = change_key_data(ini.getString("key", "right", "←"), KEY_INPUT_LEFT);
	this->choose_key = change_key_data(ini.getString("key", "choose", "Space"), KEY_INPUT_SPACE);
	this->cancel_key = change_key_data(ini.getString("key", "cancel", "B"), KEY_INPUT_B);
	this->screen_shot_key = change_key_data(ini.getString("key", "screen", "F12"), KEY_INPUT_F12);
}

void Key::update() {
	this->buffer_format();
	char KeyStateBuf[256];
	GetHitKeyStateAll(KeyStateBuf);
	for (int i = 0; i < 256; i++) this->buffer[i] = KeyStateBuf[i];
	delete[] KeyStateBuf;
}

bool Key::up() {
	return 0 != this->buffer[this->up_key];
}

bool Key::down() {
	return 0 != this->buffer[this->down_key];
}

bool Key::left() {
	return 0 != this->buffer[this->left_key];
}

bool Key::right() {
	return 0 != this->buffer[this->right_key];
}

bool Key::choose() {
	return 0 != this->buffer[this->choose_key];
}

bool Key::cancel() {
	return 0 != this->buffer[this->cancel_key];
}

bool Key::screen_shot() {
	return 0 != this->buffer[this->screen_shot_key];
}
