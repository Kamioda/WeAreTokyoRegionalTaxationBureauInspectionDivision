#pragma once
class FPSManager {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float current_fps;             //fps
	int N;//平均を取るサンプル数
	float FPS;	//設定したFPS
public:
	constexpr FPSManager();
	constexpr FPSManager(const float fps);
	bool Update();
	constexpr float GetFPS() const;
	void Wait();
};
