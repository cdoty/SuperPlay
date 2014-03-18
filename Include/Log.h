// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>
#include <TinySTL/vector.h>
 
#include "Macros.h"

NAMESPACE(SPlay)

class Log
{
	public:
		// Destructor
		~Log();

		// Log message
		void logMessage(const char* _szFormat, ...);

		// Log warning
		void logWarning(const char* _szFormat, ...);

		// Log error
		void logError(const char* _szFormat, ...);

		// Get instance
		static Log* instance();
		
		// Delete instance
		static void deleteInstance();
		
	protected:
		// Log types
		enum LogType
		{
			LogMessage,	// Log a message
			LogWarning,	// Log a warning
			LogError	// Log an error
		};

		// Log instance
		static Log*							m_pInstance;
		
		// Log strings
		tinystl::vector<tinystl::string>	m_strLogStrings;

		// Constructor
		Log();
		
		// Logs a message to a log file and debug console on Windows
		void log(LogType _eType, const char* _szFormat, ...);

		// Create the log
		void createLog();

		// Close the log
		void closeLog();

		// Log string
		void logString(LogType _eType, const tinystl::string& _strString);

		// Log current date and time
		void logDateTime();

		// Write HTML start
		void writeHTMLStart();

		// Write HTML end
		void writeHTMLEnd();
};

ENDNAMESPACE
