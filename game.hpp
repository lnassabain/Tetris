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

	Graphics::GraphicsObject* shapeRand(); //Cree un Graphisc objet de type aléatoire( I, J etc.)
	Graphics::GraphicsObject* getCurrObj(); //Getter de l'objet courant
	void setCurrObj(Graphics::GraphicsObject* obj); //Setter de l'objet courant
	int eraseLine();
	bool collisionLeft();
	bool collisionRight();
	bool collisionDown();

protected:
	/*Graphics window*/
	Window* window_;

	void draw( double dt );
	void drawShape(Graphics::GraphicsObject* obj); //a voir si ce serait pas drawCurrentObject
	void drawBg(int y, int nbLines);

    /*Keyboard management*/
	void keyboard( const std::uint8_t* keys );

private:
	Surface* planche_;
	std::vector< Sprite* > sprites_;

	std::vector< std::vector< bool > > presenceMap_;

	void drawMap();

	//eventuellement à mettre dans un objet grid ?
	int grid_nbRows_;
	int grid_nbColumns_;
	int grid_tileSize_;
	Graphics::GraphicsObject* current_obj;

};

#endif
