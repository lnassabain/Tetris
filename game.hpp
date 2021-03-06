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

	void initialize(bool multiplayer);
	void finalize();
    void loop(bool multiplayer);
	void menu();

	Graphics::GraphicsObject* shapeRand(); //Cree un Graphisc objet de type aléatoire( I, J etc.)

	void addToPresMap(Graphics::GraphicsObject* obj, int scene_id); //Noie un objet dans la presenceMap
	int eraseLine(int scene_id);

	bool collisionCreation(Graphics::GraphicsObject* obj, int scene_id); //teste si on peut creer un nouvel objet courant sans qu'il y ait de collision, sinon game over
	bool collisionLeft(Graphics::GraphicsObject* obj, int scene_id); //verifie si deplacement gauche possible
	bool collisionRight(Graphics::GraphicsObject* obj, int scene_id); //verifie si deplacement droite possible
	bool collisionDown(Graphics::GraphicsObject* obj, int scene_id);  //verifie si deplacement bas possible
	bool collisionRotation(Graphics::GraphicsObject* obj, int scene_id);  //verife si rotation possible

protected:
    /*Keyboard management*/
	/*Renvoie l'objet qu'on a deplacé(ou pas)*/
	Graphics::GraphicsObject* keyboard( const std::uint8_t* keys, Graphics::GraphicsObject* obj );

	//fonction qui gere toute seule les deplacements d'une piece
	Graphics::GraphicsObject* cpuMove(Graphics::GraphicsObject* obj);

private:
	std::vector< std::vector< int > > presenceMap_;
	std::vector< std::vector< int > > presenceMapB_; //presence map bis pour la deuxieme scene
	void drawMap();
	SceneManager* manager_;
	void drawShadow(Graphics::GraphicsObject* obj, int scene_id);
	void draw(Graphics::GraphicsObject* obj, Graphics::GraphicsObject* next,
			  int scene_id, bool multiplayer);


	int score;
	int scoreB; //score de l'ordi
	int level;
	int tot_line;
	double speed;
	void calcul_score(int nb_line, int scene_id);
	void levelUp(bool multiplayer);

};

#endif
