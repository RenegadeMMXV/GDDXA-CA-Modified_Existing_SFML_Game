/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/29	YYYY/MM/DD
*	@description	A file to hold any values that I want to access everywhere
*/

#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

/***-------------***\
|	Game Constants	|
\***-------------***/

constexpr int VERTS_IN_QUAD = 4;
constexpr int TILE_SIZE = 50;
constexpr float PLAYER_START_SPEED = 200.0f;
constexpr float PLAYER_START_HEALTH = 100.0f;


/***-------------***\
|	Enemy Constants	|
\***-------------***/

// How fast is each Enemy type?
constexpr float BLOATER_SPEED = 40.0f;
constexpr float CHASER_SPEED = 80.0f;
constexpr float CRAWLER_SPEED = 20.0f;

// How tough is each Enemy type
constexpr float BLOATER_HEALTH = 5.0f;
constexpr float CHASER_HEALTH = 1.0f;
constexpr float CRAWLER_HEALTH = 3.0f;

// Make each Enemy vary its speed slightly
constexpr int MAX_VARIANCE = 30;
constexpr int OFFSET = 101 - MAX_VARIANCE;

#endif // !CONSTANTS_H
