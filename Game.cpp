#include "Game.h"
#include <Windows.h>

bool SDLGame::init(int fieldSize, int fields) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	else {
		if ((m_window = SDL_CreateWindow(
			name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			fieldSize * fields, fieldSize * fields, SDL_WINDOW_SHOWN)) == NULL)
			return false;
		else if ((background = SDL_GetWindowSurface(m_window)) == NULL)
			return false;
		if (!(m_board = std::make_shared<Board>(fields, fields, fieldSize)))
			return false;
	}
	return m_board->init(std::string("fields\\"));
}
SDLGame::~SDLGame() {
	SDL_FreeSurface(background);
	background = NULL;
	SDL_DestroyWindow(m_window);
	m_window = NULL;

	SDL_Quit();
}

void SDLGame::playOffline() {
	SDL_Event event;
	std::vector<Player> players;
	// make it random
	players.push_back(Player(PLAYER_TYPE::CROSS, std::string("Human")));
	players.push_back(Player(PLAYER_TYPE::CIRCLE, std::string("RandomLogic")));

	m_board->printBoard(m_window, background);

	while (!m_stop) {
		while (SDL_PollEvent(&event)) {
			m_board->printBoard(m_window, background);
			switch (event.type) {
			case SDL_QUIT:
				m_stop = true;
				break;
			case SDL_KEYDOWN:
				if (players[0].move(m_board, event.key.keysym.sym)) {
					players[1].move(m_board, event.key.keysym.sym);
					m_board->printBoard(m_window, background);
				}
				switch (m_board->checkResult()) {
				case WINNER::PLUS:
					std::cout << "Krzyzyk wygral\n";
					m_board->printBoard(m_window, background);
					Sleep(1000);
					m_board->reset();
					players[0].reset();
					players[1].reset();
					break;
				case WINNER::CIRC:
					std::cout << "kolko wygralo\n";
					m_board->printBoard(m_window, background);
					Sleep(1000);
					m_board->reset();
					players[0].reset();
					players[1].reset();
					break;
				case WINNER::NONE:
					std::cout << "nie ma zwyciezcy!\n";
					players[0].reset();
					players[1].reset();
					m_board->reset();
					break;
				case WINNER::NOT_FINISHED:
					break;
				}
				break;
			}
		}  // enf of event handling loop
	}  // end of main loop
}
