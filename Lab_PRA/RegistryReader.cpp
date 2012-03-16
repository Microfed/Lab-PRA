#include "StdAfx.h"
#include <tchar.h>
#include <windows.h>
#include "RegistryReader.h"

LAB_PRA_API RegistryReader::RegistryReader(HKEY hKey)
{
	openKey(hKey, NULL);
}


LAB_PRA_API RegistryReader::~RegistryReader(void)
{
	if(&currentKeyHandle != nullptr){
		RegCloseKey(currentKeyHandle);
	}
}

LAB_PRA_API bool RegistryReader::GetKeysEnum( LPCTSTR lpName, std::vector<TCHAR>& result )
{
	size_t i = 0;
	long retCode = ERROR_SUCCESS;
	DWORD    cbName = 0;
	TCHAR    achKey[MAX_KEY_LENGTH]; 
	FILETIME ftLastWriteTime; 

	if(*lpName != NULL)
	{
		openKey(currentKeyHandle, lpName);
	}

	if (&currentKeyHandle != nullptr && this->isNoError())
	{
		while (retCode == ERROR_SUCCESS)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(
				currentKeyHandle, // дескриптор перечисляемого ключа
				i, // индекс перечисляемого подключа 
				achKey, // адрес буфера для имени подключа
				&cbName, // адрес размера буфера подключа 
				NULL, // зарезервировано 
				NULL, // адрес буфера для имени класса 
				NULL, // адрес размера буфера для имени класса
				&ftLastWriteTime // адрес для времени последней записи ключа
				);

			++i;

			if (retCode == ERROR_SUCCESS) 
			{
				result.push_back(*achKey);
			}
		}

		return true;
	} 
	else
	{
		return false;
	}
}

LAB_PRA_API long RegistryReader::GetLastError( void )
{
	return lastError;
}

LAB_PRA_API bool RegistryReader::isNoError( void )
{
	return lastError == ERROR_SUCCESS;
}

void RegistryReader::openKey( HKEY hkey, LPCTSTR lpName )
{
	lastError = RegOpenKeyEx(
		hkey,	// дескриптор указанного ключа
		lpName,	// адрес имени открываемого подключа
		NULL,	// зарезервировано
		KEY_READ,	// маска доступа безопасности
		&currentKeyHandle 	// адрес дескриптора открытого ключа
		);
}
