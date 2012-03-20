#pragma once
#include <vector>
#include <wtypes.h>
#include <string>

#ifdef LAB_PRA_EXPORTS
#define LAB_PRA_API __declspec(dllexport)
#else
#define LAB_PRA_API __declspec(dllimport)
#endif

class LAB_PRA_API IRegistryReader {
public:

    virtual bool GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);

    virtual long GetLastError(void);

    virtual bool isNoError(void);

    virtual bool ReadBinary(LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result);

    virtual DWORD ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName);

    virtual std::basic_string<TCHAR> ReadString(LPCTSTR subKeyName, LPCTSTR parameterName);

    virtual ~IRegistryReader(void);
};

