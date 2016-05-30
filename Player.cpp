#include "Player.h"
Player::Player(const PLAYER_TYPE t, std::string& logic) : winCounter(0), m_type(t) { m_logic = create(logic); }

const PLAYER_TYPE Player::getType() const { return m_type; }
void Player::wins() { ++winCounter; }
const int Player::getWins() { return winCounter; }

bool Player::move(std::shared_ptr<Board> board, SDL_Keycode event) { 
	return m_logic->move(board, *this, event); 
}

std::shared_ptr<Logic> Player::create(const std::string& name) {
	if (name == "Human") return std::make_shared<HumanLogic>();
	else if (name == "RandomLogic") return std::make_shared<RandomLogic>();
}
void Player::reset() {
	m_logic->reset();
}