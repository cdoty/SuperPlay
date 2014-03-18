// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <UILib.h>

using namespace DuiLib;

class DuiUtilities
{
	public:
		// Select item
		static void selectItem(CComboBoxUI* _pCombo, int _iIndex);
		static void selectItem(CComboBoxUI* _pComboBox, const std::string& _strSelected);

		// Setup combo box
		static void setupComboBox(CComboBoxUI* _pComboBox, int _iItemWidth);

		// Setup option
		static void setupOption(COptionUI* _pOption, int _iSize);
};
