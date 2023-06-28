#include "StdKeyBoardCtrlScheme.hpp"
#include "Command.hpp"
#include "InitMoveLeft.hpp"
#include "StopMoveLeft.hpp"
#include "InitMoveRight.hpp"
#include "StopMoveRight.hpp"
#include "InitJump.hpp"
#include "Logger.hpp"
#include "NullCommand.hpp"
#include "ProjectDefs.hpp"

using std::vector; using std::shared_ptr;

StdKeyControlScheme::StdKeyControlScheme() {
	/*
	Create the mapping

	The convention we follow is that an action to be taken on keydown
	will be the first element in the vector, an an action to be take on 
	keyup will be the second element
	*/
	
	vector<shared_ptr<Command>> handleMoveLeft = { std::make_shared<InitMoveLeft>(), std::make_shared<StopMoveLeft>() };
	this->m_key_evt_to_command_map.emplace(SDLK_a, std::move(handleMoveLeft));
	
	vector<shared_ptr<Command>> handleMoveRight = { shared_ptr<Command>(new InitMoveRight()), shared_ptr<Command>(new StopMoveRight()) };
	this->m_key_evt_to_command_map.emplace(SDLK_d, std::move(handleMoveRight));
	
	vector<shared_ptr<Command>> handleJump = { shared_ptr<Command>(new InitJump()) };
	this->m_key_evt_to_command_map.emplace(SDLK_w, std::move(handleJump));


	//this->m_key_evt_to_command_map.emplace(SDLK_a, { std::make_shared<InitMoveLeft>(), std::make_shared<StopMoveLeft>() });
	//this->m_key_evt_to_command_map.emplace(SDLK_d, { std::make_shared<InitMoveRight>(), std::make_shared<StopMoveRight>() });
	//this->m_key_evt_to_command_map.emplace(SDLK_w, { std::make_shared<InitJump>());
}
		
shared_ptr<Command> StdKeyControlScheme::translate_key_evt_to_command(SDL_Event *evt) {
	using std::vector;
	CHECK_IF_POINTER_VALID(evt);

	SDL_Keycode key = evt->key.keysym.sym;

	if (m_key_evt_to_command_map.contains(key)) {
		vector<shared_ptr<Command>> translatedEvent = m_key_evt_to_command_map.at(key);
		if ((translatedEvent.size() == 1) || (translatedEvent.size() > 1 && evt->type == SDL_EventType::SDL_KEYDOWN)) {
			return translatedEvent[0];
		}

		else if (translatedEvent.size() > 1 && evt->type == SDL_EventType::SDL_KEYUP) {
			return translatedEvent[1];
		}
	}


	else {
		LOG_MESSAGE("No command specified for key");
		return std::make_shared<NullCommand>();
	}

			
}


	

