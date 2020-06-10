#include <iostream>
#include <Windows.h>
#include <thread>
#include "consoleEngine.h"


int main() {
	//consoleEngine::Console myConsole = consoleEngine::Console(80, 30);

	//myConsole.fillBackground(L' ', consoleEngine::COLOUR::BG_BLUE);

	//myConsole.drawRect(10, 10, 1, 1, consoleEngine::BG_DARK_MAGENTA, L' ', true);

	//myConsole.drawLine(0,0, 7, 16, consoleEngine::COLOUR::BG_DARK_YELLOW, L' ');

	consoleEngine::Game myGame = consoleEngine::Game(80, 30);
	myGame.start();
	std::cin.get();
}