#include "ApplicationDirectory.h"
#include <Windows.h>
#include <stdexcept>

static std::string getLastErrorText() {
	char* buf = nullptr;
	const auto lasterr = GetLastError();
	const auto len = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
		nullptr,
		lasterr,
		LANG_NEUTRAL,
		(LPSTR)&buf,
		0,
		nullptr
	);
	auto i = len - 3;
	for (; '\r' != buf[i] && '\n' != buf[i] && '\0' != buf[i]; i++);//改行文字削除
	buf[i] = '\0';
	std::string ret = buf + ("(" + std::to_string(lasterr)) + ")";//エラーメッセージ作成
	LocalFree(buf);//FormatMessageAでFORMAT_MESSAGE_ALLOCATE_BUFFERを指定したので必ず開放
	return ret;
}

ApplicationDirectory::ApplicationDirectory() {
#ifdef UNICODE
	wchar_t dir[MAX_PATH];
#else
	char dir[MAX_PATH];
#endif
	if (!GetCurrentDirectory(MAX_PATH, dir)) throw std::runtime_error(getLastErrorText());
	this->default_directory = this->current_directory = dir;
}

void ApplicationDirectory::change_current_directory() {
	if (!SetCurrentDirectory(this->current_directory.c_str())) throw std::runtime_error(getLastErrorText());
}

// change_application_work_directory:復元後、アプリケーションのワークスペースを変更しない場合はfalseを渡す
void ApplicationDirectory::restore_current_directory(bool change_application_work_directory = true) {
	this->current_directory = this->default_directory;
	if (change_application_work_directory) this->change_current_directory();
}

void ApplicationDirectory::update_current_directory() {
#ifdef UNICODE
	wchar_t dir[MAX_PATH];
#else
	char dir[MAX_PATH];
#endif
	if (!GetCurrentDirectory(MAX_PATH, dir)) throw std::runtime_error(getLastErrorText());
	this->current_directory = dir;
}

bool ApplicationDirectory::current_directory_is_default_directory() {
	return this->current_directory == this->default_directory;
}

#ifdef UNICODE
ApplicationDirectory::ApplicationDirectory(const std::wstring default_directory) {
	if (L':' != default_directory.at(1)) {
		wchar_t dir[MAX_PATH];
		if (!GetCurrentDirectory(MAX_PATH, dir)) throw std::runtime_error(getLastErrorText());
		this->default_directory = this->current_directory = dir + default_directory.substr(1u);
	}
	else this->default_directory = this->current_directory = default_directory;
}

// after_changed_directory:変更後のカレントディレクトリ
// change_application_work_directory:アプリケーションのワークスペースを変更後のカレントディレクトリに変更しない場合はfalseを渡す
void ApplicationDirectory::change_current_directory(const std::wstring after_changed_directory, bool change_application_work_directory) {
	if (change_application_work_directory) this->change_current_directory();
	else if (after_changed_directory.empty()) this->update_current_directory();
	else this->current_directory = after_changed_directory;
}

// デフォルトのカレントディレクトリ(アプリケーションの初期ワークスペース)を取得する
std::wstring ApplicationDirectory::get_default_directory() {
	return this->default_directory;
}

// カレントディレクトリを取得する
std::wstring ApplicationDirectory::get_current_directory() {
	this->update_current_directory();
	return this->current_directory;
}

// フルパスに変換する。デフォルトディレクトリを使用する場合は第２引数にtrueを渡す
std::wstring ApplicationDirectory::change_full_path(const std::wstring filepath, bool use_default_directory) {
	if (filepath.empty()) throw std::runtime_error("ファイルパスが入力されていません。");
	else if (L':' == filepath.at(2)) return filepath;
	else return (use_default_directory ? this->default_directory : this->current_directory) + filepath.substr(1u);
}
#else
ApplicationDirectory::ApplicationDirectory(const std::string default_directory) {
	if (':' != default_directory.at(1)) {
		char dir[MAX_PATH];
		if (!GetCurrentDirectory(MAX_PATH, dir)) throw std::runtime_error(getLastErrorText());
		this->default_directory = this->current_directory = dir + default_directory.substr(1u);
	}
	else this->default_directory = this->current_directory = default_directory;
}

// after_changed_directory:変更後のカレントディレクトリ
// change_application_work_directory:アプリケーションのワークスペースを変更後のカレントディレクトリに変更するか
void ApplicationDirectory::change_current_directory(const std::string after_changed_directory, bool change_application_work_directory) {
	if (change_application_work_directory) this->change_current_directory();
	else if (after_changed_directory.empty()) this->update_current_directory();
	else this->current_directory = after_changed_directory;
}

// デフォルトのカレントディレクトリ(アプリケーションの初期ワークスペース)を取得する
std::string ApplicationDirectory::get_default_directory() {
	return this->default_directory;
}

// カレントディレクトリを取得する
std::string ApplicationDirectory::get_current_directory() {
	this->update_current_directory();
	return this->current_directory;
}

// フルパスに変換する。デフォルトディレクトリを使用する場合は第２引数にtrueを渡す
std::string ApplicationDirectory::change_full_path(const std::string filepath, bool use_default_directory) {
	if (filepath.empty()) throw std::runtime_error("ファイルパスが入力されていません。");
	else if (':' == filepath.at(2)) return filepath;
	else return (use_default_directory ? this->default_directory : this->current_directory) + filepath.substr(1u);
}
#endif
