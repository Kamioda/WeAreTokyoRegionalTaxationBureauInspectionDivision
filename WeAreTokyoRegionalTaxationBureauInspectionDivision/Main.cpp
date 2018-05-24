#include "ClientInformation.hpp"
#include "KgDxSystem.hpp"
#include "KgWinException.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int) {
	try {
		KgDxSystem::System Sys(GameTitle, 1280, 720, true, KgDxGraphic::Color(TEXT("#ffffff")), KgDxGraphic::Color(TEXT("#ffffff")));

		Sys.End();
		return 0;
	}
	catch (const std::exception& er) {
		MessageBoxA(NULL, er.what(), GameTitleA, MB_ICONERROR | MB_OK);
	}
	catch (const KgWinException& kex) {
		kex.GraphErrorMessageOnMessageBox(GameTitleA);
	}
}
