#include "DxLib.h"
#include "KeyConfig.h"
#include "ResourceManager.h"
#include "EasilyPCSP.h"

bool check_pcsp() {
	if (pcsp_end) {
		MessageBox(NULL, "ゲームプレイ制限時間になりました。ゲームを終了します。", "東京国税局査察部です", MB_ICONINFORMATION | MB_OK);
		return false;
	}
	else return true;
}

bool loop() {
	process_control();
	if (-1 == ProcessMessage()) return false;
	else if (GetWindowUserCloseFlag(TRUE) == TRUE) {
		if (MessageBoxA(NULL, "終了しますか？", "東京国税局査察部です", MB_YESNO) == IDYES) {
			return false;
		}
		else return true;
	}
	else return true;
} 
#include "Graphic.h"

void print_cursole(const int x, const int y, const int width, const int height, const Color cursole_color) {
	DrawBox(x, y, x + width, y + height, cursole_color.color_handle, TRUE);
}

#include "KeyConfig.h"
#include "SystemInfo.h"

int move_cursole(int &cursole, const int cursole_max, Key &key) {
	key.buffer_format();
	key.update();
	if (key.up()) cursole == 0 ? cursole = cursole_max : cursole--;
	if (key.down()) cursole == cursole_max ? cursole = 0 : cursole++;
	if (key.choose()) return 1;
	else if (key.cancel()) return -1;
	return 0;
}
