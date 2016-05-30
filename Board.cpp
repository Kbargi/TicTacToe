#include "Logic.h"

Board::Board(const int x, const int y, const int size/*pix*/) : m_size(size), xFieldsNum(x), yFieldsNum(y) {
	State s = State::FREE_ON;
	for (int i = 0; i < xFieldsNum; ++i) {
		for (int j = 0; j < yFieldsNum; ++j) {
			m_fields.insert(std::pair<std::pair<int, int>, Field>(std::make_pair(i, j), Field(i, j, size, s)));
			s = State::FREE_OFF;
		}
	}
}
Board::~Board() {
	for (std::map<State, SDL_Surface*>::iterator it = m_graphs.begin(); it != m_graphs.end(); ++it) {
		SDL_FreeSurface(it->second);
		it->second = NULL;
	}
}
WINNER Board::checkResult() {
	int res_x = 0;
	int res_o = 0;
	int x = 0;
	int y = 0;
	bool free = false;
	State s = State::END_OF_STATES;
	for (y = 0; y <= MAX_Y_CORDINATE; ++y) {
		for (x = 0; x <= MAX_X_CORDINATE; ++x) {
			s = getState(x, y);
			if (s == State::CIRCLE_OFF || s == State::CIRCLE_ON)
				++res_o;
			else if (s == State::CROSS_OFF || s == State::CROSS_ON)
				++res_x;
		}
		if (x > MAX_X_CORDINATE) --x;
		if (res_x == xFieldsNum) {
			setState(x, y, State::CROSS_ON);
			setState(x - 1, y, State::CROSS_ON);
			setState(x - 2, y, State::CROSS_ON);
			return WINNER::PLUS;
		}
		else if (res_o == xFieldsNum) {
			setState(x, y, State::CIRCLE_ON);
			setState(x - 1, y, State::CIRCLE_ON);
			setState(x - 2, y, State::CIRCLE_ON);
			return WINNER::CIRC;
		}
		res_o = res_x = 0;
	}
	res_x = res_o = x = y = 0;
	for (y = 0; y <= MAX_Y_CORDINATE; ++y) {
		for (x = 0; x <= MAX_X_CORDINATE; ++x) {
			s = getState(y, x);
			if (s == State::CIRCLE_OFF || s == State::CIRCLE_ON)
				++res_o;
			else if (s == State::CROSS_OFF || s == State::CROSS_ON)
				++res_x;
			else
				free = true;
		}
		if (x > MAX_X_CORDINATE) --x;
		if (res_x == xFieldsNum) {
			setState(y, x, State::CROSS_ON);
			setState(y, x - 1, State::CROSS_ON);
			setState(y, x - 2, State::CROSS_ON);
			return WINNER::PLUS;
		}
		else if (res_o == xFieldsNum) {
			setState(y, x, State::CIRCLE_ON);
			setState(y, x - 1, State::CIRCLE_ON);
			setState(y, x - 2, State::CIRCLE_ON);
			return WINNER::CIRC;
		}
		res_o = res_x = 0;
	}
	res_o = res_x = 0;
	for (x = 0; x <= MAX_X_CORDINATE; ++x) {
		State s = getState(x, x);
		if (s == State::CIRCLE_OFF || s == State::CIRCLE_ON)
			res_o++;
		else if (s == State::CROSS_OFF || s == State::CROSS_ON)
			res_x++;
	}
	if (x > MAX_X_CORDINATE) --x;
	if (res_x == xFieldsNum) {
		setState(x, x, State::CROSS_ON);
		setState(x - 1, x - 1, State::CROSS_ON);
		setState(x - 2, x - 2, State::CROSS_ON);
		return WINNER::PLUS;
	}
	else if (res_o == xFieldsNum) {
		setState(x, x, State::CIRCLE_ON);
		setState(x - 1, x - 1, State::CIRCLE_ON);
		setState(x - 2, x - 2, State::CIRCLE_ON);
		return WINNER::CIRC;
	}

	res_x = res_o = 0;
	if ((getState(2, 0) == State::CIRCLE_ON || getState(2, 0) == State::CIRCLE_OFF)
		&& (getState(1, 1) == State::CIRCLE_ON || getState(1, 1) == State::CIRCLE_OFF)
		&& (getState(0, 2) == State::CIRCLE_ON || getState(0, 2) == State::CIRCLE_OFF))
	{
		setState(2, 0, State::CIRCLE_ON);
		setState(1, 1, State::CIRCLE_ON);
		setState(0, 2, State::CIRCLE_ON);
		return WINNER::CIRC;
	}
	else if (
		(getState(2, 0) == State::CROSS_ON || getState(2, 0) == State::CROSS_OFF)
		&& (getState(1, 1) == State::CROSS_ON || getState(1, 1) == State::CROSS_OFF)
		&& (getState(0, 2) == State::CROSS_ON || getState(0, 2) == State::CROSS_OFF))
	{
		setState(2, 0, State::CROSS_ON);
		setState(1, 1, State::CROSS_ON);
		setState(0, 2, State::CROSS_ON);
		return WINNER::PLUS;
	}
	if (free) return WINNER::NOT_FINISHED;
	else return WINNER::NONE;
}
bool Board::init(std::string& path) {
	std::string tPath = path;
	const size_t pos = path.size();
	tPath += "x.bmp";
	for (int it = State::CIRCLE_OFF; it < State::END_OF_STATES; ++it) {
		tPath[pos] = std::to_string(it).c_str()[0];
		SDL_Surface* s = SDL_LoadBMP(tPath.c_str());
		if (!s) return false;
		m_graphs[static_cast<State>(it)] = s;
	}
	return true;
}
void Board::reset() {
	for (int x = 0; x < xFieldsNum; ++x) {
		for (int y = 0; y < yFieldsNum; ++y) {
			setState(x, y, State::FREE_OFF);
		}
	}
	setState(0, 0, State::FREE_ON);
}
void Board::printBoard(SDL_Window* window, SDL_Surface *screen) {
	if (!screen || !window) return;
	for (int x = 0; x < xFieldsNum; ++x) {
		for (int y = 0; y < yFieldsNum; ++y) {
			printField(window, screen, x, y);
		}
	}
}

void Board::printField(SDL_Window* window, SDL_Surface *screen, int x, int y) {
	if (!screen || !window) return;
	SDL_Rect t;
	Field& f = m_fields.at(std::make_pair(x, y));
	SDL_Surface* s = m_graphs.at(f.getState());
	if (!s) { return; }
	t.x = f.getX() * f.getSize();
	t.y = f.getY() * f.getSize();
	SDL_BlitSurface(s, NULL, screen, &t);
	SDL_UpdateWindowSurface(window);
}
void Board::setState(int x, int y, State state) {
	Field& f = m_fields.at(std::make_pair(x, y));
	f.setState(state);
}
const State Board::getState(int x, int y) {
	Field& f = m_fields.at(std::move(std::make_pair(x, y)));
	return f.getState();
}