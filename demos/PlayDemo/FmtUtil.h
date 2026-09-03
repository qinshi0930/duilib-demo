#pragma once

std::string GetAppPathA();

std::wstring GetAppPathW();

//ascii תΪ unicode
std::wstring StringToWString(std::string str);

//unicode תΪ ascii
std::string WStringToString(std::wstring str);

//utf8 ת Unicode
std::wstring UTF8ToWString(std::string str);

//Unicode ת Utf8
std::string WStringToUTF8(std::wstring str);

//ascii ת Utf8
std::string GBKToUTF8(std::string strGBK);

//utf-8 ת ascii
std::string UTF8ToGBK(std::string strUTF8);

std::string FormatString(const char* lpcszFormat, ...);

std::wstring FormatWstring(const wchar_t* lpcwszFormat, ...);

std::string replace(std::string str, std::string old_value, std::string new_value);

std::string GetMidString(std::string strSource, std::string strLeft, std::string strRight);
