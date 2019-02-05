/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILTYPES_H
#define DEVILTYPES_H

#include "Devil.h"

class Bloater : public Devil {
public:
	Bloater();
	sf::String getClassName() { return(sf::String("\nPlayerCharacter::Devil::Bloater Class.\n")); };
};

class Chaser : public Devil {
public:
	Chaser();
	sf::String getClassName() { return(sf::String("\nPlayerCharacter::Devil::Chaser Class.\n")); };
};

class Crawler : public Devil {
public:
	Crawler();
	sf::String getClassName() { return(sf::String("\nPlayerCharacter::Devil::Crawler Class.\n")); };
};

#endif	// !DEVILTYPES_H