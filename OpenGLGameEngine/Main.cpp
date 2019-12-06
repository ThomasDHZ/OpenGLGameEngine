#include "Game.h"
#include "GameMode.h"

int main()
{

	Game game = Game(4, 6, 1280, 720, GameMode::Mode2D, "GameWindow");

	while (!glfwWindowShouldClose(game.GetWindow()))
	{
		game.MainLoop();
	}

	return 0;
}
































