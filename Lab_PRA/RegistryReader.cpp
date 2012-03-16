#include "StdAfx.h"
#include <tchar.h>
#include <windows.h>
#include "RegistryReader.h"

LAB_PRA_API RegistryReader::RegistryReader(HKEY hKey){
	openKey(hKey, NULL);
}


LAB_PRA_API RegistryReader::~RegistryReader(void){
	closeKey();
}

LAB_PRA_API bool RegistryReader::GetKeysEnum( LPCTSTR lpName, std::vector<TCHAR>& result ){
	size_t i = 0;
	long retCode = ERROR_SUCCESS;
	DWORD    cbName = 0;
	TCHAR    achKey[MAX_KEY_LENGTH]; 
	FILETIME ftLastWriteTime; 

	if(lpName != NULL){
		openKey(currentKeyHandle, lpName);
	}

	if (&currentKeyHandle != nullptr && this->isNoError()){
		while (retCode == ERROR_SUCCESS){
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(
				currentKeyHandle,// дескриптор перечисляемого ключа
				i,				 // индекс перечисляемого подключа 
				achKey,			 // адрес буфера для имени подключа
				&cbName,		 // адрес размера буфера подключа 
				NULL,			 // зарезервировано 
				NULL,			 // адрес буфера для имени класса 
				NULL,			 // адрес размера буфера для имени класса
				&ftLastWriteTime // адрес для времени последней записи ключа
				);

			++i;

			if (retCode == ERROR_SUCCESS){
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

LAB_PRA_API long RegistryReader::GetLastError( void ){
	return lastError;
}

LAB_PRA_API bool RegistryReader::isNoError( void ){
	return lastError == ERROR_SUCCESS;
}

void RegistryReader::openKey( HKEY hkey, LPCTSTR lpName ){
	closeKey();

	lastError = RegOpenKeyEx(
		hkey,				// дескриптор указанного ключа
		lpName,				// адрес имени открываемого подключа
		NULL,				// зарезервировано
		KEY_READ,			// маска доступа безопасности
		&currentKeyHandle 	// адрес дескриптора открытого ключа
		);
}

void RegistryReader::closeKey(){
	if(&currentKeyHandle != nullptr){
		RegCloseKey(currentKeyHandle);
	}
}

bool RegistryReader::GetValue( LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result){
	PBYTE pbBuff;
	DWORD cBuff=0;
	DWORD Type=0;

	if(subKeyName != NULL){
		openKey(currentKeyHandle, subKeyName);
	}

	if(&currentKeyHandle != NULL && this->isNoError()){
		lastError = RegQueryValueEx(currentKeyHandle,parameterName,NULL,NULL,NULL,&cBuff);

		if (this->isNoError())
		{
			if(cBuff > 1){
				if((pbBuff=new BYTE [cBuff])==NULL) return false;

				// Считываем информацию из параметра
				RegQueryValueEx(
					currentKeyHandle,	// Описатель открытого раздела
					parameterName,		// Указатель на С-строку, содержащую название параметра,
					// о котором получается информация
					NULL,	// Зарезервирован - NULL
					&Type,	// Указатель на переменную, которая получает тип данных,
					// сохраненных в параметре
					pbBuff, // Указатель на массив, получающий данные параметра
					&cBuff	// Указатель на переменную, которая определяет размер буфера,
					// принимающего данные из параметра, в байтах
					);

				register int i;

				switch(Type){
				case(REG_SZ):
					for(i=0;i<cBuff;i++){
						if (pbBuff[i]){
							result.push_back(pbBuff[i]);
						}
					}
					return true;
					break;
				case(REG_MULTI_SZ):
					for(i=0;i<cBuff;i++){
						if (pbBuff[i]){
							result.push_back(pbBuff[i]);
						}
					}
					return true;
					break;
				case(REG_EXPAND_SZ):
					for(i=0;i<cBuff;i++){
						if (pbBuff[i]){
							result.push_back(pbBuff[i]);
						}
					}
					return true;
					break;
				}
			}
		}
	}

	return false;
}
