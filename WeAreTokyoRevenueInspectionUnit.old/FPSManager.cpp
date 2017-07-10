#include "FPSManager.h"
#include "Convert.h"
#include "DxLib.h"
#include "Ini.h"
#include <cmath>

constexpr FPSManager::FPSManager() : FPSManager(60.0f) {}

constexpr FPSManager::FPSManager(const float fps)
	: mStartTime(), mCount(), current_fps(), N(static_cast<int>(fps)), FPS(fps) {}

bool FPSManager::Update() {
	if (this->mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (this->mCount == this->N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		this->current_fps = 1000.f / ((t - this->mStartTime) / (float)this->N);
		this->mCount = 0;
		this->mStartTime = t;
	}
	this->mCount++;
	return true;
}

void FPSManager::Wait() {
	int tookTime = GetNowCount() - this->mStartTime;	//かかった時間
	int waitTime = static_cast<int>((float)this->mCount * 1000.0f / this->FPS - (float)tookTime);	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

constexpr float FPSManager::GetFPS() const {
	return this->current_fps;
}

/*
bool FPSManager::Update() {
	if (this->mCount == 0) { //1フレーム目なら時刻を記憶
		this->mStartTime = std::chrono::steady_clock::now();
	}
	if (this->mCount == this->N) { //60フレーム目なら平均を計算する
		auto t = std::chrono::steady_clock::now();
		this->current_fps = 1000.f / ((t - this->mStartTime) / this->N).count();
		this->mCount = 0;
		this->mStartTime = t;
	}
	this->mCount++;
	return true;
}

void FPSManager::Wait() {
	auto tookTime = std::chrono::steady_clock::now() - this->mStartTime;	//かかった時間
	int waitTime = std::chrono::milliseconds(this->mCount * 1000 / this->FPS) - tookTime;	//待つべき時間
	if (waitTime > 0) {
		std::this_thread::sleep_until(waitTime);	//待機
	}
}
*/
