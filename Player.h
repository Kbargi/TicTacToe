#pragma once
#include <string>
#include <memory>
#include <SDL.h>
#include "Logic.h"
#include "Types.h"
#include "Board.h"
class Logic;
class Player {
public:
	Player(const PLAYER_TYPE t, std::string& logic);

	const PLAYER_TYPE getType() const;
	void wins();
	const int getWins();
	bool move(std::shared_ptr<Board> board, SDL_Keycode event);
	void reset();
private:
	std::shared_ptr<Logic> create(const std::string& name = std::string("Human"));
	int winCounter;
	PLAYER_TYPE m_type;
	std::shared_ptr<Logic> m_logic;
};