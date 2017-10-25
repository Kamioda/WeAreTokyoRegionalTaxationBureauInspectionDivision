/*
	MIT License

	Copyright (c) 2017 シャーリィ＠Windowsゲームプログラマー(学生)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#ifndef __MSXMLREAD_HPP__
#define __MSXMLREAD_HPP__
#include <msxml.h>
#include <tchar.h>
#include <wrl/client.h>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

class MSXMLRead;

class Node {
	friend class MSXMLRead;
private:
	Microsoft::WRL::ComPtr<IXMLDOMNodeList> NodeList;
	long Length;
public:
	Node() = default;
	std::basic_string<TCHAR> GetData(const long Count) const;
	template<typename T, std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value, std::nullptr_t> = nullptr>
	T GetSignedInteger(const long Count) const { return static_cast<T>(std::stoll(this->GetData(Count))); }
	template<typename T, std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value, std::nullptr_t> = nullptr>
	T GetUnsignedInteger(const long Count) const { return static_cast<T>(std::stoull(this->GetData(Count))); }
	template<typename T, std::enable_if_t<std::is_floating_point<T>::value, std::nullptr_t> = nullptr>
	T GetFloat(const long Count) const { return static_cast<T>(std::stod(this->GetData(Count))); }
	long GetLength() const noexcept { return this->Length; }
	std::basic_string<TCHAR> operator [] (const long Count) const { return this->GetData(Count); }
	std::basic_string<TCHAR> NodePath;
};

class MSXMLRead {
private:
	Microsoft::WRL::ComPtr<IXMLDOMDocument> lpXmlDoc;
	IXMLDOMNodeList* XmlSetNodeList(const std::basic_string<TCHAR> NodePath);
	std::vector<Node> Data;
	std::basic_string<TCHAR> CommonPath;
	void LoadFromFile(const std::basic_string<TCHAR> NodePath);
public:
	MSXMLRead(const std::basic_string<TCHAR> FileName, const std::basic_string<TCHAR> CommonPath = TEXT(""));
	~MSXMLRead();
	long GetLength(const std::basic_string<TCHAR> NodePath) const noexcept;
	void Load(const std::basic_string<TCHAR> NodePath) { this->LoadFromFile(NodePath); }
	template<class ...Args> void Load(const std::basic_string<TCHAR> NodePath, Args ...arg) {
		this->LoadFromFile(NodePath);
		this->Load(std::forward<Args>(arg)...);
	}
	bool NodeDataExists(const std::basic_string<TCHAR> NodePath) const noexcept;
	size_t size() const noexcept { return this->Data.size(); }
	Node at(const size_t Count) const {
		if (Count >= this->size()) throw std::out_of_range("max num is " + std::to_string(this->size() - 1));
		return this->Data[Count];
	}
	void clear() { this->Data.clear(); }
	void ChangeCommonPath(const std::basic_string<TCHAR> NewRoot);
	Node operator [] (const size_t Count) const { return this->at(Count); }
	Node operator [] (const std::basic_string<TCHAR> NodePath) const; // WStringToStringを使う関係でcpp側に定義
};
#endif