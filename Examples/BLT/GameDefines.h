// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

static const int	gsc_iScreenWidth		= 320;
static const int	gsc_iScreenHeight		= 240;

// Max lives
static const int	gsc_iMaxLives			= 5;

// Max bullets
static const int	gsc_iMaxBullets			= 4;

// Max enemies
static const int	gsc_iMaxEnemies			= 6;

// Max explosions
static const int	gsc_iMaxExplosions		= gsc_iMaxBullets;

// Player speed
static const float	gsc_fPlayerSpeed		= 2.0f;

// Bullet speed
static const float	gsc_fBulletSpeed		= 2.0f;

// Enemy speed
static const float	gsc_fEnemySpeed			= 1.5f;

// Scroll speed
static const float	gsc_fScrollSpeed		= 0.25f;

// Sprite offset from the bottom of the screen
static const int	gsc_iBottomOffset		= 8;

// Fire button cooldown, in seconds
static const float	gsc_iButtonCooldown		= 0.25f;

// Player sort order
static const int	gsc_iPlayerSortOrder	= 0;

// Shot sort order
static const int	gsc_iShotSortOrder		= 1;

// Sprite BG layer
static const int	gsc_iBGLayer			= 3;

// Enemy score
static const int	gsc_iEnemyScore			= 25;

// Sprite VRAM tile layout
enum SpriteTileLayout
{
	PlayerTile		= 0,								// Player takes 2 tiles
	BulletTile		= PlayerTile + 2,					// Bullets each take 2 tiles
	EnemyTile		= BulletTile + gsc_iMaxBullets * 2,	// Enemies take 2 tiles each
	ExplosionTile	= EnemyTile + gsc_iMaxEnemies * 2,	// Explosions take 2 tiles each
};
