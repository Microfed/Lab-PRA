/**
 @file	RegistryReader.h

 @brief	Описывает класс RegistryReader.
		Класс содержит методы для чтения значений параметров ключей реестра
		и перечисления существующих ключей.
 */
 
#pragma once
#include "IRegistryReader.h"

#ifdef LAB_PRA_EXPORTS
#define LAB_PRA_API __declspec(dllexport)
#else
#define LAB_PRA_API __declspec(dllimport)
#endif

/**
 @class	RegistryReader

 @brief	Класс читатель значений реестра.

 @author	Microfed
 @date	24.03.2012
 */
class LAB_PRA_API RegistryReader :
    public IRegistryReader {
public:

    /**
     @fn	RegistryReader::RegistryReader(HKEY hKey);
    
     @brief	Constructor.
    
     @author	Microfed
     @date	24.03.2012
    
     @param	hKey	Дескриптор ключа. Может принимать любое из
					предопределенных значений HKEY.
     */
    RegistryReader(HKEY hKey);

    /**
     @fn	virtual bool RegistryReader::GetKeysEnum(LPCTSTR lpName, std::vector<TCHAR>& result);
    
     @brief	Получает список ключей реестра.
    
     @author	Microfed
     @date	24.03.2012
    
     @param	lpName			  	Имя ключа (раздела).
     @param [in,out]	result	Вектор строк, в который будет записан результат.
    
     @return	true if it succeeds, false if it fails.
     */
    bool GetKeysEnum(LPCTSTR lpName, std::vector<std::basic_string<TCHAR> >& result );

    /**
     @fn	virtual long RegistryReader::GetLastError(void);
    
     @brief	Gets the last error.
    
     @author	Microfed
     @date	24.03.2012
    
     @return	The last error.
     */
    long GetLastError( void );

	/**
     @fn	virtual bool RegistryReader::isNoError(void);

     @brief	Проверяет, не произошло ли ошибок в ходе
			прошлых операций.

     @author	Microfed
     @date	24.03.2012

     @return	true if no error, false if not.
     */
    bool isNoError( void );

	/**
	 @fn	virtual bool RegistryReader::ReadBinary(LPCTSTR subKeyName, LPCTSTR parameterName,
	 		std::vector<BYTE>& result);

	 @brief	Читает бинарное значение параметра ключа.

	 @author	Microfed
	 @date	24.03.2012

	 @param	subKeyName		  	Name of the sub key.
	 @param	parameterName	  	Name of the parameter.
	 @param [in,out]	result	Вектор байтов, в который будет записан результат.

	 @return	true if it succeeds, false if it fails.
	 */
    bool ReadBinary(LPCTSTR subKeyName, LPCTSTR parameterName, std::vector<BYTE>& result);

	/**
     @fn	virtual DWORD RegistryReader::ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName);

     @brief	Reads a double word.

     @author	Microfed
     @date	24.03.2012

     @param	subKeyName   	Name of the sub key.
     @param	parameterName	Name of the parameter.

     @return	The double word.
     */
    DWORD ReadDWORD(LPCTSTR subKeyName, LPCTSTR parameterName);

	/**
     @fn	virtual std::basic_string<TCHAR> RegistryReader::ReadString(LPCTSTR subKeyName,
     		LPCTSTR parameterName);

     @brief	Reads a string.

     @author	Microfed
     @date	24.03.2012

     @param	subKeyName   	Name of the sub key.
     @param	parameterName	Name of the parameter.

     @return	The string.
     */
    std::basic_string<TCHAR> ReadString(LPCTSTR subKeyName, LPCTSTR parameterName);

	/**
     @fn	virtual RegistryReader::~RegistryReader(void);

     @brief	Destructor.

     @author	Microfed
     @date	24.03.2012
     */
    ~RegistryReader(void);

private:

    /**
     @summary	The current key handle.
     */
    HKEY currentKeyHandle;

    /**
     @summary	The last error.
     */
    long lastError;

    /**
     @summary	Maximum length of the  key.
     */
    static const size_t MAX_KEY_LENGTH = 255;

    /**
     @summary	Maximum length of the value name.
     */
    static const size_t MAX_VALUE_NAME = 16383;

	/**
	 @fn	void RegistryReader::openKey( HKEY hkey, LPCTSTR lpName );
	
	 @brief	Opens a key.
	
	 @author	Microfed
	 @date	24.03.2012
	
	 @param	hkey  	Handle of the hkey.
	 @param	lpName	The subkey name.
	 */
	void openKey( HKEY hkey, LPCTSTR lpName );

    /**
     @fn	void RegistryReader::closeKey();
    
     @brief	Closes the key.
    
     @author	Microfed
     @date	24.03.2012
     */
    void closeKey();
};

