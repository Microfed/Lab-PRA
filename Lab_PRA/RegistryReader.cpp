/**
 @file	RegistryReader.cpp

 @brief	Implements the registry reader class.
 */
 
#include "StdAfx.h"
#include <tchar.h>
#include <windows.h>
#include "RegistryReader.h"

/**
 @typedef	std::basic_string<TCHAR> tstring

 @brief	Defines an alias representing the tstring.
 */
typedef std::basic_string<TCHAR> tstring;

LAB_PRA_API RegistryReader::RegistryReader(HKEY hKey) {
    openKey(hKey, NULL);
}


LAB_PRA_API RegistryReader::~RegistryReader(void) {
    closeKey();
}

LAB_PRA_API bool RegistryReader::GetKeysEnum( LPCTSTR lpName, std::vector<TCHAR>& result ) {
	size_t i = 0;
	long retCode = ERROR_SUCCESS;
	DWORD    cbName = 0;
	TCHAR    achKey[MAX_KEY_LENGTH];
	FILETIME ftLastWriteTime;

    if(lpName != NULL) {
        openKey(currentKeyHandle, lpName);
    }

    if (&currentKeyHandle != nullptr && this->isNoError()) {
        while (retCode == ERROR_SUCCESS) {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(
                          currentKeyHandle,// ���������� �������������� �����
                          i,               // ������ �������������� ��������
                          achKey,          // ����� ������ ��� ����� ��������
                          &cbName,         // ����� ������� ������ ��������
                          NULL,            // ���������������
                          NULL,            // ����� ������ ��� ����� ������
                          NULL,            // ����� ������� ������ ��� ����� ������
                          &ftLastWriteTime // ����� ��� ������� ��������� ������ �����
                      );

            ++i;

            if (retCode == ERROR_SUCCESS) {
                result.push_back(*achKey);
            }
        }

        return true;
    } else {
        return false;
    }
}

LAB_PRA_API long RegistryReader::GetLastError( void ) {
    return lastError;
}

LAB_PRA_API bool RegistryReader::isNoError( void ) {
    return lastError == ERROR_SUCCESS;
}

void RegistryReader::openKey( HKEY hkey, LPCTSTR lpName ) {
    closeKey();

    lastError = RegOpenKeyEx(
                    hkey,               // ���������� ���������� �����
                    lpName,             // ����� ����� ������������ ��������
                    NULL,               // ���������������
                    KEY_READ,           // ����� ������� ������������
                    &currentKeyHandle   // ����� ����������� ��������� �����
                );
}

void RegistryReader::closeKey() {
    if(&currentKeyHandle != nullptr) {
        RegCloseKey(currentKeyHandle);
    }
}

bool RegistryReader::ReadBinary( LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result ) {
    PBYTE pbBuff;
    DWORD cBuff = 0;
    DWORD Type = 0;

    if(subKeyName != NULL) {
        openKey(currentKeyHandle, subKeyName);
    }

    if(&currentKeyHandle != NULL && this->isNoError()) {
        lastError = RegQueryValueEx(currentKeyHandle,parameterName,NULL,NULL,NULL,&cBuff);

        if (this->isNoError()) {
            if(cBuff > 1) {
                if((pbBuff=new BYTE [cBuff]) == NULL) return false;

                // ��������� ���������� �� ���������
                lastError = RegQueryValueEx(
                                // ��������� ��������� �������
                                currentKeyHandle,
                                // ��������� �� �-������, ���������� �������� ���������,
                                // � ������� ���������� ����������
                                parameterName,
                                // �������������� - NULL
                                NULL,
                                // ��������� �� ����������, ������� �������� ��� ������,
                                // ����������� � ���������
                                &Type,
                                // ��������� �� ������, ���������� ������ ���������
                                pbBuff,
                                // ��������� �� ����������, ������� ���������� ������ ������,
                                // ������������ ������ �� ���������, � ������
                                &cBuff
                            );

                for(size_t i = 0; i < cBuff; i++) {
                    if (pbBuff[i]) {
                        result.push_back(pbBuff[i]);
                    }
                }
                return true;
            }
        }
    }

    return false;
}


DWORD RegistryReader::ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName) {
    DWORD dwValue = 0;
    DWORD dwValueSize = sizeof(DWORD);
    DWORD dwType = REG_DWORD;

    if(subKeyName != NULL) {
        openKey(currentKeyHandle, subKeyName);
    }

    if(&currentKeyHandle != NULL && this->isNoError()) {
        lastError = RegQueryValueEx(
                        currentKeyHandle,
                        parameterName,
                        NULL,
                        &dwType,
                        (PBYTE)&dwValue,
                        &dwValueSize
                    );
    }

    return dwValue;
}

std::basic_string<TCHAR> RegistryReader::ReadString(LPCTSTR subKeyName, LPCTSTR parameterName) {
	DWORD dwDataSize = 0;
	DWORD dwType = REG_SZ;
	tstring stringValue;

    if(subKeyName != NULL) {
        openKey(currentKeyHandle, subKeyName);
    }

    if(&currentKeyHandle != NULL && this->isNoError()) {
        lastError = RegQueryValueEx(currentKeyHandle, parameterName, 0, &dwType, (PBYTE)NULL, &dwDataSize);

        if(isNoError()) {
            stringValue.resize(dwDataSize + 1);
            LPCTSTR pStrValue = stringValue.c_str();

            lastError = RegQueryValueEx(currentKeyHandle, parameterName, 0, &dwType, (PBYTE)pStrValue, &dwDataSize);
        }
    }

    return stringValue;
}
