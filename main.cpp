#include "GameCore.h"


using namespace Core;
int main( int argc, char** argv )
{

	// Initialize library
	GameCore::initialize();

	//SceneManager::get().addGraphicsObject(  );

	// Game management
	Game* game = new Game();
	// - initialization
	game->initialize(false);
	game->menu();
	// - finalization
	game->finalize();
	delete game;
	game = nullptr;

	// Finalize library
	GameCore::finalize();

	return 0;
}
