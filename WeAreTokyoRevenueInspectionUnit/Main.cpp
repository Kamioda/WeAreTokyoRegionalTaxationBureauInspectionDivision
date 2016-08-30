#include<Windows.h>
#include"Init.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow) {
	if (-1 == init()) return -1;
}
