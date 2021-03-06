/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILSPAWN_H
#define DEVILSPAWN_H

#include <fstream>
#include <list>
#include <sstream>

#include "Button.h"
#include "Devil.h"
#include "InputHandler.h"
#include "PowerUp.h"
#include "SoundBoard.h"

class DevilSpawn {
public:
	DevilSpawn();
	void runGame();

private:
	void Input();
	void Update();
	void Draw();

	void initButtons();
	void initText();

	int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
	   
	// The game will always be in one of six states
	enum class GameState { PLAYING, PAUSED, MAIN_MENU, LEVELING_UP, SETTINGS, GAME_OVER };
	// Start with the MAIN_MENU m_gameState
	GameState m_gameState = GameState::MAIN_MENU;

	// Settings pages
	enum class SettingsPage { LIST, GRAPHICS, AUDIO, GAMEPLAY};
	SettingsPage m_currentSettingsPage = SettingsPage::LIST;


	// Set the screen resolution and create an SFML window
	sf::Vector2f resolution;

	sf::RenderWindow window;

	sf::Uint32 m_windowedStatus = sf::Style::Fullscreen;
	unsigned int m_frameRate = 60;
	bool m_vSyncActive = false;

	void refreshWindow();

	// Create an SFML View
	sf::View mainView;
	// Create a view for the HUD
	sf::View hudView;

	// Instance of TextureHolder
	TextureHolder holder;

	//	An Input Handler
	InputHandler m_InpHand;
	Command* cmd;

	//	A Sound Manager
	SoundBoard m_audio;

	// Hold Events betwen frames
	sf::Event evnt;

	// Where is the mouse in relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	sf::Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player* m_Player;

	// The boundaries of the arena
	sf::IntRect arena;

	// Create the background
	sf::VertexArray background;
	sf::Texture textureBackground;

	// Prepare a horde of Devils
	int hordeSize;
	int numHordeAlive;
	std::vector<Devil*> horde;
	void createHorde(int numDevils, sf::IntRect* arena);
	Devil* summonDevil(sf::Vector2f pos, int type);

	// Clock for timings
	sf::Clock m_GameClock;
	// How long has the PLAYING m_gameState been active
	sf::Time gameTimeTotal;
	sf::Time m_FrameTime;

	// When was the fire button last pressed?
	sf::Time lastPressed;

	// Create a skin for the Mouse Cursor
	sf::Sprite sprite_mouse;
	sf::Texture texture_mouse;

	// Create a couple of pickups
	std::vector<PowerUp*> powerUps;
	void generatePowerUps(int count, sf::IntRect* arena);
	PowerUp* newPowerUp(sf::Vector2i pos, int type);

	// About the game
	int wave = 0;
	int score = 0;
	int hiScore = 0;

	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	sf::Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsUpdatePeriod = 60;

	// For the home/game over screen
	sf::Sprite spriteGameOver;
	sf::Texture textureGameOver;

	// Create a Sprite for the Ammo UI Icon
	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon
		= TextureHolder::GetTexture("Graphics\\ammo_icon.png");

	// A container for the Font
	sf::Font font;

	// Declare Text containers
	sf::Text pausedText;
	sf::Text gameOverText;
	sf::Text levelUpText;
	sf::Text mainMenuText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	sf::Text hordeRemainingText;
	sf::Text waveNumberText;
	sf::Text settingsText;
	sf::Text graphicsSettingsText;
	sf::Text audioSettingsText;
	sf::Text gameplaySettingsText;

	// Declare Buttons Lists
	std::list<GUI::Button> btnLst_gameOver;
	std::list<GUI::Button> btnLst_levelUp;
	std::list<GUI::Button> btnLst_mainMenu;
	std::list<GUI::Button> btnLst_allSettings;
	std::list<GUI::Button> btnLst_graphicsSettings;
	std::list<GUI::Button> btnLst_audioSettings;
	std::list<GUI::Button> btnLst_gameplaySettings;

	// Declare Shapes
	sf::RectangleShape pausedShader;
	sf::RectangleShape miniMapBorder;
	sf::RectangleShape healthBar;
};

#endif // DEVILSPAWN_H