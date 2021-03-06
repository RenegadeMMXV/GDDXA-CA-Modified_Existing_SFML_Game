/**
*	@author			Ciaran Bent [K00221230]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description	Command Pattern Implementation
*/

#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Command.h"

namespace ControlScheme {
	enum {
		DEFAULT = 0,
		BUMPERJUMPER = 1
	};
}

class InputHandler {
public:
	InputHandler();
	void chooseScheme(sf::Uint32);
	Command* handleInput(sf::Time t);

	//  Is the Player using a controller?
	unsigned int m_controllerIndex = 0;
	sf::Time m_inputBlocker = sf::milliseconds(10);
	sf::Time m_sinceLastInput = sf::Time::Zero;
	sf::Time m_LastToggleEvent = sf::Time::Zero;

private:
	//	Which control scheme to use
	sf::Uint32 m_ControlScheme = ControlScheme::DEFAULT;
	
	//	Null command
	Command* noInput = new cmd_Null();

	//	Keyboard Keys we want to use
	Command* key_W			= nullptr;
	Command* key_A			= nullptr;
	Command* key_S			= nullptr;
	Command* key_D			= nullptr;
	Command* key_R			= nullptr;
	Command* key_SPACE		= nullptr;
	Command* key_RETURN		= nullptr;
	Command* key_BCKSPACE	= nullptr;
	Command* key_ESCAPE		= nullptr;

	//	Mouse Buttons we want to use
	Command* mouse_LMB	= nullptr;
	Command* mouse_RMB	= nullptr;
	Command* mouse_MMB	= nullptr;

	//	Gamepad Buttons we want to use
	Command* cont_CROSS						= nullptr;
	Command* cont_SQUARE					= nullptr;
	Command* cont_TRIANGLE					= nullptr;
	Command* cont_CIRCLE					= nullptr;
	Command* cont_L1						= nullptr;
	Command* cont_L2						= nullptr;
	Command* cont_R1						= nullptr;
	Command* cont_R2						= nullptr;
	Command* cont_LEFT_STICK_LEFT			= nullptr;
	Command* cont_LEFT_STICK_RIGHT			= nullptr;
	Command* cont_LEFT_STICK_UP				= nullptr;
	Command* cont_LEFT_STICK_DOWN			= nullptr;
	Command* cont_RIGHT_STICK_LEFT			= nullptr;
	Command* cont_RIGHT_STICK_RIGHT			= nullptr;
	Command* cont_RIGHT_STICK_UP			= nullptr;
	Command* cont_RIGHT_STICK_DOWN			= nullptr;
};

#endif // !INPUTHANDLER_H


