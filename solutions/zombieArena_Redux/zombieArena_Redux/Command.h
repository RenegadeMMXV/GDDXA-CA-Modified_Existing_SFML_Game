/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"

/**
*	Parent/Superclass
*/
class Command {
public:
	virtual ~Command() { /*delete this;*/ }
	virtual void execute(Player& pc) = 0;
};

/*
*	Command supplied as Default when controller input is NULL
*/
class cmd_Null : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::IDLE;
		pc.m_Movement_H = PlayerCharacter::Movement_H::IDLE;
	}
};

/**
*	Set the Character to run Up
*/
class cmd_RunUp : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::UP;
	}
};

/**
*	Set the Character to run Left
*/
class cmd_RunLeft : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Movement_H = PlayerCharacter::Movement_H::LEFT;
	}
};

/**
*	Set the Character to run Down
*/
class cmd_RunDown : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::DOWN;
	}
};

/**
*	Set the Character to run Right
*/
class cmd_RunRight : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Movement_H = PlayerCharacter::Movement_H::RIGHT;
	}
};

/**
*	Set the Character to Attacking
*/
class cmd_Attack : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Action = PlayerCharacter::Action::ATTACKING;
	}
};

#endif // !COMMAND_H