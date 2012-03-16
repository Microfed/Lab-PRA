#include "stdafx.h"
#include <string>
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <winerror.h>
#include "gtest/gtest.h"
#include "../Lab_PRA/IRegistryReader.h"
#include "../Lab_PRA/RegistryReader.h"

typedef std::basic_string<TCHAR> tstring;

TEST(RegistryReader_GetKeysEnum, ShouldReturnMoreThanOneElementForValidPredefinedKey)
{
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	tstring tstr = _T("");
	LPCTSTR ptsz = tstr.c_str();
	std::vector<TCHAR> result(0);
	bool success = reader->GetKeysEnum(ptsz, result);

	EXPECT_GT(result.size(), 1);
	EXPECT_TRUE(success);
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnMoreThanOneElementForValidSubkey)
{
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	tstring tstr = _T("Software");
	LPCTSTR ptsz = tstr.c_str();
	std::vector<TCHAR> result(0);
	reader->GetKeysEnum(ptsz, result);

	EXPECT_GT(result.size(), 1);
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnZeroElementForInvalidSubkey)
{
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	tstring tstr = _T("247634_invalid subkey");
	LPCTSTR ptsz = tstr.c_str();
	std::vector<TCHAR> result(0);
	reader->GetKeysEnum(ptsz, result);

	EXPECT_EQ(0, result.size());
}

TEST(RegistryReader_GetKeysEnum, ShouldReturnZeroElementForInvalidKey)
{
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
	tstring tstr = _T("");
	LPCTSTR ptsz = tstr.c_str();
	std::vector<TCHAR> result(0);
	reader->GetKeysEnum(ptsz, result);

	EXPECT_EQ(result.size(), 0);
}

TEST(RegistryReader_GetLastError, ShouldReturnNonZeroForInvalidKey){
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
	long actual = reader->GetLastError();

	EXPECT_NE(ERROR_SUCCESS, actual);
}

TEST(RegistryReader_GetLastError, ShouldReturnZeroForValidKey){
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	long actual = reader->GetLastError();

	EXPECT_EQ(ERROR_SUCCESS, actual);
}

TEST(RegistryReader_isNoError, ShouldReturnNoErrorForValidKey){
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(HKEY_CLASSES_ROOT));
	bool actual = reader->isNoError();

	EXPECT_TRUE(actual);
}

TEST(RegistryReader_isNoError, ShouldReturnErrorForInvalidKey){
	std::auto_ptr<IRegistryReader> reader(new RegistryReader(NULL));
	bool actual = reader->isNoError();

	EXPECT_FALSE(actual);
}