#include "Game.h"
#include "GameMode.h"

int main()
{

	Game game = Game(4, 6, 3840, 2160, GameMode::Mode2D, "GameWindow");

	while (!glfwWindowShouldClose(game.GetWindow()))
	{
		game.MainLoop();
	}

	return 0;
}
































