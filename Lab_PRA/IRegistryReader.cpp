#include "StdAfx.h"
#include "IRegistryReader.h"

LAB_PRA_API IRegistryReader::~IRegistryReader( void )
{

}

LAB_PRA_API bool IRegistryReader::GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result )
{
	return true;
}

LAB_PRA_API long IRegistryReader::GetLastError( void )
{
	return 0L;
}

bool IRegistryReader::isNoError( void )
{
	return true;
}

bool IRegistryReader::GetValue( LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result )
{
	return false;
}
