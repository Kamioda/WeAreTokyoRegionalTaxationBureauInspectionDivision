#include "SystemInfo.h"
#include "Common.h"
#include "Convert.h"
#include "Random.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
constexpr int bright_level_change_speed = 2;

void launch(ApplicationDirectory directory) {
	Picture picture = directory.change_full_path(".\\Graphic\\launch.png", true);
	for (int i = 0; i <= 100; i++) {
		ClearDrawScreen();
		SetDrawBright(255 * i / 100, 255 * i / 100, 255 * i / 100);
		picture.print(0, 0, window_width, window_height, false);
		ScreenFlip();
	}
	WaitTimer(1000);
	for (int i = 100; i >= 0; i--) {
		ClearDrawScreen();
		SetDrawBright(255 * i / 100, 255 * i / 100, 255 * i / 100);
		picture.print(0, 0, window_width, window_height, false);
		ScreenFlip();
	}
}

static std::vector<std::string> read_sound_data_from_txt(const std::string& filepath, ApplicationDirectory directory) {
	if (!PathFileExistsA(filepath.c_str())) throw std::runtime_error("ファイルが見つかりません");
	std::ifstream ifs(filepath);
	std::vector<std::string> arr;
	for (std::string s; std::getline(ifs, s);) arr.emplace_back(directory.change_full_path(s, true));
	return arr;
}

static std::vector<int> read_sound_data(ApplicationDirectory directory) {
	const std::vector<std::string> filepath = read_sound_data_from_txt(directory.change_full_path(".\\System\\title.dat"), directory);
	std::vector<int> sound_handle;
	for (std::string i : filepath) sound_handle.emplace_back(LoadSoundMem(i.c_str()));
	return sound_handle;
}

int title(ApplicationDirectory directory, const int string_size) {
	using clock = std::chrono::system_clock;
	const std::vector<int> title_sound = read_sound_data(directory);
	std::uniform_int_distribution<int> rand(0, title_sound.size() - 1);
	Picture picture = directory.change_full_path(".\\Graphic\\title.png", true).c_str();
	String start_message = String("", string_size, -1, String::FontType::default_font);
	String end_message = String("", string_size, -1, String::FontType::default_font);
	const time_t start = clock::to_time_t(clock::now());
	PlaySoundMem(title_sound[rand(make_mt())], DX_PLAYTYPE_BACK);
	int bright_level = 0;
	while (loop()) {
		ClearDrawScreen();
		SetDrawBright(255 * bright_level / 100, 255 * bright_level / 100, 255 * bright_level / 100);
		picture.print(0, 0, window_width, window_height, false);
		if (clock::to_time_t(clock::now()) - start % 2 == 0) {
			start_message.print(20, window_height - 32, BasicColor::white,"ゲームを始めるにはSpaceキーを押してください。");
			end_message.print(20, window_height - 16, BasicColor::white, "ゲームを終了するにはEscキーを押してください。");
		}
		ScreenFlip();
		if (0 != CheckHitKey(KEY_INPUT_SPACE)) return 0;
		if ([]() {
			if (0 != CheckHitKey(KEY_INPUT_ESCAPE)) return MessageBoxA(NULL, "本当に終了しますか？", "東京国税局査察部です", MB_YESNO) == IDYES;
			else return false;
		}()
		) return -1; // Escキーが押され、終了メッセージで「はい」を選択すると終了する
		bright_level += bright_level == 100 ? 0 : bright_level_change_speed;
	}
	return -1; // ProcessMessage関数が-1になったら強制的に終わらせるため。ここで例外スローすると終了しただけなのにエラーメッセージが出るということもある
}

#include "TaxDataRead.h"
#include "Menu.h"

CriminalInvestigationCase::CriminalInvestigationCase(const std::vector<CaughtTax> list) {
	for (auto& i : list) {
		if (i.tax_name == "所得税") this->income_tax.emplace_back(i);
		else if (i.tax_name == "法人税") this->corporate_tax.emplace_back(i);
		else if (i.tax_name == "相続税") this->inheritance_tax.emplace_back(i);
	}
}

#include "VirtualChildWindow.h"
std::vector<CaughtTax> choose_tax(Key &key, String str, ApplicationDirectory directory) {
	static CriminalInvestigationCase ciCase = CriminalInvestigationCase(read_xml_criminal_investigation_case(directory));
	int cursole = 0;
	VirtualChildWindow child = VirtualChildWindow(320, 180, Color("#228b22"), 80);
	for (int i = 0; loop() && i != 1; i = move_cursole(cursole, 2, key)) {
		ClearDrawScreen();
		child.start();
		str.print(321, 181, BasicColor::white, "どの税金の強制調査に行きますか？");
		print_cursole(321, 199 + (18 * cursole), 54, 18, BasicColor::yellow);
		str.print(321, 199, cursole == 0 ? BasicColor::black : BasicColor::white, "所得税");
		str.print(321, 217, cursole == 1 ? BasicColor::black : BasicColor::white, "法人税");
		str.print(321, 235, cursole == 2 ? BasicColor::black : BasicColor::white, "相続税");
		child.end();
		ScreenFlip();
	}
	return cursole == 0 ? ciCase.income_tax : (cursole == 1 ? ciCase.corporate_tax : ciCase.inheritance_tax);
}

CaughtTax choose_play_criminal_investigation_case(Key &key, String str, ApplicationDirectory directory) {
	const std::vector<CaughtTax> tax = choose_tax(key, str, directory);
	std::uniform_int_distribution<size_t> rand(0, tax.size() - 1);
	return tax[rand(make_mt())];
}
