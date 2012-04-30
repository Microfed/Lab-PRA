#include "stdafx.h"
#include <tchar.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "../Lab_PRA/IRegistryReader.h"
#include "../Lab_PRA/RegistryReader.h"

typedef std::basic_string<TCHAR> tstring;

TEST(RegistryReader_GetKeysEnum, ShouldReturnMoreThanOneElementForValidPredefinedKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring tstr = _T("");
    LPCTSTR ptsz = tstr.c_str();
    std::vector<tstring> result(0);
    bool success = reader->GetKeysEnum(ptsz, result);

    EXPECT_GT(result.size(), 1);
    EXPECT_TRUE(success);
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnMoreThanOneElementForValidSubkey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring tstr = _T("Software");
    LPCTSTR ptsz = tstr.c_str();
    std::vector<tstring> result(0);
    reader->GetKeysEnum(ptsz, result);

    EXPECT_GT(result.size(), 1);
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnZeroElementForInvalidSubkey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring tstr = _T("247634_invalid subkey");
    LPCTSTR ptsz = tstr.c_str();
    std::vector<tstring> result(0);
    reader->GetKeysEnum(ptsz, result);

    EXPECT_EQ(0, result.size());
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnCorrectElementsForValidSubkey_TestForRegistryReader) {
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	tstring tstr = _T("TestForRegistryReader");
	LPCTSTR ptsz = tstr.c_str();
	std::vector<tstring> result(0);
	reader->GetKeysEnum(ptsz, result);

	std::vector<tstring> strExpected;
	strExpected.push_back(_T("key1"));
	strExpected.push_back(_T("key2"));
	strExpected.push_back(_T("key3"));

	EXPECT_GT(result.size(), 1);
	EXPECT_STREQ(strExpected[0].c_str(), result[0].c_str());
	EXPECT_STREQ(strExpected[1].c_str(), result[1].c_str());
	EXPECT_STREQ(strExpected[2].c_str(), result[2].c_str());
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnZeroElementForInvalidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
    tstring tstr = _T("");
    LPCTSTR ptsz = tstr.c_str();
    std::vector<tstring> result(0);
    reader->GetKeysEnum(ptsz, result);

    EXPECT_EQ(result.size(), 0);
}

TEST(RegistryReader_GetLastError, ShouldReturnNonZeroForInvalidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
    long actual = reader->GetLastError();

    EXPECT_NE(ERROR_SUCCESS, actual);
}

TEST(RegistryReader_GetLastError, ShouldReturnZeroForValidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    long actual = reader->GetLastError();

    EXPECT_EQ(ERROR_SUCCESS, actual);
}

TEST(RegistryReader_isNoError, ShouldReturnNoErrorForValidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    bool actual = reader->isNoError();

    EXPECT_TRUE(actual);
}

TEST(RegistryReader_isNoError, ShouldReturnErrorForInvalidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
    bool actual = reader->isNoError();

    EXPECT_FALSE(actual);
}

TEST(RegistryReader_GetValue, ShouldReturnFalseForInvalidKey) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
    std::vector<BYTE> result(0);
    bool actual = reader->ReadBinary(NULL, NULL, result);

    EXPECT_FALSE(actual);
}

TEST(RegistryReader_ReadBinary, ShouldReturnDefaultValueForValidSubkey_TestForRegistryReader) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring keyName = _T("TestForRegistryReader");
    LPCTSTR pKeyName = keyName.c_str();
    std::vector<BYTE> result(0);
    reader->ReadBinary(pKeyName, NULL, result);
    TCHAR* expected = _T("defaultValue");
    BYTE* actual = result.data();

    EXPECT_GT(result.size(), 1);
    EXPECT_EQ(expected[0], actual[0]);
}

TEST(RegistryReader_ReadDWORD, ShouldReturnDWORDValueForValidSubkey_TestForRegistryReader) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring keyName = _T("TestForRegistryReader");
    LPCTSTR pKeyName = keyName.c_str();
    tstring parName = _T("Reg_dword");
    LPCTSTR pParName = parName.c_str();
    DWORD result = reader->ReadDWORD(pKeyName, pParName);

    EXPECT_TRUE(result);
    EXPECT_FALSE(reader->GetLastError());
}

TEST(RegistryReader_ReadString, ShouldReturnStringValueForValidSubkey_TestForRegistryReader) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring keyName = _T("TestForRegistryReader");
    LPCTSTR pKeyName = keyName.c_str();
    tstring parName = _T("Reg_sz");
    LPCTSTR pParName = parName.c_str();
    const TCHAR* result = reader->ReadString(pKeyName, pParName).c_str();
    tstring strExpected = _T("reg_sz_value");

    EXPECT_STREQ(strExpected.c_str(), result);
    EXPECT_FALSE(reader->GetLastError());
}

TEST(RegistryReader_ReadString, ShouldReturnMultiStringValueForValidSubkey_TestForRegistryReader) {
    std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
    tstring keyName = _T("TestForRegistryReader");
    LPCTSTR pKeyName = keyName.c_str();
    tstring parName = _T("Reg_multi_sz");
    LPCTSTR pParName = parName.c_str();
    const TCHAR* result = reader->ReadString(pKeyName, pParName).c_str();
    tstring strExpected = _T("reg_multi_sz");

    EXPECT_STREQ(strExpected.c_str(), result);
    EXPECT_FALSE(reader->GetLastError());
}