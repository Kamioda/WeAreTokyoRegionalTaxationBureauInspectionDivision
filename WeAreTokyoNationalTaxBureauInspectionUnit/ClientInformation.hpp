#pragma once
constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;
constexpr const char* GameTitleA = "“Œ‹‘Å‹Ç¸@•”‚Å‚·";
constexpr const wchar_t* GameTitleW = L"“Œ‹‘Å‹Ç¸@•”‚Å‚·";
#ifdef UNICODE
constexpr const wchar_t* GameTitle = GameTitleW;
#else
constexpr const char* GameTitle = GameTitleA;
#endif
