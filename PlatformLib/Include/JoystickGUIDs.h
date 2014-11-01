// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

enum GamePads
{
	// GameMon gamepad Model FT2E92
	// Button A: 4
	// Button B: 3
	// Button X: 2
	// Button Y: 1
	// Button L: 5
	// Button R: 6
	// Select: 7
	// Start: 8
	GAMEMON_GAMEPAD	= 0x2E9219FA,

	// Spin Master Model 47004(?)
	// Button A: 2
	// Button B: 3
	// Button X: 1
	// Button Y: 4
	// Button L: L1 (7)
	// Button R: R1 (8)
	// Select: Select (9)
	// Start: Start (10)
	SPIN_MASTER_GAMEPAD	= 0x00070810,
	TWIN_USB_GAMEPAD	= 0xe0010810,

	// Game Elements Model GGE900
	// Button A: 4
	// Button B: 3
	// Button X: 2
	// Button Y: 1
	// Button L: L1 (5)
	// Button R: R1 (6)
	// Select: Select (9)
	// Start: Start (10)
	// Game Elements Model GGE908
	// Philips Model SGC2909BB / 27
	// Button A: 2 (2)
	// Button B: 3 (3)
	// Button X: 2 (1)
	// Button Y: 3 (4)
	// Button L: 2 (5)
	// Button R: 3 (6)
	// Select: Esc (11)
	// Start: Enter (12)
	AXISPAD_GGE900_GAMEPAD			= 0x000305EF,
	GAME_ELEMENTS_GGE908_GAMEPAD	= 0x01070F30,
	PHILIPS_GGE909_GAMEPAD			= 0x010B0F30,

	// Afterglow PS3
	// Button A: O (3)
	// Button B: X (2)
	// Button X: Triangle (4)
	// Button Y: Square (1)
	// Button L1: L1 (5)
	// Button R1: R1 (6)
	// Select: Select (9)
	// Start: Start (10)
	AFTERGLOW_PS3_GAMEPAD		= 0x08361A34,
	P3_PS3_WIRELESS_CONTROLLER	= 0x310D0E8F,

	// PowerA 3 in 1 Remote Control/Game Pad
	// Button A: O (3)
	// Button B: X (2)
	// Button X: Triangle (4)
	// Button Y: Square (1)
	// Button L1: L1 (5)
	// Button R1: R1 (6)
	// Select: Select (9)
	// Start: Start (10)
	POWERA_3IN1_GAMEPAD			= 0x0876062a,
	POWERA_PS3_PRO_WIRELESS		= 0x576d20d6,

	// Xbox 360 wired/wireless controllers
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (4)
	// Button Y: X (3)
	// L1: L1 (5)
	// R1: R1 (6)
	// Select: Back (7)
	// Start: Start (8)
	XBOX360_GAMEPAD						= 0xF9001BAD,
	XBOX360_POWERA_GAMEPAD				= 0x3F0015E4,
	XBOX360_POWERA_MINI_PRO_EX_GAMEPAD	= 0x531A24C6,
	XBOX360_HORI_EX2_JOYSTICK			= 0x000D0F0D,
	XBOX360_ARCADE_GAMESTICK_JOYSTICK	= 0x47580738,
	MADCATZ_XBOX360_GAMEPAD				= 0x47160738,
	XBOX360_WIRELESS_ADAPTER			= 0x02A1045E,
	SCP_DS3_DRIVER						= 0x028E045E,
	CAPCOM_XBOX360_SF4_FIGHTPAD			= 0xF02E1BAD,
	
	XBOX_ONE_GAMEPAD					= 0x02d1045e,

	// Microsoft SideWinder Freestyle Pro
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Arrow next to dpad (10)
	// Start: Start (9)
	SIDEWINDER_FREESTYLE_PRO_GAMEPAD	= 0x000E045E,

	// Microsoft SideWinder Plug & Play Game Pad
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (4)
	// Button Y: X (3)
	// Button L: L (5)
	// Button R: R (6)
	SIDEWINDER_PLUG_PLAY_GAMEPAD	= 0x0027045E,

	// Microsoft SideWinder Plug & Play Game Pad
	// Button A: B (2)
	// Button B: A (1)
	// Button Y: X (5)
	// Button X: Y (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Z (6)
	// Start: Arrow (9)
	SIDEWINDER_GAME_PAD_PRO_GAMEPAD	= 0x0026045E,

	// Logitech Dual Action/Precision game pad
	// Button A: 3
	// Button B: 2
	// Button X: 4
	// Button Y: 1
	// Button L: 5
	// Button R: 6
	// Select: 9 (9)
	// Start: 10 (10)
	LOGITECH_DUAL_ACTION_GAMEPAD	= 0xC216046D,
	LOGITECH_PRECISION_GAMEPAD		= 0xC21A046D,

	// Logitech WingMan (USB)
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Select (11)
	// Start: Start (9)
	LOGITECH_WINGMAN_GAMEPAD	= 0xC209046D,

	// SteelSeries 1GC/3GC/Dragon Rise/Generic USB/Playstation 2 style game pad
	// Button A: 3 (3)
	// Button B: 2 (2)
	// Button X: 4 (4)
	// Button Y: 1 (1)
	// Button L: 5 (5)
	// Button R: 6 (6)
	// Select: 9 (9)
	// Start: 10 (10)
	// Dragon Rise uses a different button layout
	// Button A: 4 (4)
	// Button B: 3 (3)
	// Button X: 2 (2)
	// Button Y: 1 (1)
	// Button L: 5 (5)
	// Button R: 6 (6)
	// Select: 9 (9)
	// Start: 10 (10)
	DRAGON_RISE_GAMEPAD		= 0x00010079,
	STEELSERIES_1GC_GAMEPAD	= 0x00110079,
	STEELSERIES_3GC_GAMEPAD	= 0x00060079,

	// SteelSeries Free
	// Button A: 3 (2)
	// Button B: 4 (1)
	// Button X: 2 (5)
	// Button Y: 1 (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: A (13)
	// Start: B (12)
	STEELSERIES_FREE		= 0x14121038,

	// Saitek P150
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Z (6)
	// Start: C (3)
	SAITEK_P150_GAMEPAD	= 0x051006A3,

	// Saitek P880
	// Saitek P2500
	// Button A: 4
	// Button B: 3
	// Button X: 2
	// Button Y: 1
	// Button L: 7
	// Button R: 8
	// Select: 5
	// Start: 6
	SAITEK_P880_GAMEPAD		= 0x010906A3,
	SAITEK_P2500_GAMEPAD	= 0xFF0C06A3,

	// Saitek P990
	// Button A: 3
	// Button B: 2
	// Button X: 4
	// Button Y: 1
	// Button L: 5
	// Button R: 6
	// Select: Gray (10)
	// Start: Black (9)
	SAITEK_P990_GAMEPAD	= 0x040B06A3,

	// Mayflash Wii Classic Controller Adapter
	// Button A: a (2)
	// Button B: b (3)
	// Button X: x (1)
	// Button Y: y (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Select (9)
	// Start: Start (10)
	// Right port is joystick 1
	MAYFLASH_DUAL_BOX_WII_ADAPTER	= 0x03011D79,

	// Mayflash Wireless Wii U Controller Adapter
	// Button A: A (3)
	// Button B: B (2)
	// Button X: X (4)
	// Button Y: Y (1)
	// Button L: L (5)
	// Button R: R (6)
	// Select: '-' (9)
	// Start: '+' (10)
	MAYFLASH_WIRELESS_WIIU_ADAPTER	= 402653305,

	// Mayflash SS Controller Adapter
	// Button A: A (1)
	// Button B: B (2)
	// Button X: C (3)
	// Button Y: Y (5)
	// Button L: L (6)
	// Button R: R (8)
	// Select: Unassigned
	// Start: '+' (10)
	// Left port is joystick 1
	MAYFLASH_SS_CONTROLLER_ADAPTER = 806358671,

	// Mayflash MD2/SNES/SFC/NES/FC Adapter
	// Button A: A (1)
	// Button B: B (2)
	// Button X: X (3)
	// Button Y: Y (4)
	// Button L: L (5)
	// Button R: R (6)
	// Select: Select (7)
	// Start: 'Start' (8)

	MAYFLASH_MSSNF_CONTROLLER_ADAPTER	= 0x18040079,

	// Nyko Playpad
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Unassigned
	// Start: Right arrow (12)
	NYKO_PLAYPAD_GAMEPAD	= 0x00091D79,
	NYKO_PLAYPAD_HID		= 0x0000FFFF,

	// PIII Converter Model 538 (PS2 adapter)
	// Button A: O (2)
	// Button B: X (3)
	// Button X: Triangle (1)
	// Button Y: Square (4)
	// Button L: L1 (7)
	// Button R: R1 (8)
	// Select: Select (9)
	// Start: Start (10)
	PIII_CONVERTER_ADAPTER		= 0x00010810,
	PS3_CONVERTER_ADAPTER		= 0x00030810,
	CAPCOM_PS3_SF4_FIGHTPAD		= 0x88280738,
	CAPCOM_PS3_SD_GAMEPAD		= 0x32850738,
	BATTLEFIELD4_PS3_GAMEPAD	= 0x01320E6F,
	
	// Mad Catz CTRLR
	MAD_CATZ_CTRLR_GAMEPAD		= 0x52630738,

	// XBCD driver v1.07 (http://www.redcl0ud.com/xbcd.html)
	// Button A: B (2)
	// Button B: A (1)
	// Button Y: X (4)
	// Button X: Y (3)
	// Button L: L (11)
	// Button R: R (12)
	// Select: Back (6)
	// Start: Start (5)
	XBCD_XBOX_ADAPTER	= 0x45160738,
	
	// XBCD driver v0.2.7 (http://vba-m.com/forum/Thread-xbcd-0-2-7-release-info-updates-will-be-posted-here)
	// Button A: B (2)
	// Button B: A (1)
	// Button Y: X (4)
	// Button X: Y (3)
	// Button L: L (11)
	// Button R: R (12)
	// Select: Back (6)
	// Start: Start (5)
	XBCD_27_XBOX_ADAPTER	= 0x0289045E,

	// Radio Shack Cat. No 26-728 Gamepad mode
	// Gravid PC GamePad
	// Button A: Yellow
	// Button B: Green
	// Select: Red
	// Start: Blue
	// PC Fighter 6
	// Button A: B
	// Button B: A
	// Button X: Y
	// Button Y: X
	// Select: Z
	// Start: C
	// Gamepad!
	// Button A: 3
	// Button B: 4
	// Select: 1
	// Start: 2
	RADIO_SHACK_PC_ADAPTER	= 0x0201079D,

	// Retrolink Saturn Game pad
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Z (6)
	// Start: Start (9)
	RETROLINK_CLASSIC_GAMEPAD	= 0xD01312BD,

	// MotionInJoy PS3 Driver
	// Button A: O (2)
	// Button B: X (3)
	// Button X: Triangle (1)
	// Button Y: Square (4)
	// Button L: L1 (5)
	// Button R: R1 (6)
	// Select: Select (9)
	// Start: Start (10)
	MOTIONINJOY_PS3_WIRED_GAMEPAD	= 0x03088888,

	// Neo Geo X Arcade Stick
	// Button A: A (1)
	// Button B: B (2)
	// Button X: C (4)
	// Button Y: D (3)
	// Select: Select (9)
	// Start: Start (10)
	NEOGEO_X_ARCADE_JOYSTICK	= 0x4E471292,

	// Retro-bit NES Controller adapter
	// Button A: A (1)
	// Button B: B (2)
	// Select: Select (3)
	// Start: Start (4)
	RETROBIT_NES_ADAPTER	= 0x46431292,

	// Retro-bit Genesi Controller adapter
	// Button A: C (3)
	// Button B: B (2)
	// Button X: X (4)
	// Button Y: A (1)
	// Button L: Y (5)
	// Button R: Z (6)
	// Select: Mode (8)
	// Start: Start (7)
	RETROBIT_GENESIS_ADAPTER	= 0x47451292,

	// Gravis GamePad Pro
	// Button A: Yellow (3)
	// Button B: Green (2)
	// Button X: Blue (4)
	// Button Y: Red (1)
	// Button L: L1 (5)
	// Button R: R1 (6)
	// Select: Select (9)
	// Start: Start (10)
	GRAVIS_GAMEPAD_PRO_GAMEPAD	= 0x40010428,

	// Mayflash SNES Controller Adapter
	// Button A: A (2)
	// Button B: B (3)
	// Button X: X (1)
	// Button Y: Y (4)
	// Button L: L (7)
	// Button R: R (8)
	// Select: Select (9)
	// Start: Start (10)
	// Right port is joystick 1
	MAYFLASH_SNES_CONTROLLER_ADAPTER	= 0x30130E8F,

	// Classic SNES Adapter
	// Button A: A (2)
	// Button B: B (1)
	// Button X: X (4)
	// Button Y: Y (3)
	// Button L: L (5)
	// Button R: R (6)
	// Select: Select (7)
	// Start: Start (8)
	CLASSIC_SNES_CONTROLLER_ADAPTER	= 0x88660925,

	// Hyperkin 
	// Button A: A (1)
	// Button B: B (2)
	// Button X: X (3)
	// Button Y: Y (4)
	// Button L: L (5)
	// Button R: R (6)
	// Select: Start (8)
	// Start: Select (7)
	HYPERKIN_PIXEL_ART_CONTROLLER		= 0x00060810,

	// 8BitDo NES30 gamepad 
	// Button A: A (2)
	// Button B: B (3)
	// Button X: X (1)
	// Button Y: Y (4)
	// Button L: L (5)
	// Button R: R (6)
	// Select: Start (8)
	// Start: Select (7)
	NES30_GAMEPAD	= 0xAB111235,

	// GF G60306A USB Game Controller
	// Button A: 5
	// Button B: 4
	// Button X: 2
	// Button Y: 1
	// Button L: 7
	// Button R: 8
	// Select: 11 (11)
	// Start: 12 (12)
	GF_G60406A_GAMEPAD	= 0x00030E8F,

	// Thrustmaster Firestore Dual Analog 2
	// Thrustmaster Dual Analog 3
	// Button A: Right face button (3)
	// Button B: Bottom face button (1)
	// Button X: Top face button (4)
	// Button Y: Left face button (2)
	// Button L: Top Left (5)
	// Button R: Top Right (7)
	// Button Select: Finger Left (9)
	// Button Start: Finger Right (10)
	THRUSTMASTER_FIRESTORM_DUAL_2_GAMEPAD	= 0xB303044F,
	THRUSTMASTER_DUAL_ANALOG_3_GAMEPAD		= 0xB315044F,

	// Logic 3 USB Intruder
	// Button A: D (4)
	// Button B: C (3)
	// Button X: B (2)
	// Button Y: A (1)
	// Button L: L1 (5)
	// Button R: R1 (7)
	// Select: L2 (6)
	// Start: R2 (8)
	LOGIC_3_USB_INTRUDER_GAMEPAD	= 0x990207B5,

	// Ion Go Pad
	// Button A: 2
	// Button B: 1
	// Button X: 4
	// Button Y: 3
	// Button L: 7
	// Button R: 8
	// Select: 5
	// Start: 6
	ION_GO_PAD_GAMEPAD	= 0x20600583,

	// Ouya game controller
	// Button A: A (4)
	// Button B: O (1)
	// Button X: Y (3)
	// Button Y: U (2)
	// Button L: L1 (5)
	// Button R: R1 (6)
	// Select: L2 (13)
	// Start: R2 (14)
	OUYA_GAMEPAD	= 0x00012836,

	// Gamestick game controller
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (5)
	// Button Y: X (4)
	// Button L: L1 (7)
	// Button R: R1 (8)
	// Select: -
	// Start: Start (12)
	GAMESTICK_GAMEPAD	= 0x10110F0D,

	// Moga Hero gamepad
	// Button A: B (2)
	// Button B: A (1)
	// Button X: Y (4)
	// Button Y: X (3)
	// Button L: L1 (5)
	// Button R: R1 (6)
	// Select: Select (7)
	// Start: Start (8)
	MOGA_HERO_GAMEPAD	= 0x89e520d6,

	// SF digital pad
	// Button A: 5 (4)
	// Button B: 4 (3)
	// Button X: 2 (1)
	// Button Y: 1 (0)
	// Button L: 7 (6)
	// Button R: 8 (7)
	// Select: 9 (8)
	// Start: 10 (9)
	SF_DIGITAL_PAD		= 0x00130E8F
};

struct JoystickDefine
{
	// GUID
	GamePads	eGamePad;
	
	// Buttons
	int			m_iButtonA;
	int			m_iButtonB;
	int			m_iButtonX;
	int			m_iButtonY;
	int			m_iButtonL;
	int			m_iButtonR;
	int			m_iSelectButton;
	int			m_iStartButton;
};

// GUID, A, B, Select, Start
JoystickDefine	gsc_joysticks[]	=
{
	{SIDEWINDER_PLUG_PLAY_GAMEPAD, 1, 0, 3, 2, 4, 5, -1, -1},
	{SIDEWINDER_GAME_PAD_PRO_GAMEPAD, 1, 0, 4, 3, 6, 7, 5, 8},
	{RETROLINK_CLASSIC_GAMEPAD, 1, 0, 4, 3, 6, 7, 5, 8},
	{NYKO_PLAYPAD_GAMEPAD, 1, 0, 4, 3, 6, 7, -1, 11},
	{NYKO_PLAYPAD_HID, 1, 0, 4, 3, 6, 7, -1, 11},
	{XBOX360_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX360_POWERA_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX360_POWERA_MINI_PRO_EX_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX360_WIRELESS_ADAPTER, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX_ONE_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{SCP_DS3_DRIVER, 1, 0, 3, 2, 4, 5, 6, 7},
	{CAPCOM_XBOX360_SF4_FIGHTPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX360_HORI_EX2_JOYSTICK, 1, 0, 3, 2, 4, 5, 6, 7},
	{XBOX360_ARCADE_GAMESTICK_JOYSTICK, 1, 0, 3, 2, 4, 5, 6, 7},
	{MADCATZ_XBOX360_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{ION_GO_PAD_GAMEPAD, 1, 0, 3, 2, 6, 7, 4, 5},
	{XBCD_XBOX_ADAPTER, 1, 0, 3, 2, 10, 11, 5, 4},
	{XBCD_27_XBOX_ADAPTER, 1, 0, 3, 2, 10, 11, 5, 4},
	{NEOGEO_X_ARCADE_JOYSTICK, 1, 0, 2, 3, -1, -1, 8, 9},
	{RETROBIT_NES_ADAPTER, 0, 1, -1, -1, -1, -1, 2, 3},
	{RETROBIT_GENESIS_ADAPTER, 2, 1, 3, 0, 4, 5, 7, 6},
	{SIDEWINDER_FREESTYLE_PRO_GAMEPAD, 1, 0, 4, 3, 6, 7, 9, 8},
	{GAMEMON_GAMEPAD, 3, 2, 1, 0, 4, 5, 6, 7},
	{RADIO_SHACK_PC_ADAPTER, 3, 2, 1, 0, -1, -1, 4, 5},
	{THRUSTMASTER_FIRESTORM_DUAL_2_GAMEPAD, 2, 0, 3, 1, 4, 6, 8, 9},
	{THRUSTMASTER_DUAL_ANALOG_3_GAMEPAD, 2, 0, 3, 1, 4, 6, 8, 9},
	{AFTERGLOW_PS3_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},
	{P3_PS3_WIRELESS_CONTROLLER, 2, 1, 3, 0, 4, 5, 8, 9},	
	{POWERA_3IN1_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},
	{POWERA_PS3_PRO_WIRELESS, 2, 1, 3, 0, 4, 5, 8, 9},
	{GRAVIS_GAMEPAD_PRO_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},
	{LOGITECH_DUAL_ACTION_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},
	{LOGITECH_PRECISION_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},
	{LOGITECH_WINGMAN_GAMEPAD, 1, 0, 4, 3, 6, 7, 10, 8},
	{STEELSERIES_1GC_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},	
	{STEELSERIES_3GC_GAMEPAD, 1, 2, 0, 3, 6, 7, 8, 9},	
	{STEELSERIES_FREE, 1, 0, 4, 3, 6, 7, 12, 11},	
	{SAITEK_P150_GAMEPAD, 1, 0, 4, 3, 6, 7, 5, 2},
	{SAITEK_P880_GAMEPAD, 3, 2, 1, 0, 6, 7, 4, 5},
	{SAITEK_P2500_GAMEPAD, 3, 2, 1, 0, 6, 7, 4, 5},
	{SAITEK_P990_GAMEPAD, 2, 1, 3, 0, 4, 5, 9, 8},
	{SPIN_MASTER_GAMEPAD, 1, 2, 0, 3, 6, 7, 8, 9},
	{TWIN_USB_GAMEPAD, 1, 2, 0, 3, 6, 7, 8, 9},
	{MAYFLASH_DUAL_BOX_WII_ADAPTER, 1, 2, 0, 3, 6, 7, 8, 9},
	{MAYFLASH_WIRELESS_WIIU_ADAPTER, 2, 1, 3, 0, 4, 5, 8, 9},
	{MAYFLASH_SS_CONTROLLER_ADAPTER, 0, 1, 2, 4, 5, 7, -1, 9},
	{MAYFLASH_MSSNF_CONTROLLER_ADAPTER, 0, 1, 2, 3, 4, 5, 6, 7},
	{MAYFLASH_SNES_CONTROLLER_ADAPTER, 1, 2, 0, 3, 6, 7, 8, 9},
	{CLASSIC_SNES_CONTROLLER_ADAPTER, 1, 0, 3, 2, 4, 5, 6, 7},
	{HYPERKIN_PIXEL_ART_CONTROLLER, 0, 1, 2, 3, 4, 5, 7, 6},
	{NES30_GAMEPAD, 1, 2, 0, 3, 4, 5, 6, 7},
	{AXISPAD_GGE900_GAMEPAD, 3, 2, 1, 0, 4, 5, 10, 11},	   
	{GAME_ELEMENTS_GGE908_GAMEPAD, 1, 2, 0, 3, 4, 5, 8, 9},
	{PHILIPS_GGE909_GAMEPAD, 1, 2, 0, 3, 4, 5, 8, 9},
	{PIII_CONVERTER_ADAPTER, 1, 2, 0, 3, 6, 7, 8, 9},
	{PS3_CONVERTER_ADAPTER, 1, 2, 0, 3, 6, 7, 8, 9},
	{CAPCOM_PS3_SF4_FIGHTPAD, 2, 1, 3, 0, 4, 6, 8, 9},	
	{CAPCOM_PS3_SD_GAMEPAD, 2, 1, 3, 0, 4, 6, 8, 9},	
	{BATTLEFIELD4_PS3_GAMEPAD, 2, 1, 3, 0, 4, 5, 8, 9},	
	{MAD_CATZ_CTRLR_GAMEPAD, 1, 0, 4, 3, 6, 7, -1, 11},	
	{MOTIONINJOY_PS3_WIRED_GAMEPAD, 1, 2, 0, 3, 4, 5, 8, 9},
	{LOGIC_3_USB_INTRUDER_GAMEPAD, 3, 2, 1, 0, 4, 6, 5, 7},
	{DRAGON_RISE_GAMEPAD, 3, 2, 1, 0, 4, 5, 8, 9},
	{GF_G60406A_GAMEPAD, 4, 3, 1, 0, 6, 7, 10, 11},
	{OUYA_GAMEPAD, 3, 0, 2, 1, 4, 5, 12, 13},
	{GAMESTICK_GAMEPAD, 1, 0, 4, 3, 6, 7, -1, 11},
	{MOGA_HERO_GAMEPAD, 1, 0, 3, 2, 4, 5, 6, 7},
	{SF_DIGITAL_PAD, 4, 3, 1, 0, 6, 7, 8, 9},
};
