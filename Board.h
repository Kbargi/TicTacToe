#pragma once
#include <map>
#include "Field.h"
#include "SDL.h"
class Board {
public:
	Board(const int x, const int y, const int size/*pix*/);
	~Board();
	bool init(std::string& path);
	void printBoard(SDL_Window* window, SDL_Surface *screen);
	void printField(SDL_Window* window, SDL_Surface *screen, int x, int y);
	void setState(int x, int y, State state);
	const State getState(int x, int y);
	WINNER checkResult();
	void reset();
private:
	int m_size;
	int xFieldsNum;
	int yFieldsNum;
	std::map<std::pair<int, int>, Field> m_fields;
	std::map<State, SDL_Surface*> m_graphs;
};