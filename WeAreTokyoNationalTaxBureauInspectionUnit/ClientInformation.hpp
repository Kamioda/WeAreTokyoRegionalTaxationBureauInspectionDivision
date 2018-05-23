#pragma once
constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;
constexpr const char* GameTitleA = "東京国税局査察部です";
constexpr const wchar_t* GameTitleW = L"東京国税局査察部です";
#ifdef UNICODE
constexpr const wchar_t* GameTitle = GameTitleW;
#else
constexpr const char* GameTitle = GameTitleA;
#endif
