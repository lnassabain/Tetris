#include <SDL.h>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>
#include <math.h>
#include "game.hpp"
#include "GraphicsObject.h"


Game::Game()
:	manager_( nullptr )
,	presenceMap_()
,	presenceMapB_()
,	score( 0 )
,	scoreB( 0 )
,	level( 1 )
,	tot_line( 0 )
, 	speed( 1000 )
{
}

Game::~Game()
{

}

void Game::initialize(bool multiplayer)
{
	manager_ = new SceneManager(multiplayer);
    /*Pour modeliser la grille, on cree une matrice booleenne. Lorsque l'objet
    arrete de bouger (touche le fond), on met la matrice à cette zone à true.
    De la même maniere, lorsqu'on deplace un objet, s'il touche une zone qui
    est a true, il y a collision*/
    presenceMap_.resize( manager_->get_nbRows(),
						 std::vector< int >( manager_->get_nbCol(), 0 ) );
	presenceMap_.push_back( std::vector< int >( manager_->get_nbCol(), 1 ) ); //le sol
	// for (int i = 0 ; i < presenceMap_.size() ; i++)
	// 	for (int j = 0 ; j < manager_->get_nbCol() ; j++)
	// 		std::cout<< i <<" " << j <<" " << (bool)presenceMap_[i][j] << std::endl;
	presenceMapB_.resize( manager_->get_nbRows(),
						 std::vector< int >( manager_->get_nbCol(), 0 ) );
	presenceMapB_.push_back( std::vector< int >( manager_->get_nbCol(), 1 ) );

}

void Game::finalize()
{
	delete manager_;
	manager_ = nullptr;
}


bool Game::collisionRotation(Graphics::GraphicsObject* obj, int scene_id)
{
	int rot = obj->getRotation();
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	int windowWidth = manager_->get_nbCol() * manager_->get_tileSize();
	int new_x, new_y;
	int placeXinPM, placeYinPM;
	int x_offset, y_offset;
	std::vector< std::vector< int > > presMap;

	switch(scene_id)
	{
		case 1:
			presMap = presenceMap_;
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			break;
		case 2:
			presMap = presenceMapB_;
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}

	const Graphics::TShape shapeTiles = obj->tiles_[(rot+1) % 4]; //la prochaine rotation
	for (const auto& p : shapeTiles)
	{
		new_x = x - x_offset + p.first * manager_->get_tileSize();
		new_y = y - y_offset + p.second * manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize(); //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / manager_->get_tileSize(); //On obtient l'indice y dans PresenceMap

		if (presMap[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}

		else if (new_x < 0)
		{
			return true;
		}

		else if (new_x > windowWidth - manager_->get_tileSize())
		{
			return true;
		}
	}

	return false;
}




bool Game::collisionLeft(Graphics::GraphicsObject* obj, int scene_id)
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	int new_x, new_y;
	int x_offset, y_offset;
	int placeXinPM, placeYinPM;
	std::vector< std::vector< int > > presMap;

	switch(scene_id)
	{
		case 1:
			presMap = presenceMap_;
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			break;
		case 2:
			presMap = presenceMapB_;
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;

	}

	const Graphics::TShape shapeTiles = obj->tiles_[ obj->getRotation() ]; //current rotation ID;
	for ( const auto& p : shapeTiles ) //tous les carrés
	{
		new_x = x - x_offset + (p.first-1) * manager_->get_tileSize();
		new_y = y - y_offset + (p.second) * manager_->get_tileSize();

		if (new_x < 0) // si le coin gauche du carré est inférieur à 0
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / manager_->get_tileSize();
			placeYinPM = new_y / manager_->get_tileSize();
			if (presMap[placeYinPM][placeXinPM] != 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::collisionRight(Graphics::GraphicsObject* obj, int scene_id)
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	int new_x, new_y;
	int x_offset, y_offset;
	int placeXinPM, placeYinPM;
	std::vector< std::vector< int > > presMap;
	int windowWidth = manager_->get_nbCol() * manager_->get_tileSize();

	switch(scene_id)
	{
		case 1:
			presMap = presenceMap_;
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			break;
		case 2:
			presMap = presenceMapB_;
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}

	const Graphics::TShape shapeTiles = obj->tiles_[obj->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x - x_offset + (p.first+1) * manager_->get_tileSize();
		new_y = y - y_offset + (p.second) * manager_->get_tileSize();

		if (new_x > windowWidth - manager_->get_tileSize())
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / manager_->get_tileSize();
			placeYinPM = new_y / manager_->get_tileSize();
			if (presMap[placeYinPM][placeXinPM] != 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::collisionDown(Graphics::GraphicsObject* obj, int scene_id)
{
	int new_x;
	int new_y;
	int placeXinPM; //place du carré dans le PresenceMap, coord. x
	int placeYinPM; //place du carré dans le PresenceMap, coord. y
	int x_offset, y_offset;
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	std::vector< std::vector< int > > presMap;

	switch(scene_id)
	{
		case 1:
			presMap = presenceMap_;
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			break;
		case 2:
			presMap = presenceMapB_;
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}


	const Graphics::TShape shapeTiles = obj->tiles_[obj->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x - x_offset + p.first * manager_->get_tileSize();
		new_y = y - y_offset + (p.second+1)*manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize(); //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / manager_->get_tileSize(); //On obtient l'indice y dans PresenceMap

		if (presMap[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}
	}

	return false;
}


bool Game::collisionCreation(Graphics::GraphicsObject* obj, int scene_id)
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	int new_x, new_y;
	int x_offset, y_offset;
	int placeXinPM, placeYinPM;
	std::vector< std::vector< int > > presMap;

	switch(scene_id)
	{
		case 1:
			presMap = presenceMap_;
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			break;
		case 2:
			presMap = presenceMapB_;
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			break;
		default:
			std::cerr << "Numero non valide" << std::endl;
			exit(1);
			break;
	}


	const Graphics::TShape shapeTiles = obj->tiles_[obj->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x - x_offset + p.first * manager_->get_tileSize();
		new_y = y - y_offset + p.second * manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize();
		placeYinPM = new_y / manager_->get_tileSize();

		if (presMap[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}
	}

	return false;
}


Graphics::GraphicsObject* Game::keyboard( const std::uint8_t* keys, Graphics::GraphicsObject* obj )
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	if (keys[SDL_SCANCODE_UP]){
		if (!collisionRotation(obj,1))
		{
			obj -> rotate();
		}
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		if (!collisionLeft(obj,1)) //test si possible de se deplacer vers la gauche
		{
			obj -> setPositionX(x-manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		if (!collisionRight(obj,1)) //test si possible de se deplacer vers la droite
		{
			obj -> setPositionX(x+manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		if (!collisionDown(obj,1)) //test si possible de se deplacer vers le bas
		{
			obj -> setPositionY(y+manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_SPACE]){
		while (!collisionDown(obj,1))
		{
			obj->setPositionY(obj->getPositionY()+manager_->get_tileSize());
		}
	}

	return obj;
}

Graphics::GraphicsObject* Game::cpuMove(Graphics::GraphicsObject* obj)
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	srand(time(NULL));
	int m = rand() % 6;

	switch(m)
	{
		case 0: //deplacement à gauche
			if (!collisionLeft(obj, 2))
			{
				obj -> setPositionX(x-manager_->get_tileSize());
			}
			break;
		case 1: //deplacement à droite
			if (!collisionRight(obj, 2))
			{
				obj -> setPositionX(x+manager_->get_tileSize());
			}
			break;
		case 2: //deplacement vers le bas
			if (!collisionDown(obj, 2))
			{
				obj -> setPositionY(y+manager_->get_tileSize());
			}
			break;
		case 3: //rotation
			if (!collisionRotation(obj, 2))
			{
				obj -> rotate();
			}
			break;
		case 4: //on ne fait rien
			break;
		case 5: //on drop la piece
			while (!collisionDown(obj, 2))
			{
				obj->setPositionY(obj->getPositionY()+manager_->get_tileSize());
			}
			break;
	}

	return obj;
}

Graphics::GraphicsObject* Game::shapeRand(){
	srand(time(NULL));
	int s = rand() % 7; //va de 0 à 6
	Graphics::GraphicsObject* obj;
	switch(s)
	{
		case 0:
			obj = Graphics::ShapeI::create();
			break;
		case 1:
			obj = Graphics::ShapeO::create();
			break;
		case 2:
			obj = Graphics::ShapeT::create();
			break;
		case 3:
			obj = Graphics::ShapeJ::create();
			break;
		case 4:
			obj = Graphics::ShapeL::create();
			break;
		case 5:
			obj = Graphics::ShapeS::create();
			break;
		case 6:
			obj = Graphics::ShapeZ::create();
			break;
		default:
			std::cerr << "Numero non valide" << std::endl;
			exit(1);
			break;
	}
	return obj;
}

/**
 * Check if there are lines to remove and do it. Increases the player score.
 * @return number of erased lines, to calculate the new score
 */
int Game::eraseLine(int scene_id)
{
	std::vector< std::vector< int > > presMap;
	int nb_complete = 0;
	std::stack <int> idx_erasedL; //pour la maj de presenceMap_
	idx_erasedL.push(-1); //pour aller jusqu'en haut dans la maj de presenceMap_

	switch (scene_id)
	{
		case 1:
			presMap = presenceMap_;
			break;
		case 2:
			presMap = presenceMapB_;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}

	// Parcourt toutes les lignes de presenceMap_ sauf la derniere qui est le sol
	for (size_t i = 0 ; i < presMap.size()-1 ; i++)
	{
		std::vector< int > line = presMap[i];
		size_t j = 0;

		// Cherche jusqu'où la ligne est remplie
		while (j < line.size() && line[j] != 0)
			j++;

		if (j == line.size()) //ligne completement remplie
		{
			nb_complete++;
			idx_erasedL.push(i); // on empile l'indice de la ligne

			manager_->drawEraseLine(i, scene_id);
		}
	}
	if (nb_complete != 0)
	{	// On met à jour presenceMap_
		// Les lignes qui ont été décalées :
		int& next_erasedL = idx_erasedL.top(); //on dépile la derniere ligne
		idx_erasedL.pop();

		size_t begin = next_erasedL; // à partir de la ligne qui a été enlevée
		for (size_t x = 1 ; x <= nb_complete ; x++) // x = numéro de la ligne complète en cours
		{
			int& next_erasedL = idx_erasedL.top(); // on dépile la ligne d'apres
			idx_erasedL.pop();
			size_t end = next_erasedL + x ; //exclue
			// on divise presenceMap_ en blocs de lignes séparés par les lignes enlevées
			for (size_t l = begin ; l > end ; l--)
			{
				presMap[ l ] = presMap[ l - x ];
			}
			begin = end;
		}

		// Les lignes vides en haut de l'écran dues à la disparition de lignes en dessous:
		for (int i = 0 ; i < nb_complete ; i ++)
			presMap[i] = std::vector<int>( manager_->get_nbCol(), 0 );
	}

	switch(scene_id)
	{
		case 1:
			presenceMap_ = presMap;
			break;
		case 2:
			presenceMapB_ = presMap;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}

	return nb_complete;
}

void Game::calcul_score(int nb_line, int scene_id)
{
	int sc_tmp; 
	switch(scene_id)
	{
		case 1:
			sc_tmp = score;
			break;
		case 2:
			sc_tmp = scoreB;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}

	switch (nb_line)
	{
		case 0 :
			return;
		case 1 :
			sc_tmp += 40 * level;
			tot_line += 1;
			break;
		case 2 :
			sc_tmp += 100 * level;
			tot_line += 3;
			break;
		case 3 :
			sc_tmp += 300 * level;
			tot_line += 5;
			break;
		case 4 :
			sc_tmp += 1200 * level;
			tot_line += 8;
			std::cout << "TETRIS !" << std::endl;
			break;
		default :
			std::cerr << "default case in switch(nb_line) in calcul_score" << std::endl;
			exit(1);
	}
	switch (scene_id)
	{
		case 1:
			score = sc_tmp;
			std::cout << "New score : " << score << std::endl;
			break;
		case 2:
			scoreB = sc_tmp;
			std::cout << "New CPU score : " << scoreB << std::endl;
			break;
		default:
			std::cerr << "Numero de scene non valide" << std::endl;
			exit(1);
			break;
	}
}

void Game::levelUp()
{
	if ( tot_line >= 10 * (level) )
	{
		level ++;
		double mult = 0.8 - (level-1) * 0.007 ;
		speed = mult;
		for (int i = 0 ; i < level-2 ; i++)
			speed *= mult;
		speed *= 1000;
		std::cout << "LEVEL UP : " << level << std::endl;
	}

	if (level == 16)
	{
		std::cout << "LEVEL 15 COMPLETED : SCORE = " << score
				  << " CONGRATULATION !" << std::endl;
		exit(0);
	}
}


void Game::addToPresMap(Graphics::GraphicsObject* obj, int scene_id)
{
	int carre_x, carre_y;
	int placeXinPM, placeYinPM;
	int x = obj -> getPositionX();
	int y = obj -> getPositionY();
	int colID = obj->getColor();
	int x_offset, y_offset;

	switch(scene_id)
	{
		case 1:
			x_offset = X_OFFSET;
			y_offset = Y_OFFSET;
			for (const auto& p : obj->tiles_[ obj->getRotation() ] )
			{
				carre_x = x - x_offset + p.first*manager_->get_tileSize();
				carre_y = y - y_offset + p.second*manager_->get_tileSize();

				placeXinPM = carre_x / manager_->get_tileSize();
				placeYinPM = carre_y / manager_->get_tileSize();

				presenceMap_[placeYinPM][placeXinPM] = colID;
			}
			break;
		case 2:
			x_offset = X2_OFFSET;
			y_offset = Y2_OFFSET;
			for (const auto& p : obj->tiles_[ obj->getRotation() ] )
			{
				carre_x = x - x_offset + p.first*manager_->get_tileSize();
				carre_y = y - y_offset + p.second*manager_->get_tileSize();

				placeXinPM = carre_x / manager_->get_tileSize();
				placeYinPM = carre_y / manager_->get_tileSize();

				presenceMapB_[placeYinPM][placeXinPM] = colID;
			}
			break;
		default:
			std::cerr << "Numero non valide" << std::endl;
			exit(1);
			break;
	}


	return;
}


void Game::loop(bool multiplayer)
{
	bool quit = false;
	bool toucheFond = true;
	bool toucheFondB = true;
	int lastTime=0;
	int currentTime;
	Graphics::GraphicsObject* co;
	Graphics::GraphicsObject* coB;
	Graphics::GraphicsObject* next = shapeRand();

	while ( !quit )
	{

		bool check_key = false; //un bouton a été appuyé si true
		int y;

		if (toucheFond==true)
		{
			//object = *next; //copie
			co = next;

			if(collisionCreation(co,1))
			{
				std::cout << "GAME OVER. SCORE : " << score << " | LEVEL : " << level
						<< std::endl;
				exit(0);
			}

			// Prochain objet
			next = shapeRand();
			draw(co, next, 1);
			toucheFond = false;
			SDL_Delay(400);
		}


		if(multiplayer && toucheFondB==true)
		{
			//On cree l'objet pour la deuxieme fenetre
			coB = shapeRand();
			coB -> setPositionX(coB->getPositionX() + 555);
			if(collisionCreation(coB,2))
			{
				std::cout << "GAME OVER. YOUR SCORE: " << score << std::endl;
				std::cout << "GAME OVER. SCORE CPU: " << scoreB << std::endl;
				exit(0);
			}
			draw(coB, next, 2);
			toucheFondB = false;
		}

		// Event management
		SDL_Event event;
		while ( !quit && SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					check_key= true;
					break;

			}
		}
		//keyboard management
		if (check_key==true)
		{
			const Uint8* state = SDL_GetKeyboardState(NULL);
			co = keyboard(state, co);
			quit |= state[ SDL_SCANCODE_ESCAPE ];
			check_key = false;
		}

		if(multiplayer)
		{
			coB = cpuMove(coB);
		}

		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + speed)
		{
			if (multiplayer)
			{
				if (!collisionDown(coB, 2))
				{
					y = coB -> getPositionY();
					coB->setPositionY(y + manager_->get_tileSize());
				}
				else
				{
					toucheFondB = true;
					addToPresMap(coB,2);
				}
			}
			if (!collisionDown(co,1)) //si on peut se deplacer vers le bas
			{
				y = co -> getPositionY();
				//on se deplace vers le bas
				co -> setPositionY(y + manager_->get_tileSize());
			}
			else
			{
				toucheFond = true;
				// on l'ajoute à la matrice de presence
				addToPresMap(co,1);
			}
			lastTime = currentTime;
		}

		int nb_line = eraseLine(1);
		calcul_score(nb_line, 1);
		levelUp();
		draw(co, next, 1);

		if(multiplayer)
		{
			int nb_lineB = eraseLine(2);
			calcul_score(nb_lineB, 2);
			draw(coB, next, 2);
		}
	}
	return;
}


/**
 * Draws the shadow of the current piece on the floor
 */
void Game::drawShadow(Graphics::GraphicsObject* obj, int scene_id)
{
	// On cherche où serait la pièce au sol ; code de SPACE
	int x = obj->getPositionX();
	int y = obj->getPositionY();

	Graphics::GraphicsObject shadow = *obj; //copie

	int y_new = y;
	while (!collisionDown(&shadow, scene_id))
	{
		y_new += manager_->get_tileSize();
		shadow.setPositionY(y_new);
	}

	manager_->drawShadow(shadow, scene_id);
}



void Game::draw(Graphics::GraphicsObject* obj, Graphics::GraphicsObject* next, int scene_id)
{
	manager_->drawBg(0, manager_->get_nbRows(), scene_id);
	drawShadow(obj, scene_id);
	manager_->drawShape(obj, scene_id);
	switch (scene_id)
	{
		case 1:
			manager_->drawPresMap(presenceMap_, scene_id);
			break;
		case 2:
			manager_->drawPresMap(presenceMapB_, scene_id);
			break;
		default:
			std::cerr << "Numero non valide" << std::endl;
			exit(1);
			break;
	}

	manager_->display_1p();
	manager_->displayFigure(score, 430, 70);
	manager_->displayFigure(level, 430, 205);
	manager_->displayNext(next);


	manager_->update();
}


void Game::menu()
{
	int mode = 0 ;
	manager_->displayMenu(mode);

	bool quit = false;
	SDL_Event event;
	while ( !quit )
	{
		SDL_PollEvent( &event );
		//std::cout << "boucle while, event type = " << event.type << std::endl;

		switch ( event.type )
		{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				const Uint8* key = SDL_GetKeyboardState(NULL);
				if (key[SDL_SCANCODE_DOWN])
				{
					mode ++;
					mode %= 3;
				}
				if (key[SDL_SCANCODE_UP])
				{
					if (mode == 0)
						mode = 2;
					else
						mode --;
				}
				if (key[SDL_SCANCODE_RETURN])
				{
					if (mode == 0)
					{
						initialize(false);
						loop(false);
						SDL_Quit();
						return;
					}
					else if (mode == 1)
					{
						initialize(true);
						loop(true);
						SDL_Quit();
						return;
					}
					else
					{
						quit = true;
					}
				}

				manager_->displayMenu(mode);

			//	quit |= key[ SDL_SCANCODE_ESCAPE ];
				break;

		}
		SDL_Delay(100);
	}




	//loop(); //lance le jeu
}
