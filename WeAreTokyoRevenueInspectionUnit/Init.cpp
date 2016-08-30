#include"SystemInfo.h"
#include"WindowInfo.h"
#include"DxLib.h"

void window_size_adjustment() {
	if (rc.left < 1440 || rc.bottom < 900) {
		window_width = 960;
		window_height = 540;
	}
}

int init() {
	GetWindowRect(GetDesktopWindow(), &rc);
	window_size_adjustment();
	SetMainWindowText("“Œ‹ž‘Å‹Ç¸Ž@•”‚Å‚·");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(window_width, window_height, 16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(153, 217, 234);
	SetAlwaysRunFlag(TRUE);
	if (DxLib_Init() == -1 || SetMouseDispFlag(TRUE) == -1) return -1;
	SetTransColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	string_handle = CreateFontToHandle("common", 18, DX_FONT_DEFAULT);
	ClearDrawScreen();
	return 0;
}
