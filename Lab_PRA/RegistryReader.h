#pragma once
#include "IRegistryReader.h"

#ifdef LAB_PRA_EXPORTS
#define LAB_PRA_API __declspec(dllexport)
#else
#define LAB_PRA_API __declspec(dllimport)
#endif

class LAB_PRA_API RegistryReader :
	public IRegistryReader
{
public:
	RegistryReader(HKEY hKey);

	bool GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);

	virtual long GetLastError( void );

	virtual bool isNoError( void );

	~RegistryReader(void);

private:
	HKEY currentKeyHandle;
	long lastError;
	static const size_t MAX_KEY_LENGTH = 255;
	static const size_t MAX_VALUE_NAME = 16383;

	void openKey( HKEY hkey, LPCTSTR lpName ); 
};
