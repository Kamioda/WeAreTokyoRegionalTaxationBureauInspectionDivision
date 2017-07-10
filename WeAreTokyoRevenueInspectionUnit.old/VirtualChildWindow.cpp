// 仮想的に子ウィンドウみたいなものを作ろうという試み
#include "VirtualChildWindow.h"
#include "SystemInfo.h"
#include "DxLib.h"

VirtualChildWindow::VirtualChildWindow(const int x, const int y, const Color color, const int blend_level)
	: box(Box(window_width / 2, window_height / 2, color, true)), x(x), y(y), blend_level(blend_level) {}

void VirtualChildWindow::start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (this->blend_level * 255) / 100);
	this->box.print(this->x, this->y);
}

void VirtualChildWindow::end() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
