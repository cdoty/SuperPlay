// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "DuiUtilities.h"

void DuiUtilities::selectItem(CComboBoxUI* _pCombo, int _iIndex)
{
	if (_pCombo != NULL)
	{
		if (-1 == _iIndex)
		{
			int	iCount	= _pCombo->GetCount();

			if (iCount > 0)
			{
				iCount--;
			}

			_pCombo->SelectItem(iCount);
		}

		else
		{
			 if (_iIndex < _pCombo->GetCount())
			 {
				_pCombo->SelectItem(_iIndex);
			}
		}
	}
}

void DuiUtilities::selectItem(CComboBoxUI* _pComboBox, const std::string& _strSelected)
{
	if (_pComboBox != NULL)
	{
		int	t_c	= _pComboBox->GetCount();

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			if (_pComboBox->GetItemAt(iLoop)->GetText() == _strSelected.c_str())
			{
				_pComboBox->SelectItem(iLoop);

				break;
			}
		}
	}
}

void DuiUtilities::setupComboBox(CComboBoxUI* _pComboBox, int _iItemWidth)
{
	// Set images
	_pComboBox->SetItemBkImage("file='ComboItemNormal.png' corner='1,1,1,1'");
	_pComboBox->SetSelectedItemImage("file='ComboItemSelected.png' corner='1,1,1,1'");
	_pComboBox->SetHotItemImage("file='ComboItemHover.png' corner='1,1,1,1'");
	_pComboBox->SetNormalImage("file='ComboNormal.png' corner='5,4,28,4'");
	_pComboBox->SetHotImage("file='ComboHover.png' corner='5,4,28,4'");
	_pComboBox->SetPushedImage("file='ComboClick.png' corner='5,4,28,4'");
	_pComboBox->SetDisabledImage("file='ComboInactive.png' corner='5,4,28,4'");

	// Set colors
	_pComboBox->SetItemTextColor(0xFF000000);
	_pComboBox->SetSelectedItemTextColor(0xFF000000);
	_pComboBox->SetSelectedItemBkColor(0xFFC1E3FF);
	_pComboBox->SetHotItemTextColor(0xFF000000);
	_pComboBox->SetHotItemBkColor(0xFFE9F5FF);
	_pComboBox->SetDisabledItemTextColor(0xFFCCCCCC);
	_pComboBox->SetDisabledItemBkColor(0xFFFFFFFF);

	// Set sizes
	_pComboBox->SetFixedWidth(_iItemWidth);

	SIZE	size	= {0, 90};

	_pComboBox->SetDropBoxSize(size);
	
	RECT	rctPadding	= {2, 3, 2, 3};

	_pComboBox->SetPadding(rctPadding);
	
	RECT	rctTextPadding	= {2, 1, 2, 1};

	_pComboBox->SetItemTextPadding(rctTextPadding);

	// Set font
	_pComboBox->SetItemFont(0);
}

void DuiUtilities::setupOption(COptionUI* _pOption, int _iSize)
{
	// Set images
	_pOption->SetFixedWidth(_iSize);
	_pOption->SetFixedHeight(_iSize);
	_pOption->SetMinWidth(_iSize);
	_pOption->SetMinHeight(_iSize);
	_pOption->SetMaxWidth(_iSize);
	_pOption->SetMaxHeight(_iSize);

	// Set images
	_pOption->SetNormalImage("file='OptionNormal.png'");
	_pOption->SetHotImage("file='OptionHover.png'");
	_pOption->SetSelectedImage("file='OptionClick.png'");
	_pOption->SetDisabledImage("file='OptionInactive.png'");
}

