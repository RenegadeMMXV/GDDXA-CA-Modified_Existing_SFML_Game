/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILTYPES_H
#define DEVILTYPES_H

#include "Devil.h"

class Demon : public Devil {
public:
	Demon();
	sf::String getClassName() { return(sf::String("PlayerCharacter::Devil::Demon")); };
};

class Chaser : public Devil {
public:
	Chaser();
	sf::String getClassName() { return(sf::String("PlayerCharacter::Devil::Chaser")); };
};

class Crawler : public Devil {
public:
	Crawler();
	sf::String getClassName() { return(sf::String("PlayerCharacter::Devil::Crawler")); };
};

#endif	// !DEVILTYPES_H