// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdio.h>
#include <stdarg.h>

#include "Log.h"

NAMESPACE(SPlay)

// Log file and title
static const char*	gsc_szLogTitle	= "Log Title";

Log*	Log::m_pInstance	= NULL;

Log::Log()
{
	createLog();
}

Log::~Log()
{
	closeLog();
}

Log* Log::instance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance	= new Log();
	}
	
	return	m_pInstance;	
}

void Log::deleteInstance()
{
	delete	m_pInstance;
		
	m_pInstance	= NULL;
}

void Log::logMessage(const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogMessage, szString);
}

void Log::logWarning(const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogWarning, szString);
}

void Log::logError(const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogError, szString);
}

void Log::log(LogType _eType, const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(_eType, szString);
}

void Log::createLog()
{
	writeHTMLStart();

	log(LogMessage, "Logging started");
}

void Log::closeLog()
{
	log(LogMessage, "Logging ended");
	
	writeHTMLEnd();
}

void Log::logString(LogType _eType, const tinystl::string& _strString)
{
	printf("%s\n", _strString.c_str());
}

void Log::logDateTime()
{
}

void Log::writeHTMLStart()
{
}

void Log::writeHTMLEnd()
{
}

ENDNAMESPACE
