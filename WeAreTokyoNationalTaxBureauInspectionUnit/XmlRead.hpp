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
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <msxml.h>
#include <tchar.h>

class Node {
private:
public:
	Node() = default;
	std::basic_string<TCHAR> NodePath;
	IXMLDOMNodeList* NodeList;
	long Length;
	std::basic_string<TCHAR> operator [] (const long Count) const; // ちょっと長いからcpp側に定義
};

class MSXMLRead {
private:
	IXMLDOMDocument* lpXmlDoc;
	IXMLDOMNodeList* XmlSetNodeList(const std::basic_string<TCHAR> NodePath, long &Length);
	std::vector<Node> Data;
	std::basic_string<TCHAR> CommonPath;
	void LoadFromFile(const std::basic_string<TCHAR> NodePath);
public:
	MSXMLRead(const std::basic_string<TCHAR> FileName, const std::basic_string<TCHAR> CommonPath = TEXT(""));
	~MSXMLRead() {
		this->lpXmlDoc->Release();
		this->Data.clear();
	}
	long CheckLength(const std::basic_string<TCHAR> NodePath);
	void Check(const std::basic_string<TCHAR> NodePath) { this->CheckLength(NodePath); }
	template<class ...Args> void Check(const std::basic_string<TCHAR> NodePath, Args ...arg) {
		this->CheckLength(NodePath);
		this->Check(std::forward<Args>(arg)...);
	}
	void Load(const std::basic_string<TCHAR> NodePath) { this->LoadFromFile(NodePath); }
	template<class ...Args> void Load(const std::basic_string<TCHAR> NodePath, Args ...arg) {
		this->LoadFromFile(NodePath);
		this->Load(std::forward<Args>(arg)...);
	}
	size_t size() const { return this->Data.size(); }
	Node at(const size_t Count) const { return this->Data[Count]; }
	void clear() { this->Data.clear(); }
	void ChangeCommonPath(const std::basic_string<TCHAR> NewRoot);
	Node operator [] (const size_t Count) const { return this->at(Count); }
	Node operator [] (const std::basic_string<TCHAR> NodePath) const; // WStringToStringを使う関係でcpp側に定義
};
#endif
