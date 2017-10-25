#include "D:/Users/AinoMegumi/BitBucket/Kamioda Games/CommonSourceCode/Split.hpp"
#include "Core.hpp"
#include <Windows.h>
#include <process.h>
#include "KgWinException.hpp"

/*
	コマンドラインとして必要なもの
	/UserName:(ユーザー名)
	/PCSP:(PCSPによる制限フラグ)
*/

static inline std::string GetDataFromCommandLine(const std::vector<std::string> Args, const std::string SearchData) {
	for (auto& i : Args) {
		const std::vector<std::string> Temp = SplitA(i, ':');
		if (Temp[0] == "/" + SearchData) return Temp[1];
	}
	return "";
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow) {
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(CmdShow);
	try {
		if (std::strlen(lpCmdLine) == 0) {

		}
		else {
			const std::vector<std::string> Args = SplitA(lpCmdLine, ' ');
			UserName = GetDataFromCommandLine(Args, "UserName");
			PCSPRunFlag = (GetDataFromCommandLine(Args, "PCSPRun") == "true");
			
		}
	}
	catch (const std::exception& er) {
		return MessageBoxA(NULL, er.what(), "東京国税局査察部です", MB_ICONERROR | MB_OK);
	}
	catch (const KgWinException& kex) {
		return kex.GraphErrorMessageOnMessageBox("東京国税局査察部です");
	}
}
