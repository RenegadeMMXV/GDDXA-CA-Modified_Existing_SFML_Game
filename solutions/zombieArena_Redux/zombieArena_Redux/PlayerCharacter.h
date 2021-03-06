/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/31	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "TextureHolder.h"
#include "WeaponTypes.h"

class PlayerCharacter abstract {
public:
	/***---------------------***\
	|	Finite State Machines	|
	\***---------------------***/

	enum class Movement_V { IDLE, UP, DOWN };
	enum class Movement_H { IDLE, LEFT, RIGHT };
	enum class Action { IDLE, ATTACKING };

	Movement_V m_Movement_V = Movement_V::IDLE;
	Movement_H m_Movement_H = Movement_H::IDLE;
	Action m_Action = Action::IDLE;

	//	What weapon is currently equipped?
	Weapon* m_Weapon;
	void reload() { this->m_Weapon->reload(); };
	void shoot(sf::Vector2f origin, sf::Vector2f target, sf::Time currentFrameTime)
		{ this->m_Weapon->fire(origin, target, currentFrameTime); };

	// How much health has the PC got?
	int m_Health;

	// What is the maximum health the PC can have
	int m_MaxHealth;

	// Find out if the PC is alive
	bool isAlive();

	// Where is the PC
	sf::FloatRect getPosition() { return this->m_Sprite.getGlobalBounds(); };

	// Where is the center of the PC
	sf::Vector2f getCentre() { return this->m_Position; };

	// Send a copy of the sprite to main
	sf::Sprite getSprite() { return this->m_Sprite; };

	// How much health has the PC currently got?
	int getHealth() { return this->m_Health; };

	// How long ago was the player last hit
	sf::Time getLastHitTime() { return this->m_LastHit; };

	// A SoundBoard
	SoundBoard* m_Audio;
	
protected:
	/***---------***\
	|	Variables	|
	\***---------***/

	// Speed in pixels per second
	float m_Speed;

	// Maximum Speed in pixels per second
	float m_MaxSpeed;

	// Where is the PC
	sf::Vector2f m_Position;

	// What does the PC look like
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	// When was the PC last hit
	sf::Time m_LastHit;


	/***---------***\
	|	Functions	|
	\***---------***/

	void init(SoundBoard& audio);

	virtual void spawn(float posX, float posY) = 0;
	virtual void update(sf::Time elapsedTime);
	virtual sf::String getClassName() = 0 { return(sf::String("PlayerCharacter")); };

	// Handle hits in both directions
	/*virtual sf::Time getLastHitTime() = 0;*/
	virtual bool onHit(sf::Time timeHit);
};

#endif // !PLAYERCHARACTER_H