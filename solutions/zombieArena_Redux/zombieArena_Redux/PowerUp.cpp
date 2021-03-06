/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "PowerUp.h"

/***-----------------***\
|	General PowerUps	|
\***-----------------***/

/**
*	Default Constructor
*/
PowerUp::PowerUp() {
	this->m_Sprite.setOrigin(
		this->m_Sprite.getTextureRect().width / 2,
		this->m_Sprite.getTextureRect().height / 2);

	int offset = (rand() % 7) - 3;	// Range between [-3, +3]
	this->m_timeToLive = sf::seconds(START_SECONDS_TO_LIVE + offset);

	offset = (rand() % 7) - 3;
	this->m_timeToWait = sf::seconds(START_WAIT_TIME + offset);
}

/**
*	Spawn the PowerUp into the Game World
*/
void PowerUp::spawn(sf::Vector2i pos) {
	this->m_timeSinceSpawn = sf::Time::Zero;
	this->m_Spawned = true;
	
	this->m_Sprite.setPosition(pos.x, pos.y);
}

/**
*	Make the PowerUp better (generic)
*/
void PowerUp::upgrade() {
	// Make them more frequent and last longer
	this->m_timeToLive += sf::seconds(START_SECONDS_TO_LIVE / 10.0f);
	this->m_timeToWait -= sf::seconds(START_WAIT_TIME / 10.0f);
}

/**
*	Activate the PowerUp
*/
void PowerUp::activated(PlayerCharacter* pc) {
	this->m_Spawned = false;
	this->m_timeSinceDespawn = sf::Time::Zero;
}

/*
*	Update the PowerUp
*/
bool PowerUp::update(sf::Time elapsedTime, sf::IntRect& bounds) {
	if (this->m_Spawned) {
		this->m_timeSinceSpawn += elapsedTime;
	}
	else {
		this->m_timeSinceDespawn += elapsedTime;
	}
	
	// Do we need to hide a pickup?
	if (this->m_timeSinceSpawn > this->m_timeToLive && this->m_Spawned)	{
		// Revove the pickup and put it somewhere else
		this->m_Spawned = false;
		this->m_timeSinceDespawn = sf::Time::Zero;
	}

	// Do we need to spawn a pickup
	if (this->m_timeSinceDespawn > this->m_timeToWait && !this->m_Spawned) {
		// spawn the pickup
		sf::Vector2i spawnLoc = sf::Vector2i(
			(rand() % bounds.height - 75) + 50,
			(rand() % bounds.width - 75) + 50);
		spawn(spawnLoc);
		return(true);
	}
	return(false);
}

/***-------------***\
|	AMMO PowerUp	|
\***-------------***/

/**
*	Create a new Ammo PowerUp
*/
AmmoPowerUp::AmmoPowerUp() {
	// Associate texture with sprite
	this->m_Sprite.setTexture(TextureHolder::GetTexture(
		"graphics\\ammo_pickup.png"));

	// How much is pickup worth
	this->m_Value = AMMO_START_VALUE;
}

/**
*
*/
void AmmoPowerUp::activated(PlayerCharacter* pc) {
	this->PowerUp::activated(pc);
	pc->m_Weapon->loadBullets(this->m_Value);

	std::cout << "Ammo PowerUp Activated!" << std::endl;
}

/**
*	Increase the amount of Ammunition restored
*/
void AmmoPowerUp::upgrade() {
	this->m_Value += (AMMO_START_VALUE * 0.5f);
	this->PowerUp::upgrade();
}

/***-------------***\
|	Health PowerUp	|
\***-------------***/

/**
*	Create a new Health PowerUp
*/
HealthPowerUp::HealthPowerUp() {
	this->m_Sprite.setTexture(TextureHolder::GetTexture(
		"graphics\\health_pickup.png"));

	// How much is pickup worth
	this->m_Value = HEALTH_START_VALUE;
}

/**
*	Add the value of this PowerUp to the PlayerCharacter Health
*/
void HealthPowerUp::activated(PlayerCharacter* pc) {
	this->PowerUp::activated(pc);

	if (pc->m_Health + this->m_Value < pc->m_MaxHealth) {
		pc->m_Health += this->m_Value;
	}
	else {
		pc->m_Health = pc->m_MaxHealth;
	}

	std::cout << "Health PowerUp Activated!" << std::endl;
}

/**
*	Increase the amount of Health restored
*/
void HealthPowerUp::upgrade() {
	this->m_Value += (HEALTH_START_VALUE * 0.5f);
	this->PowerUp::upgrade();
}

/***-------------***\
|	Weapon PickUp	|
\***-------------***/

/**
*	Create a new Weapon PickUp
*/
WeaponPickUp::WeaponPickUp() {
	this->m_Sprite.setTexture(TextureHolder::GetTexture(
		"graphics\\weapon_pickup.png"));
}

/**
*	Randomly select between 3 weapons.
*/
void WeaponPickUp::activated(PlayerCharacter* pc) {
	this->PowerUp::activated(pc);

	Weapon* newWeapon = nullptr;
	int type = (rand() % 10);

	if (type < 4) {
		pc->m_Weapon = pc->m_Weapon->forgeWeapon(*pc->m_Audio, Weapon::WEAPON_TYPES::ASSAULTRIFLE);
	}
	else if (type < 8) {
		pc->m_Weapon = pc->m_Weapon->forgeWeapon(*pc->m_Audio, Weapon::WEAPON_TYPES::SHOTGUN);
	}
	else/* if (type > 8) */ {
		pc->m_Weapon = pc->m_Weapon->forgeWeapon(*pc->m_Audio, Weapon::WEAPON_TYPES::RPG);
	}

	std::cout << "Weapon PowerUp Activated!" << std::endl;
}
