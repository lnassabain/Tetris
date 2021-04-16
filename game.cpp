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
,	current_obj( nullptr )
,	score( 0 )
,	level( 1 )
,	tot_line( 0 )
, 	speed( 1000 )
{
}

Game::~Game()
{

}

void Game::initialize()
{
	manager_ = new SceneManager();

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

}

void Game::finalize()
{
	delete manager_;
	manager_ = nullptr;
}

Graphics::GraphicsObject* Game::getCurrObj(){
	return current_obj;
}

void Game::setCurrObj(Graphics::GraphicsObject* obj){
	current_obj = obj;
}


bool Game::collisionRotation()
{
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int rot = co->getRotation();
	int x = co->getPositionX();
	int y = co->getPositionY();

	int new_x, new_y;
	int placeXinPM, placeYinPM;

	const Graphics::TShape shapeTiles = co->tiles_[(rot+1) % 4]; //la prochaine rotation
	for (const auto& p : shapeTiles)
	{
		new_x = x + p.first * manager_->get_tileSize();
		new_y = y + p.second * manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize(); //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / manager_->get_tileSize(); //On obtient l'indice y dans PresenceMap

		if (presenceMap_[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}

		else if (new_x < 0)
		{
			return true;
		}

		else if (new_x > manager_->get_windowWidth() - manager_->get_tileSize())
		{
			return true;
		}
	}

	return false;
}




bool Game::collisionLeft()
{
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();
	int new_x, new_y;
	int placeXinPM, placeYinPM;

	const Graphics::TShape shapeTiles = co->tiles_[ co->getRotation() ]; //current rotation ID;
	for ( const auto& p : shapeTiles ) //tous les carrés
	{
		new_x = x + (p.first-1) * manager_->get_tileSize();
		new_y = y + (p.second) * manager_->get_tileSize();

		if (new_x < 0) // si le coin gauche du carré est inférieur à 0
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / manager_->get_tileSize();
			placeYinPM = new_y / manager_->get_tileSize();
			if (presenceMap_[placeYinPM][placeXinPM] != 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::collisionRight()
{
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();
	int new_x, new_y;
	int placeXinPM, placeYinPM;

	const Graphics::TShape shapeTiles = co->tiles_[co->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x + (p.first+1) * manager_->get_tileSize();
		new_y = y + (p.second) * manager_->get_tileSize();

		if (new_x > manager_->get_windowWidth() - manager_->get_tileSize())
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / manager_->get_tileSize();
			placeYinPM = new_y / manager_->get_tileSize();
			if (presenceMap_[placeYinPM][placeXinPM] != 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::collisionDown(Graphics::GraphicsObject* obj)
{
	int new_x;
	int new_y;
	int placeXinPM; //place du carré dans le PresenceMap, coord. x
	int placeYinPM; //place du carré dans le PresenceMap, coord. y
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int x = obj->getPositionX();
	int y = obj->getPositionY();

	const Graphics::TShape shapeTiles = obj->tiles_[co->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x + p.first * manager_->get_tileSize();
		new_y = y + (p.second+1)*manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize(); //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / manager_->get_tileSize(); //On obtient l'indice y dans PresenceMap

		if (presenceMap_[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}
	}

	return false;
}


bool Game::collisionCreation(Graphics::GraphicsObject* obj)
{
	int x = obj->getPositionX();
	int y = obj->getPositionY();
	int new_x, new_y;
	int placeXinPM, placeYinPM;

	const Graphics::TShape shapeTiles = obj->tiles_[obj->getRotation()];
	for (const auto& p : shapeTiles)
	{
		new_x = x + p.first * manager_->get_tileSize();
		new_y = y + p.second * manager_->get_tileSize();

		placeXinPM = new_x / manager_->get_tileSize();
		placeYinPM = new_y / manager_->get_tileSize();

		if (presenceMap_[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}
	}

	return false;
}


void Game::keyboard( const std::uint8_t* keys )
{
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();
	if (keys[SDL_SCANCODE_UP]){
		if (!collisionRotation())
		{
			co -> rotate();
		}
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		if (!collisionLeft()) //test si possible de se deplacer vers la gauche
		{
			co -> setPositionX(x-manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		if (!collisionRight()) //test si possible de se deplacer vers la droite
		{
			co -> setPositionX(x+manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		if (!collisionDown(co)) //test si possible de se deplacer vers le bas
		{
			co -> setPositionY(y+manager_->get_tileSize());
		}
	}
	if (keys[SDL_SCANCODE_SPACE]){
		while (!collisionDown(co))
		{
			co->setPositionY(co->getPositionY()+manager_->get_tileSize());
		}
	}
	return;
}

Graphics::GraphicsObject* Game::shapeRand(){
	srand(time(NULL));
	int s = rand() % 7; //va de 0 à 6
	Graphics::GraphicsObject* obj;
	switch(s){
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
int Game::eraseLine()
{
	int nb_complete = 0;
	std::stack <int> idx_erasedL; //pour la maj de presenceMap_
	idx_erasedL.push(-1); //pour aller jusqu'en haut dans la maj de presenceMap_

	// Parcourt toutes les lignes de presenceMap_ sauf la derniere qui est le sol
	for (size_t i = 0 ; i < presenceMap_.size()-1 ; i++)
	{
		std::vector< int > line = presenceMap_[i];
		size_t j = 0;

		// Cherche jusqu'où la ligne est remplie
		while (j < line.size() && line[j] != 0)
			j++;

		if (j == line.size()) //ligne completement remplie
		{
			nb_complete++;
			idx_erasedL.push(i); // on empile l'indice de la ligne

			manager_->drawEraseLine(i);
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
				presenceMap_[ l ] = presenceMap_[ l - x ];
			}
			begin = end;
		}

		// Les lignes vides en haut de l'écran dues à la disparition de lignes en dessous:
		for (int i = 0 ; i < nb_complete ; i ++)
			presenceMap_[i] = std::vector<int>( manager_->get_nbCol(), 0 );
	}
	return nb_complete;
}

void Game::calcul_score(int nb_line)
{
	switch (nb_line)
	{
		case 0 :
			return;
		case 1 :
			score += 40 * level;
			tot_line += 1;
			break;
		case 2 :
			score += 100 * level;
			tot_line += 3;
			break;
		case 3 :
			score += 300 * level;
			tot_line += 5;
			break;
		case 4 :
			score += 1200 * level;
			tot_line += 8;
			std::cout << "TETRIS !" << std::endl;
			break;
		default :
			std::cerr << "default case in switch(nb_line) in calcul_score" << std::endl;
			exit(1);
	}
	std::cout << "New score : " << score << std::endl;
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


void Game::addToPresMap(Graphics::GraphicsObject* obj)
{
	int carre_x, carre_y;
	int placeXinPM, placeYinPM;
	int x = obj -> getPositionX();
	int y = obj -> getPositionY();
	int colID = obj->getColor();


	for (const auto& p : obj->tiles_[ obj->getRotation() ] )
	{
		carre_x = x + p.first*manager_->get_tileSize();
		carre_y = y + p.second*manager_->get_tileSize();

		placeXinPM = carre_x / manager_->get_tileSize();
		placeYinPM = carre_y / manager_->get_tileSize();

		presenceMap_[placeYinPM][placeXinPM] = colID;
	}

	return;
}


void Game::loop()
{
	bool quit = false;
	while ( !quit )
	{
		//On cree l'objet courant
		Graphics::GraphicsObject* co;
		co = shapeRand();
		if(collisionCreation(co))
		{
			std::cout << "GAME OVER. SCORE : " << score << " | LEVEL : " << level
					  << std::endl;
			exit(0);
		}
		setCurrObj(co);



		bool toucheFond = false;
		bool check_key = false; //un bouton a été appuyé si true
		int lastTime=0;
		int currentTime;
		int y;

		draw();

		SDL_Delay(500);

		while (!quit && !toucheFond)
		{

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
				keyboard( state );
				quit |= state[ SDL_SCANCODE_ESCAPE ];
				check_key = false;
			}

			currentTime = SDL_GetTicks();
			if (currentTime > lastTime + speed)
			{
				if (!collisionDown(co)) //si on peut se deplacer vers le bas
				{
					y = co -> getPositionY();
					//on se deplace vers le bas
					co -> setPositionY(y + manager_->get_tileSize());
				}
				else
				{
					toucheFond = true;
					// on l'ajoute à la matrice de presence
					addToPresMap(co);
				}
				lastTime = currentTime;
			}

			int nb_line = eraseLine();
			calcul_score(nb_line);
			levelUp();

			draw();
		}

	}
	SDL_Quit();
}


/**
 * Draws the shadow of the current piece on the floor
 */
void Game::drawShadow()
{
	// On cherche où serait la pièce au sol ; code de SPACE
	Graphics::GraphicsObject* co = getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();

	Graphics::GraphicsObject shadow = *co; //copie

	int y_new = y;
	while (!collisionDown(&shadow))
	{
		y_new += manager_->get_tileSize();
		shadow.setPositionY(y_new);
	}

	manager_->drawShadow(shadow);
}



void Game::draw()
{
	// La grille
	manager_->drawBg(0, manager_->get_nbRows());
	drawShadow();
	manager_->drawShape(getCurrObj());
	manager_->drawPresMap(presenceMap_);

	manager_->display_1p();

	manager_->update();
}
