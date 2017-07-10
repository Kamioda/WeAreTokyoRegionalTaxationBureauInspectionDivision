#include "Table.h"
#include <array>

constexpr int window_width = 720;
constexpr int window_height = 405;

int init() {
#ifndef _DEBUG
	SetWindowUserCloseEnableFlag(FALSE);
#endif
	SetMainWindowText("キーコンフィグ変更");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(window_width, window_height, 16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(153, 217, 234);
	SetAlwaysRunFlag(TRUE);
	if (DxLib_Init() == -1 || SetMouseDispFlag(TRUE) == -1) return -1;
	SetTransColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	return 0;
}

bool all_zero(std::array<int, 256> buf, int &num) {
	for (size_t i = 0; i < buf.size(); i++) {
		if (buf[i] != 0) {
			num = static_cast<int>(i);
			return false;
		}
	}
	return true;
}

std::string change_num_to_string(int num) {
	for (auto& i : config_list) if (i.second == num) return i.first;
	throw std::runtime_error("このキーは使えません。");
}

std::string change_english_to_japanese(std::string command_line) {
	if (command_line == "up") return "上";
	else if (command_line == "left") return "左";
	else if (command_line == "down") return "下";
	else if (command_line == "right") return "右";
	else if (command_line == "choose") return "決定";
	else if (command_line == "cancel") return "キャンセル";
	else if (command_line == "reload") return "キー情報の再読込み";
	else if (command_line == "screen") return "スクリーンショット";
	else throw std::runtime_error("無効な引数です。");
}

#include "Ini.h"

int key_reset() {
	Ini ini(".\\System\\system.ini");
	ini.edit("key", "up", std::to_string(KEY_INPUT_UP));
	ini.edit("key", "down", std::to_string(KEY_INPUT_DOWN));
	ini.edit("key", "left", std::to_string(KEY_INPUT_LEFT));
	ini.edit("key", "right", std::to_string(KEY_INPUT_RIGHT));
	ini.edit("key", "choose", std::to_string(KEY_INPUT_SPACE));
	ini.edit("key", "cancel", std::to_string(KEY_INPUT_B));
	ini.edit("key", "reload", std::to_string(KEY_INPUT_F11));
	ini.edit("key", "screen", std::to_string(KEY_INPUT_F12));
	return MessageBox(NULL, "キーコンフィグを初期設定に戻しました。", "キーコンフィグ変更", MB_OK);
}

void key_reset(const std::string cmdline) {
	if (cmdline.empty()) {
		if (
			MessageBox(
				NULL,
				"キーコンフィグを初期設定に戻します。\nよろしいですか？\n※初期設定に戻さず、キーの変更を行いたい方は、ランチャーの「設定変更」を選択してください。",
				"キーコンフィグ変更",
				MB_ICONWARNING | MB_YESNO) == IDYES) key_reset();
	}
	else if (
		MessageBox(
			NULL,
			"キーコンフィグを初期設定に戻します。\nよろしいですか？\n",
			"キーコンフィグ変更",
			MB_ICONWARNING | MB_YESNO) == IDYES) key_reset();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow) {
	if (std::strlen(lpCmdLine) == 0 || std::string(lpCmdLine) == "reset") {
		key_reset(lpCmdLine);
		return 0;
	}
	if (-1 == init()) return -1;
	try {
		char KeyStateBuf[256];
		std::array<int, 256> buf;
		buf.fill(0);
		std::string key;
		while (-1 != ProcessMessage()) {
			int num;
			// キーコンフィグ設定部分スタート
			while (-1 != ProcessMessage() && all_zero(buf, num)) {
				ClearDrawScreen();
				DrawFormatString(0, 0, GetColor(0, 0, 0), "%sの操作をどのキーに割り当てますか？", change_english_to_japanese(lpCmdLine).c_str());
				ScreenFlip();
				buf.fill(0);
				while (ProcessMessage() == 0 && CheckHitKeyAll() == 0) {}
				GetHitKeyStateAll(KeyStateBuf);
				if (1 == KeyStateBuf[KEY_INPUT_F11]) {
					MessageBox(NULL, "そのキーは固定キーとして割り当てられています。", "キーコンフィグ変更", MB_OK);
					continue;
				}
				for (int i = 0; i < 256; i++) buf[i] = KeyStateBuf[i];
			}
			// コンフィグ変更確認
			try {
				key = change_num_to_string(num);
			}
			catch (std::exception &er) {
				if (MessageBox(NULL, er.what(), "キーコンフィグ変更", MB_ICONERROR | MB_RETRYCANCEL) == IDCANCEL) return -1;
				else continue;
			}
			char s[1024];
			sprintf_s(s, "%sキーを%sキーに割り当てます。よろしいですか？", change_english_to_japanese(lpCmdLine).c_str(), key.c_str());
			if (MessageBox(NULL, s, "キーコンフィグ変更", MB_YESNO) == IDYES) break;
		}
		// 書き込み
		Ini ini(".\\System\\system.ini");
		ini.edit("key", lpCmdLine, key);
		MessageBox(NULL, "変更完了しました。", "キーコンフィグ変更", MB_OK);
		return DxLib_End();
	}
	catch (std::exception &er) {
		DxLib_End();
		return MessageBox(NULL, er.what(), "キーコンフィグ変更", MB_ICONERROR | MB_OK);
	}
}
