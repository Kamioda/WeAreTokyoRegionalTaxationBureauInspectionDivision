#include "ApplicationDirectory.h"
#include "ConfigRead.h"
#include "DxLib.h"
const int window_width = get_int_from_config_file("x2");
const int window_height = get_int_from_config_file("y2") + 20;


int init() {
	SetWindowUserCloseEnableFlag(FALSE);
	SetMultiThreadFlag(TRUE);
	SetMainWindowText(get_text_from_config_file("title").c_str());
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

#include "Ini.h"
#include "GetEnvironmentVariable.h"
#include "GetUser_m.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#ifdef _DEBUG
#pragma comment(lib, "GetUser_md.lib")
#else
#pragma comment(lib, "GetUser_m.lib")
#endif

struct MachineInfo {
	MachineInfo(std::string machine_name, std::string user_name, std::string user_full_name, std::string pw)
		: machine_name(machine_name), user_name(user_name), user_full_name(user_full_name), pw(pw) {}
	bool operator == (const MachineInfo& machine) {
		return this->machine_name == machine.machine_name
			&& this->user_name == machine.user_name
			&& this->user_full_name == machine.user_full_name
			&& this->pw == machine.pw;
	}
	std::string machine_name;
	std::string user_name;
	std::string user_full_name;
	std::string pw;
};

#define Win7 "KAMIMEGU-VAIO"
#define Win10 "AMAKAMI-VAIO"

MachineInfo machine_info[] = {
	MachineInfo(Win7, "Kamioda", "神御田", "kagucho2503"),
	MachineInfo(Win7, "AinoMegumi", "あいめぐ", "happinesschargeprecure2014"),
	MachineInfo(Win10, "AmanoIchigo", "いちご", "yumeiro2010"),
	MachineInfo(Win10, "Kamioda", "神御田", "kaguchokamioda2014"),
	MachineInfo(Win10, "聖人", "神御田聖人", "cardcaptorsakura19860401")
};

bool IsGameMaster() {
	EnvironmentVariable env = EnvironmentVariable();
	if (get_text_from_config_file("cmdline") != "/mode:gm") return false;
	if (!PathFileExists((env.get_variable_num("AppData") + "\\Kamioda Games\\wtriugm.ini").c_str())) return false;
	Ini gm(env.get_variable_num("AppData") + "\\Kamioda Games\\wtriugm.ini");
	return MachineInfo(
		env.get_variable_num("ComputerName"),
		env.get_variable_num("UserName"),
		GetUser().search_user_name_to_full_name(env.get_variable_num("UserName")),
		gm.getString("GameMaster", "PW", "")
	) == machine_info[gm.getnum("GameMaster", "ID", 0)];
}

namespace GMPattern {
	void CreateButton() {
		DrawBox(0, window_height - 20, window_width, window_height, GetColor(0, 0, 0), FALSE);
		DrawLine(window_width / 4, window_height - 20, window_width / 4, window_height, GetColor(0, 0, 0));
		DrawLine(window_width / 2, window_height - 20, window_width / 2, window_height, GetColor(0, 0, 0));
		DrawLine(window_width * 3 / 2, window_height - 20, window_width * 3 / 4, window_height, GetColor(0, 0, 0));
		DrawString(2, window_height - 18, "ユーザーモード", GetColor(0, 0, 0));
		DrawString((window_width / 4) + 2, window_height - 18, "ゲームマスターモード", GetColor(0, 0, 0));
		DrawString((window_width / 2) + 2, window_height - 18, "設定変更", GetColor(0, 0, 0));
		DrawString((window_width * 3 / 4) + 2, window_height - 18, "終了", GetColor(0, 0, 0));
	}
	void ChangeCursolePointColor(const int cursole) {

	}
}

namespace UserPattern {
	void CreateButton() {
		DrawBox(0, window_height - 20, window_width, window_height, GetColor(0, 0, 0), FALSE);
		DrawLine(window_width / 4, window_height - 20, window_width / 4, window_height, GetColor(0, 0, 0));
		DrawLine(window_width / 2, window_height - 20, window_width / 2, window_height, GetColor(0, 0, 0));
		DrawLine(window_width * 3 / 2, window_height - 20, window_width * 3 / 4, window_height, GetColor(0, 0, 0));
		DrawString(2, window_height - 18, "ゲームスタート", GetColor(0, 0, 0));
		DrawString((window_width / 4) + 2, window_height - 18, "簡易PCSP設定", GetColor(0, 0, 0));
		DrawString((window_width / 2) + 2, window_height - 18, "その他の設定変更", GetColor(0, 0, 0));
		DrawString((window_width * 3 / 4) + 2, window_height - 18, "終了", GetColor(0, 0, 0));
	}
	void ChangeCursolePointColor(const int cursole) {

	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow) {
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(CmdShow);
	try {
		directory = ApplicationDirectory();
		Ini ini(directory.change_full_path(".\\config\\message.ini"));
		if (FALSE == PathFileExistsA(directory.change_full_path(".\\config\\config.lcr").c_str()))
			return MessageBoxA(NULL, ini.getString("Message", "notlcr", "not lcr").c_str(), "ランチャーエラー", MB_ICONERROR | MB_OK);
		if (-1 == init()) return -1;
		int x, y, mouse = -1;
		const int GHandle = LoadGraph(get_text_from_config_file("launchergraph").c_str());
		const bool gmflag = IsGameMaster();
		while (-1 != ProcessMessage()) {
			ClearDrawScreen();
			DrawExtendGraph(0, 0, window_width, window_height - 20, GHandle, FALSE);
			if (gmflag) {
				using namespace GMPattern;
				CreateButton();
				ChangeCursolePointColor(mouse);
			}
			GetMousePoint(&x, &y);
			
		}
		return 0;
	}
	catch (std::exception) {
		return MessageBoxA(NULL, "不明なエラーが発生しました", "ランチャーエラー", MB_ICONERROR | MB_OK);
	}
}
