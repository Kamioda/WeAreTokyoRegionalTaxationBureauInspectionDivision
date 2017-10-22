#pragma once
#include <Pdh.h>
#include <Psapi.h>
#include <string>
class CPUManagerA {
private:
	PDH_HQUERY              hQuery;
	PDH_HCOUNTER            hCounter;
	PDH_RAW_COUNTER         rawValueStack;
	PDH_FMT_COUNTERVALUE    fmtValue;
	int core;
	double cpu_usage;
	bool GetTotalUsage;
	void UpdateT();
	void UpdateP();
	void remove_extension(std::string &process_name);
public:
	CPUManagerA(const char* process_name = NULL);
	CPUManagerA(const std::string& process_name);
	~CPUManagerA();
	CPUManagerA& operator = (const CPUManagerA& c);
	CPUManagerA& operator = (const char* process_name);
	CPUManagerA& operator = (const std::string& process_name);
	bool throw_exception;
	void Update();
	double get_usage();
};

class MemoryManager {
private:
	HANDLE process_handle;
	PROCESS_MEMORY_COUNTERS memory;
public:
	MemoryManager() = default;
	MemoryManager(const DWORD pid);
	~MemoryManager();
	double get_memory_usage(); // ワーキングセットの値を取得
	void Update();
};

void process_control();
