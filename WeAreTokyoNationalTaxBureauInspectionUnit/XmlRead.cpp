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
#include "KgWinException.hpp"
#include "XmlRead.hpp"
#include <Shlwapi.h>
#include <comdef.h>
#include <type_traits>
#pragma comment(lib, "Shlwapi.lib")

namespace Win32LetterConvert {
	// code copy from Storage.cpp in repositry "DefeatMonster.old"(Author:AinoMegumi)
	std::string WStringToString(const std::wstring oWString) {
		const int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, (char *)NULL, 0, NULL, NULL);
		if (0 == iBufferSize) throw KgWinException(); // std::runtime_error -> KgWinException
		char* cpMultiByte = new char[iBufferSize];
		WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
		std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
		delete[] cpMultiByte;
		return oRet;
	}
	std::wstring StringToWString(const std::string oString) {
		const int iBufferSize = MultiByteToWideChar(CP_OEMCP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);
		if (0 == iBufferSize) throw KgWinException(); // std::runtime_error -> KgWinException
		wchar_t* cpWideChar = new wchar_t[iBufferSize];
		MultiByteToWideChar(CP_OEMCP, 0, oString.c_str(), -1, cpWideChar, iBufferSize);
		std::wstring oRet(cpWideChar, cpWideChar + iBufferSize - 1);
		delete[] cpWideChar;
		return oRet;
	}
}

namespace Replace {
	// code copy from make_array.h in repositry xml_text_cooking_quiz(Author:yumetodo)
	std::basic_string<TCHAR> LF(std::basic_string<TCHAR>&& Str) {
		if (_T("empty") == Str) return _T("");
		const std::basic_string<TCHAR> ReplaceTarget = _T("\\n");
		const std::basic_string<TCHAR> AfterReplace = _T("\n");
		for (size_t pos = Str.find(ReplaceTarget); std::string::npos != pos; pos = Str.find(ReplaceTarget, pos + AfterReplace.length())) {
			Str.replace(pos, ReplaceTarget.length(), AfterReplace);
		}
		return Str;
	}
}

std::basic_string<TCHAR> Node::operator [] (const long Count) const {
	IXMLDOMNode* lpItem;
	this->NodeList->get_item(Count, &lpItem);
	BSTR Strings;
	lpItem->get_text(&Strings);
	std::basic_string<TCHAR> Str = Replace::LF(
#if defined(UNICODE)
		Strings
#else
		Win32LetterConvert::WStringToString(Strings)
#endif
	);
	Str.resize(std::char_traits<TCHAR>::length(Str.c_str()));
	return Str;
}

MSXMLRead::MSXMLRead(const std::basic_string<TCHAR> FileName, const std::basic_string<TCHAR> CommonPath) {
	if (FALSE == PathFileExists(FileName.c_str())) throw std::runtime_error(
#if defined(UNICODE)
		Win32LetterConvert::WStringToString(FileName)
#else
		FileName
#endif
		+ " : file is not found.");
	CoInitialize(nullptr);
	IXMLDOMDocument* XmlDoc;
	const HRESULT ErrorCode = CoCreateInstance(CLSID_DOMDocument, nullptr, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**)&XmlDoc);
	if (XmlDoc == nullptr) throw KgWinException("xml open failed.\nCause : ", ErrorCode); // std::runtime_error -> KgWinException
	this->lpXmlDoc = XmlDoc;
	VARIANT_BOOL Result;
	this->lpXmlDoc->put_async(VARIANT_FALSE);
	this->lpXmlDoc->load(_variant_t(FileName.c_str()), &Result);
	if (0 == Result) {
		this->lpXmlDoc->Release();
		CoUninitialize();
		throw std::runtime_error("xml read failed");
	}
	this->CommonPath = CommonPath;
}

IXMLDOMNodeList* MSXMLRead::XmlSetNodeList(const std::basic_string<TCHAR> NodePath, long &Length) {
	BSTR Path = SysAllocString((
#if defined(UNICODE)
		this->CommonPath + NodePath
#else
		Win32LetterConvert::StringToWString(this->CommonPath + NodePath)
#endif
		).c_str());
	if (NodePath.empty() || 0 == SysStringLen(Path)) {
		SysFreeString(Path);
		return NULL;
	}
	IXMLDOMNodeList* lpNodeList;
	if (E_INVALIDARG == this->lpXmlDoc->selectNodes(Path, &lpNodeList)) {
		SysFreeString(Path);
		lpNodeList->Release();
		return NULL;
	}
	lpNodeList->get_length(&Length);
	SysFreeString(Path);
	return lpNodeList;
}

long MSXMLRead::CheckLength(const std::basic_string<TCHAR> NodePath) {
	long Length = 0;
	IXMLDOMNodeList* list = XmlSetNodeList(this->CommonPath + NodePath, Length);
	if (NULL == list) {
		list->Release();
		throw std::runtime_error("xml read failed");
	}
	list->Release();
	return Length;
}

void MSXMLRead::LoadFromFile(const std::basic_string<TCHAR> NodePath) {
	Node node;
	node.NodePath = this->CommonPath + NodePath;
	node.NodePath.resize(std::char_traits<TCHAR>::length(node.NodePath.c_str()));
	node.NodeList = this->XmlSetNodeList(NodePath, node.Length);
	this->Data.emplace_back(node);
}

void MSXMLRead::ChangeCommonPath(const std::basic_string<TCHAR> NewRoot) {
	this->clear();
	this->CommonPath = NewRoot;
}

Node MSXMLRead::operator [] (const std::basic_string<TCHAR> NodePath) const {
	for (const auto& i : this->Data) if (i.NodePath == this->CommonPath + NodePath) return i;
	throw std::runtime_error(
#if defined(UNICODE)
		Win32LetterConvert::WStringToString(this->CommonPath + NodePath)
#else
		this->CommonPath + NodePath
#endif
		+ " : not found such node.");
}
