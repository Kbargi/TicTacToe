#pragma once
#include <utility>
#include <random>
#include <chrono>
#include <memory>
#include <map>
#include <string>

#include <SDL.h>
#include "Board.h"
#include "Player.h"
class Player;
class Logic {
public:
	virtual bool move(std::shared_ptr<Board> board, Player& player,
		SDL_Keycode event) = 0;
	virtual void reset() {};
	virtual ~Logic() {};
};

class RandomLogic : public Logic {
public:
	RandomLogic();
	virtual bool move(std::shared_ptr<Board> board, Player& player,
		SDL_Keycode event);
	virtual ~RandomLogic() {};

private:
	std::minstd_rand0 generator;
};

class HumanLogic : public Logic {
public:
	HumanLogic() : x(0), y(0) {}
	virtual bool move(std::shared_ptr<Board> board, Player& player,
		SDL_Keycode event);
	virtual void reset() { x = y = 0; }

private:
	State switchState(const Player& player, const State s, const SDL_Keycode k);
	int x;
	int y;
};
