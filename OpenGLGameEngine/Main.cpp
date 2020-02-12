#include "Game.h"
#include "GameMode.h"
#include "../OpenGL.Base/GLWindow.h"
#include "../DirectX11.Base/DirectXWindow.h"

int main()
{

	Game game = Game(4, 6, 3840, 2160, GameMode::Mode3D, "GameWindow");

	while (!glfwWindowShouldClose(game.GetWindow()))
	{
		game.MainLoop();
	}

	return 0;
}