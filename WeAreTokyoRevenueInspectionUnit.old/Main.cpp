#include "ApplicationDirectory.h"
#include "Common.h"
#include "GMAuthentication.h"
#include "Init.h"
#include "Menu.h"
#include "KeyConfig.h"
#include "SystemInfo.h"
#include "ScreenShot.h"
#include "EasilyPCSP.h"
#include <Windows.h>
#include <thread>
#include <ctime>
/*
デバッグ時要注意箇所
MapGraph.cpp 34~41行目
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow) {
	bool gm_mode =
#ifdef _DEBUG
		true
#else
		is_game_master_mode(lpCmdLine)
#endif
		;
	try {
		ApplicationDirectory directory = ApplicationDirectory();
		Ini system(directory.change_full_path(".\\System\\system.ini"));
		PowerState power = PowerState();
		int string_size;
		if (-1 == init(power, directory, string_size)) return -1;
		Key key = Key(directory);
		String 	str = String("common", 18, DX_FONT_DEFAULT);
		std::thread th(&change_title);
		th.detach();
		launch(directory);
		if (-1 == title(directory, string_size)) return end(-1); // Escキーを押すと強制終了
		std::thread pcsp(&easily_pcsp, system, std::chrono::system_clock::now(), gm_mode);
		pcsp.detach();
		while (loop() && check_pcsp()) {
			const CaughtTax tax = choose_play_criminal_investigation_case(key, str, directory);
		}
		return end(0);
	}
	catch (const std::exception &er) {
		return end(er.what());
	}
}
