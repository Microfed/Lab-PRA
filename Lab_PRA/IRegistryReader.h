/**
 @file	IRegistryReader.h

 @brief	Declares the IRegistryReader interface.
 */
 
#pragma once
#include <vector>
#include <wtypes.h>
#include <string>

#ifdef LAB_PRA_EXPORTS
#define LAB_PRA_API __declspec(dllexport)
#else
#define LAB_PRA_API __declspec(dllimport)
#endif

/**
 @class	IRegistryReader

 @brief	Интерфейс класса-читателя значений реестра.

 @author	Microfed
 @date	24.03.2012
 */
class LAB_PRA_API IRegistryReader {
public:

    /**
     @fn	virtual bool IRegistryReader::GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);
    
     @brief	Получает список ключей реестра.
    
     @author	Microfed
     @date	24.03.2012
    
     @param	lpName			  	Имя ключа (раздела).
     @param [in,out]	result	Вектор строк, в который будет записан результат.
    
     @return	true if it succeeds, false if it fails.
     */
    virtual bool GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);

    /**
     @fn	virtual long IRegistryReader::GetLastError(void);
    
     @brief	Gets the last error.
    
     @author	Microfed
     @date	24.03.2012
    
     @return	The last error.
     */
    virtual long GetLastError(void);

    /**
     @fn	virtual bool IRegistryReader::isNoError(void);
    
     @brief	Проверяет, не произошло ли ошибок в ходе
			прошлых операций.
    
     @author	Microfed
     @date	24.03.2012
    
     @return	true if no error, false if not.
     */
    virtual bool isNoError(void);

	/**
	 @fn	virtual bool IRegistryReader::ReadBinary(LPCTSTR subKeyName, LPCTSTR parameterName,
	 		std::vector<BYTE>& result);
	
	 @brief	Читает бинарное значение параметра ключа.
	
	 @author	Microfed
	 @date	24.03.2012
	
	 @param	subKeyName		  	Name of the sub key.
	 @param	parameterName	  	Name of the parameter.
	 @param [in,out]	result	Вектор байтов, в который будет записан результат.
	
	 @return	true if it succeeds, false if it fails.
	 */
	virtual bool ReadBinary(LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result);

    /**
     @fn	virtual DWORD IRegistryReader::ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName);
    
     @brief	Reads a double word.
    
     @author	Microfed
     @date	24.03.2012
    
     @param	subKeyName   	Name of the sub key.
     @param	parameterName	Name of the parameter.
    
     @return	The double word.
     */
    virtual DWORD ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName);

    /**
     @fn	virtual std::basic_string<TCHAR> IRegistryReader::ReadString(LPCTSTR subKeyName,
     		LPCTSTR parameterName);
    
     @brief	Reads a string.
    
     @author	Microfed
     @date	24.03.2012
    
     @param	subKeyName   	Name of the sub key.
     @param	parameterName	Name of the parameter.
    
     @return	The string.
     */
    virtual std::basic_string<TCHAR> ReadString(LPCTSTR subKeyName, LPCTSTR parameterName);

    /**
     @fn	virtual IRegistryReader::~IRegistryReader(void);
    
     @brief	Destructor.
    
     @author	Microfed
     @date	24.03.2012
     */
    virtual ~IRegistryReader(void);
};

