/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

class Bullet {
private:
	// Where is the bullet?
	sf::Vector2f m_Position;

	// What each bullet looks like
	sf::RectangleShape m_BulletShape;

	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed;

	// What fraction of 1 pixel does the bullet travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Where is this bullet headed to?
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

// Public function prototypes go here
public:
	// The constructor
	Bullet(float damage, float speed);

	float m_BulletDamage;

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(sf::Vector2f origin,
		sf::Vector2f target);

	// Tell the calling code where the bullet is in the world
	sf::FloatRect getPosition();

	// Return the actual shape (for drawing)
	sf::RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);
};

#endif // BULLET_H