// Easily Kamioda Games Parental Control Service Platform(WeAreTokyoRevenueInspectionUnit.exeÇÃÇ›Çêßå¿Ç∑ÇÈä»à’PCSPÅBéûä‘ï€ë∂ã@î\ÇÕÇ»Çµ)
#include "Convert.h"
#include "SystemInfo.h"
#include "Ini.h"
#include <ctime>
#include <chrono>
#include <mutex>
static std::mutex mutex;

bool pcsp_end = false;

void easily_pcsp(Ini ini, const std::chrono::time_point<std::chrono::system_clock> start, const bool gm_mode) {
	if (gm_mode) return;
	try {
		const time_t minute = static_cast<time_t>(ini.getnum("EPCSP", "time", 0)) * 60;
		if (minute != 0) {
			tm end;
			gmtime_s(&end, &minute);
			tm current;
			using clock = std::chrono::system_clock;
			for (time_t now = clock::to_time_t(clock::now());
				current.tm_hour == end.tm_hour && current.tm_min == end.tm_min;
				now = clock::to_time_t(clock::now()), localtime_s(&current, &now)) {
				if (end_flag) return;
			}
			mutex.lock();
			pcsp_end = true;
			mutex.unlock();
		}
	}
	catch (std::exception) {}
}
