#pragma once
#include <Windows.h>

enum class ACPowerState {
	online, offline, backup
};

enum class BatteryState {
	high, low, critical, charging, not_exist
};

class PowerState {
private:
	LPSYSTEM_POWER_STATUS power;
public:
	PowerState();
	void Update();
	bool ACPowerIsOnline();
	bool BatteryExists();
	ACPowerState GetACPowerState();
	BatteryState GetBatteryState();
	int GetBatteryRemain();
};
