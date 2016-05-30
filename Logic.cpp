#include "Logic.h"

RandomLogic::RandomLogic()
	: generator(std::chrono::system_clock::now().time_since_epoch().count()) {}

bool RandomLogic::move(std::shared_ptr<Board> board, Player& player,
	SDL_Keycode event) {
	const int max = 3;
	int i = 0;
	int x = (generator() - 1) % max;
	int y = (generator() - 1) % max;
	while (board->getState(x, y) != State::FREE_OFF &&
		board->getState(x, y) != State::FREE_ON) {
		x = (generator() - 1) % max;
		y = (generator() - 1) % max;
		if (++i > 1000) return false;
	}
	State s = player.getType() == PLAYER_TYPE::CIRCLE ? State::CIRCLE_OFF
		: State::CROSS_OFF;
	board->setState(x, y, s);
	return true;
}
bool HumanLogic::move(std::shared_ptr<Board> board, Player& player,
	SDL_Keycode event) {
	switch (event) {
	case SDLK_UP:  // up - vertical
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		y = (y <= MIN_Y_CORDINATE) ? MAX_Y_CORDINATE : y - 1;
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		break;
	case SDLK_DOWN:  // down - vertical
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		y = (y >= MAX_Y_CORDINATE) ? MIN_Y_CORDINATE : y + 1;
		board->setState(x, y, switchState(player, board->getState(x, y), event));

		break;
	case SDLK_LEFT:  // left - horizontal
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		x = (x <= MIN_X_CORDINATE) ? MAX_X_CORDINATE : x - 1;
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		break;
	case SDLK_RIGHT:  // right - horizontal
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		x = (x >= MAX_X_CORDINATE) ? MIN_X_CORDINATE : x + 1;
		board->setState(x, y, switchState(player, board->getState(x, y), event));
		break;
	case SDLK_RETURN:  // select
		State sb = board->getState(x, y);
		State sa = switchState(player, sb, event);
		board->setState(x, y, sa);
		return sa != sb;
	}
	return false;
}
State HumanLogic::switchState(const Player& player, const State s,
	const SDL_Keycode k) {
	switch (k) {
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_RIGHT:
	case SDLK_LEFT:
		switch (s) {
		case State::FREE_ON:
			return State::FREE_OFF;
		case State::FREE_OFF:
			return State::FREE_ON;
		case State::CIRCLE_ON:
			return State::CIRCLE_OFF;
		case State::CIRCLE_OFF:
			return State::CIRCLE_ON;
		case State::CROSS_ON:
			return State::CROSS_OFF;
		case State::CROSS_OFF:
			return State::CROSS_ON;
		}
	case SDLK_RETURN:
		switch (s) {
		case State::FREE_ON:
			return (player.getType() == PLAYER_TYPE::CIRCLE) ? State::CIRCLE_ON
				: State::CROSS_ON;
		case State::CROSS_OFF:
			return State::CROSS_ON;
		case State::CROSS_ON:
			return State::CROSS_ON;
		case State::CIRCLE_OFF:
			return State::CIRCLE_ON;
		case State::CIRCLE_ON:
			return State::CIRCLE_ON;
		}
	}
}