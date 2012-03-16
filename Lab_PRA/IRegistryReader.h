#pragma once
#include <vector>
#include <wtypes.h>

#ifdef LAB_PRA_EXPORTS
#define LAB_PRA_API __declspec(dllexport)
#else
#define LAB_PRA_API __declspec(dllimport)
#endif

class LAB_PRA_API IRegistryReader
{
public:

	virtual bool GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);

	virtual long GetLastError(void);

	virtual bool isNoError(void);
	
	virtual ~IRegistryReader(void);
};

