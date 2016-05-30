#include <iostream>
#include <string>
#include <SDL.h>
#include "Game.h"

int main(int argc, char* args[]) {
	SDLGame* g = new SDLGame(std::string("TicTacToe"));
	if (!g) return 0;
	if (!g->init(200, 3)) return 0;
	g->playOffline();
	return 0;
}