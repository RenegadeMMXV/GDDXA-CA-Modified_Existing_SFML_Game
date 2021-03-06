/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::Update() {
		/***------------***\
		| Update the Scene |
		\***------------***/

		// Update while Playing
	if (m_gameState == GameState::PLAYING) {
		m_audio.onNotify(SoundBoard::SFX::MUSIC_GAME);
		
		// Change the mouse to the GAME mouse
		window.setMouseCursorVisible(false);
		texture_mouse = TextureHolder::GetTexture("Graphics\\crosshair.png");
		sprite_mouse.setTexture(texture_mouse);
		sprite_mouse.setOrigin(25, 25);

		// Where is the mouse pointer
		mouseScreenPosition = sf::Mouse::getPosition(window);

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window.mapPixelToCoords(
			mouseScreenPosition, mainView);

		// Set the crosshair to the mouse world location
		sprite_mouse.setPosition(mouseWorldPosition);

		// Update the player
		m_Player->update(m_FrameTime);

		// Make the view centre around the player				
		mainView.setCenter(m_Player->getCentre());

		// Loop through each Devil and update them
		for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if ((*it)->isAlive()) {
				(*it)->update(m_FrameTime, m_Player->getCentre());
			}
		}

		// Update any bullets that are in-flight
		for (std::vector<Bullet*>::iterator it = m_Player->m_Weapon->m_Ammo.begin(); it != m_Player->m_Weapon->m_Ammo.end(); ++it) {
			if ((*it)->getPosition().left < 0
				|| (*it)->getPosition().left > arena.width
				|| (*it)->getPosition().top < 0
				|| (*it)->getPosition().top > arena.height) {

				(*it)->stop();
			}
			else if ((*it)->isInFlight()) {
				(*it)->update(m_FrameTime.asSeconds());
			}
		}

		// Update the PowerUps
		for (std::vector<PowerUp*>::iterator it = powerUps.begin(); it != powerUps.end(); ++it) {
			if ((*it)->update(m_FrameTime, arena)) {
				m_audio.onNotify(SoundBoard::SFX::POWERUP_SPAWN);
			}
		}

		// Collision detection
		// Have any horde been shot?
		for (std::vector<Bullet*>::iterator it = m_Player->m_Weapon->m_Ammo.begin();
			it != m_Player->m_Weapon->m_Ammo.end(); ++it) {

			for (std::vector<Devil*>::iterator it2 = horde.begin();
				it2 != horde.end(); ++it2) {

				if ((*it)->isInFlight() &&
					(*it2)->isAlive()) {
					
					if ((*it)->getPosition().intersects
					((*it2)->getPosition())) {
						// Stop the bullet
						(*it)->stop();

						// Register the hit and see if it was a kill
						if ((*it2)->onHit(gameTimeTotal, (*it))) {
							// Not just a hit but a kill too
							m_audio.onNotify(SoundBoard::SFX::HIT_KILL);
							score += 10;
							if (score >= hiScore) {
								hiScore = score;
							}

							numHordeAlive--;

							// When all the horde are dead (again)
							if (numHordeAlive == 0) {
								m_gameState = GameState::LEVELING_UP;
							}
						}

						// Make a splat sound
						m_audio.onNotify(SoundBoard::SFX::HIT_UNARMED);
					}
				}
			}
		}// End zombie being shot

		// Has the Player Wandered out of the Zone?
		if (m_Player->getCentre().x < 0) {
			m_Player->onHit(gameTimeTotal);
		}
		else if (m_Player->getCentre().x > arena.width) {
			m_Player->onHit(gameTimeTotal);
		}
			
		if (m_Player->getCentre().y < 0) {
			m_Player->onHit(gameTimeTotal);
		}
		else if (m_Player->getCentre().y > arena.height) {
			m_Player->onHit(gameTimeTotal);
		}// End player wondering

		// Have any horde touched the player			
		for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if (m_Player->getPosition().intersects
			((*it)->getPosition()) && (*it)->isAlive()) {

				if (m_Player->onHit(gameTimeTotal)) {
					m_audio.onNotify(SoundBoard::SFX::HIT_PLAYER);
				}

				if (m_Player->getHealth() <= 0) {
					m_gameState = GameState::GAME_OVER;

					std::ofstream outputFile("gamedata\\scores.txt");
					outputFile << hiScore;
					outputFile.close();
				}
			}
		}// End player touched

		// Has the player touched a PowerUp
		for (std::vector<PowerUp*>::iterator it = powerUps.begin(); it != powerUps.end(); ++it) {
			if (m_Player->getPosition().intersects
				((*it)->getPosition()) && (*it)->isSpawned()) {
				
				(*it)->activated(m_Player);
				
				// Play a sound
				m_audio.onNotify(SoundBoard::SFX::POWERUP_PICKUP);
			}
		}

		// Resize the health bar
		healthBar.setSize(sf::Vector2f(m_Player->getHealth() * 3, 70));
		healthBar.setOrigin(healthBar.getSize().x / 2, healthBar.getSize().y / 2);

		// Increment the amount of time since the last HUD update
		timeSinceLastUpdate += m_FrameTime;
		// Increment the number of frames since the last HUD calculation
		framesSinceLastHUDUpdate++;
		// Calculate FPS every fpsUpdatePeriod frames
		if (framesSinceLastHUDUpdate > fpsUpdatePeriod) {

			// Update game HUD text
			std::stringstream ssAmmo;
			std::stringstream ssScore;
			std::stringstream ssHiScore;
			std::stringstream ssWave;
			std::stringstream ssHordeAlive;

			// Update the ammo text
			ssAmmo << m_Player->m_Weapon->m_clipRemaining << "/" << m_Player->m_Weapon->m_bulletsReserved;
			ammoText.setString(ssAmmo.str());

			// Update the score text
			ssScore << "Score:" << score;
			scoreText.setString(ssScore.str());

			// Update the high score text
			ssHiScore << "Hi Score:" << hiScore;
			hiScoreText.setString(ssHiScore.str());

			// Update the wave
			ssWave << "Wave:" << wave;
			waveNumberText.setString(ssWave.str());

			// Update the high score text
			ssHordeAlive << "Horde Size:" << numHordeAlive;
			hordeRemainingText.setString(ssHordeAlive.str());

			framesSinceLastHUDUpdate = 0;
			timeSinceLastUpdate = sf::Time::Zero;
		}// End HUD update

	}// End updating the PLAYING m_gameState

	// Update while in Paused
	else if (m_gameState == GameState::PAUSED) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);
	}

	// Update while in Main Menu
	else if (m_gameState == GameState::MAIN_MENU) {
		m_audio.onNotify(SoundBoard::SFX::MUSIC_MAINMENU);
		mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_mainMenu.begin(); it != btnLst_mainMenu.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}

	// Update while in Leveling Up
	else if (m_gameState == GameState::LEVELING_UP) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_levelUp.begin(); it != btnLst_levelUp.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}

	// Update while in Settings
	else if (m_gameState == GameState::SETTINGS) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);
		
		if (m_currentSettingsPage == SettingsPage::LIST) {
			for (std::list<GUI::Button>::iterator it = btnLst_allSettings.begin(); it != btnLst_allSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GRAPHICS) {
			for (std::list<GUI::Button>::iterator it = btnLst_graphicsSettings.begin(); it != btnLst_graphicsSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
			
			/*std::cout
				<< "Current Resolution:\t" << resolution.x << " x " << resolution.y << std::endl
				<< "Framerate:\t\t" << m_frameRate << std::endl
				<< "V-Sync Status:\t\t" << m_vSyncActive << std::endl << std::endl;;*/
		}
		else if (m_currentSettingsPage == SettingsPage::AUDIO) {
			for (std::list<GUI::Button>::iterator it = btnLst_audioSettings.begin(); it != btnLst_audioSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GAMEPLAY) {
			for (std::list<GUI::Button>::iterator it = btnLst_gameplaySettings.begin(); it != btnLst_gameplaySettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
	}

	// Update while in Game Over
	else if (m_gameState == GameState::GAME_OVER) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_gameOver.begin(); it != btnLst_gameOver.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}
}