#ifndef _GAME_H_
#define _GAME_H_

#include <cstdint>
#include <vector>
#include <list>

#include "window.h"
#include "sprite.h"
#include "surface.h"
#include "GraphicsObject.h"
#include "sceneManager.hpp"


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

	void addToPresMap(Graphics::GraphicsObject* obj); //Noie un objet dans la presenceMap
	int eraseLine();

	bool collisionCreation(Graphics::GraphicsObject* obj); //teste si on peut creer un nouvel objet courant sans qu'il y ait de collision, sinon game over
	bool collisionLeft();
	bool collisionRight();
	bool collisionDown(Graphics::GraphicsObject* obj);
	bool collisionRotation();

protected:
    /*Keyboard management*/
	void keyboard( const std::uint8_t* keys );

private:
	std::vector< std::vector< int > > presenceMap_;
	void drawMap();
	SceneManager* manager_;
	void drawShadow();
	void draw();


	Graphics::GraphicsObject* current_obj;

	int score;
	int level;
	int tot_line;
	double speed;
	void calcul_score(int nb_line);
	void levelUp();

};

#endif
