#include "Game.h"
#include <eng.h>

int main(int argc, char* argv[])
{
	Game* game = new Game();
	eng::Engine& engine = eng::Engine::GetInstance();
	engine.SetApplication(game);

	if (engine.Init(1920, 1080))
	{
		engine.Run();
	}

	engine.Destroy();
    return 0;
}
