#include "Game.h"
#include <eng.h>

int main(int argc, char* argv[])
{
	Game* game = new Game();
	eng::Engine engine;
	engine.SetApplication(game);

	if (engine.Init(1280, 720))
	{
		engine.Run();
	}

	engine.Destroy();
    return 0;
}
