#pragma once
#include "Types.h"

class Field {
public:
	Field(int x, int y, int size = 200, State state = State::FREE_OFF)
		: x(x), y(y), m_size(size), m_state(state)
	{}
	int getX() { return x; }
	void setX(const int x) { this->x = x; }

	int getY() { return y; }
	void setY(const int y) { this->y = y; }

	int getSize() { return m_size; }
	void setSize(const int size) { m_size = size; }

	void setState(const State state) { m_state = state; }
	const State getState() { return m_state; }
private:
	int x;
	int y;
	int m_size;
	State m_state;
};