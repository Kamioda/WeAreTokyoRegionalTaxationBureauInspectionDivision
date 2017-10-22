#pragma once
#include "ApplicationDirectory.h"
#include <array>
#include <utility>
constexpr char* config_filepath = ".\\System\\config.ini";

class Key {
private:
	ApplicationDirectory directory;
	std::array<char, 256> buffer;
	int up_key, down_key, left_key, right_key, choose_key, cancel_key, screen_shot_key;
	void load_config(); // コンフィグの読み込み(config.iniのロード)
public:
	Key() = default;
	Key(ApplicationDirectory directory);
	void buffer_format(); // 配列初期化
	void update(); // キー状態の再取得
	bool up();
	bool down();
	bool left();
	bool right();
	bool choose();
	bool cancel();
	bool screen_shot();
};
