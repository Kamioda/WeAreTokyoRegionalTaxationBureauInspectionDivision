#include "SystemInfo.h"
#include "KeyConfig.h"
#include "Ini.h"
#include "Convert.h"
#include "WindowInfo.h"
#include "PowerState.h"
#include "Graphic.h"
#include "DxLib.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

static inline void window_size_adjustment_use_rect() {
	if (rc.left < 1440 || rc.bottom < 900) {
		window_width = 960;
		window_height = 540;
	}
}

constexpr bool window_size_is_reserved_size_balance(const int width, const int height, const int width_balance, const int height_balance) {
	return (width % width_balance != 0 || height % height_balance != 0) ? false : height == height_balance * (width / width_balance);
}

static void window_size_adjustment(ApplicationDirectory directory) {
	window_size_adjustment_use_rect();
	if (PathFileExistsA(directory.change_full_path(".\\user.ini", true).c_str())) {
		Ini ini = Ini(directory.change_full_path(".\\user.ini", true));
		const int width = ini.getnum("Window", "width", window_width == 960 ? 960 : 1280);
		const int height = ini.getnum("Window", "height", window_height == 540 ? 540 : 720);
		if (window_size_is_reserved_size_balance(width, height, 16, 9)) {
			window_width = width;
			window_height = height;
		}
	}
	mapchip_graph_size = mapchip_size * window_width / 1280;
}

// 1280-20 640-10
static inline int calc_message_window_coordinate() {
	return 20 * window_width / 1280;
}

// 1280-16
static inline int calc_string_size() {
	return 16 * window_width / 1280;
}

int init(PowerState power, ApplicationDirectory directory, int &string_size) {
	if (power.GetACPowerState() != ACPowerState::online) {
		if (IDNO == MessageBoxA(
			NULL,
			"電源に接続されていません。\n"
			"ゲーム中は、バッテリー消費が大きくなることがあるだけでなく、\n"
			"CPU使用率が高くなり、本ゲームや他のプロセスの動作が不安定になることがあります。\n"
			"それでもプレイしますか？",
			"東京国税局査察部です",
			MB_ICONWARNING | MB_YESNO
		)) return -1;
	}
	SetWindowUserCloseEnableFlag(FALSE);
	GetWindowRect(GetDesktopWindow(), &rc);
	window_size_adjustment(directory);
	SetMultiThreadFlag(TRUE);
	SetMainWindowText("東京国税局査察部です");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(window_width, window_height, 16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255, 255, 255);
	SetAlwaysRunFlag(TRUE);
	if (DxLib_Init() == -1 || SetMouseDispFlag(TRUE) == -1) return -1;
	SetTransColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	string_size = calc_string_size();
	message_window_space = calc_message_window_coordinate();
	return 0;
}


int end(const int ret_num) {
	end_flag = true;
	DxLib_End();
	return ret_num;
}

int end(const char* error_message) {
	return end(MessageBox(NULL, error_message, "東京国税局査察部です", MB_ICONERROR | MB_OK));
}