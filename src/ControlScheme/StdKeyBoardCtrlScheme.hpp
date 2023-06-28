#pragma once

#include <map>
#include <memory>
#include <vector>
#include "Command.hpp"
#include "ControlScheme.hpp"
#include "SDL.h"



class StdKeyControlScheme : public ControlScheme {

public:
	StdKeyControlScheme();
	virtual ~StdKeyControlScheme() = default;
	std::shared_ptr<Command> translate_key_evt_to_command(SDL_Event *evt) override;


private:
	std::map<SDL_Keycode, std::vector<std::shared_ptr<Command>>> m_key_evt_to_command_map;

};