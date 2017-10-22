int window_width = 1280;
int window_height = 720;
bool end_flag = false;
int mapchip_graph_size, message_window_space, string_size;
#include "DxLib.h"
#include "ResourceManager.h"
RECT rc;

void change_title() {
	CPUManagerA cpumanager("WeAreTokyoRevenueInspectionUnit");
	MemoryManager memory(GetCurrentProcessId());
	while (-1 != ProcessMessage()) {
		cpumanager.Update();
		memory.Update();
		SetMainWindowText(
			(
			"“Œ‹‘Å‹Ç¸@•”‚Å‚·@CPU : "
			+ std::to_string(cpumanager.get_usage())
			+ "%@ƒƒ‚ƒŠ : "
			+ std::to_string(memory.get_memory_usage())
			+ "KB"
			).c_str()
		);
	}
}
