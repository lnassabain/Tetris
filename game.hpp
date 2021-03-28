#ifndef _GAME_H_
#define _GAME_H_

#include <cstdint>
#include <vector>
#include <list>

#include "window.h"
#include "sprite.h"
#include "surface.h"
#include "GraphicsObject.h"

// class Window;
// class Surface;
// class Sprite;



class Game
{
public:
	Game();
	virtual ~Game();

	void initialize();
	void finalize();
    void loop();
	Graphics::GraphicsObject* shapeRand();

protected:
	/*Graphics window*/
	Window* window_;

	void draw( double dt );

    /*Keyboard management*/
	void keyboard( const std::uint8_t* keys );

private:
	Surface* planche_;
	std::vector< Sprite* > sprites_;

	std::list< std::vector< bool > > presenceMap_;

	void drawMap();

	//eventuellement à mettre dans un objet grid ?
	int grid_nbRows_;
	int grid_nbColumns_;
	int grid_tileSize_;

};

#endif
