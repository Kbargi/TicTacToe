#pragma once

#include <iostream>
#include <string>
#include <map>
#pragma once
#include <memory>
#include <vector>
#include <SDL.h>

#include "Logic.h"



class SDLGame {
public:
	SDLGame(std::string& name) : name(name), m_stop(false) {}

	~SDLGame();

	bool init(int, int);

	void playOffline();
private:
	std::string name;
	SDL_Window* m_window;
	SDL_Surface* background;
	std::shared_ptr<Board> m_board;
	bool m_stop;
};

