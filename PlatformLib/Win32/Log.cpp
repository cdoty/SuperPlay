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

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "Log.h"
#include "StoragePath.h"

NAMESPACE(SPlay)

// Log file and title
static const char*	gsc_szLogTitle	= "Log Title";
static const char*	gsc_szLogFile	= "Log.html";

Log*	Log::m_pInstance	= NULL;

Log::Log()
{
	createLog();
}

Log::~Log()
{
	closeLog();

	m_strLogStrings.clear();
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

	vsprintf_s(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogMessage, szString);
}

void Log::logWarning(const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf_s(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogWarning, szString);
}

void Log::logError(const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf_s(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(LogError, szString);
}

void Log::log(LogType _eType, const char* _szFormat, ...)
{
	va_list	sArgs;
	char	szString[256];

	va_start(sArgs, _szFormat);

	vsprintf_s(szString, _szFormat, sArgs);

	va_end(sArgs);

	logString(_eType, szString);
}

void Log::createLog()
{
	// Erase any existing log.
	Storage::deleteFile(gsc_szLogFile);

	writeHTMLStart();

	log(LogMessage, "Logging started");
}

void Log::closeLog()
{
	log(LogMessage, "Logging ended");
	
	writeHTMLEnd();

	char	szTempPath[MAX_PATH];
	char	szLogPath[MAX_PATH];

	GetTempPath(MAX_PATH, szTempPath);

	sprintf(szLogPath, "%s%s", szTempPath, gsc_szLogFile);

	// Log messages to log file.
	Storage*	pStorage	= new Storage();

	if (true == pStorage->create(szLogPath))
	{
		size_t	t_c	= m_strLogStrings.size();
		
		for (size_t iLoop = 0; iLoop < t_c; ++iLoop)
		{
			pStorage->writeString(m_strLogStrings[iLoop].c_str());
		}

		pStorage->close();
	}

	delete	pStorage;
}

void Log::logString(LogType _eType, const tinystl::string& _strString)
{
	logDateTime();

	switch (_eType)
	{
		case LogError:
			m_strLogStrings.push_back("<FONT COLOR=#FF0000>Error: ");

			break;

		case LogWarning:
			m_strLogStrings.push_back("<FONT COLOR=#FFFF00>Warning: ");

			break;

		case LogMessage:
		default:
			m_strLogStrings.push_back("<FONT COLOR=#00FF00>");

			break;
	}

	m_strLogStrings.push_back(_strString);
	m_strLogStrings.push_back("</FONT><BR>");

#if defined WIN32 && defined _DEBUG
	OutputDebugString(_strString.c_str());
	OutputDebugString("\n");
#endif
}

void Log::logDateTime()
{
	char	szString[256];

	m_strLogStrings.push_back("<FONT COLOR=#FFFFFF>[");

	GetTimeFormat(LOCALE_USER_DEFAULT, 0, NULL, "hh':'mm':'ss tt", szString, sizeof(szString));

	m_strLogStrings.push_back(szString);
	m_strLogStrings.push_back("]</FONT> ");
}

void Log::writeHTMLStart()
{
	m_strLogStrings.push_back("<HTML><HEAD><TITLE>");
	m_strLogStrings.push_back(gsc_szLogTitle);
	m_strLogStrings.push_back("</TITLE></HEAD><BODY BGCOLOR=#00001F>");
}

void Log::writeHTMLEnd()
{
	m_strLogStrings.push_back("</BODY></HTML>\n");
}

ENDNAMESPACE
