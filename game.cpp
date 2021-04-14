#include <SDL.h>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>
#include <math.h>
#include "game.hpp"
#include "GraphicsObject.h"

#define S_GRIS 0
#define S_ROUGE 1
#define S_JAUNE 2
#define S_VERT 3
#define S_BLEU 4
#define S_VIOLET 5
#define S_ORANGE 6
#define S_CYAN 7
#define S_SHADOW 8

#define X_OFFSET 0
#define Y_OFFSET 0


Game::Game()
:	window_( nullptr )
,	planche_( nullptr )
,	sprites_()
,	presenceMap_()
,	grid_nbRows_( 0 )
,	grid_nbColumns_( 0 )
,	grid_tileSize_( 0 )
,	current_obj( nullptr )
,	score( 0 )
,	level( 1 )
,	tot_line( 0 )
, 	speed( 1000 )
{
}

Game::~Game()
{
	for ( auto sprite : sprites_ )
	{
		delete sprite;
		sprite = nullptr;
	}
	sprites_.clear();

	delete planche_;
	planche_ = nullptr;

	delete window_;
	window_ = nullptr;
}

void Game::initialize()
{
    grid_nbRows_ = 20;
	grid_nbColumns_ = 10;
	grid_tileSize_ = 32;
    /*Pour modeliser la grille, on cree une matrice booleenne. Lorsque l'objet
    arrete de bouger (touche le fond), on met la matrice à cette zone à true.
    De la même maniere, lorsqu'on deplace un objet, s'il touche une zone qui
    est a true, il y a collision*/
    presenceMap_.resize( grid_nbRows_, std::vector< int >( grid_nbColumns_, 0 ) );
	presenceMap_.push_back( std::vector< int >( grid_nbColumns_, 1 ) ); //le sol
	// for (int i = 0 ; i < presenceMap_.size() ; i++)
	// 	for (int j = 0 ; j < grid_nbColumns_ ; j++)
	// 		std::cout<< i <<" " << j <<" " << (bool)presenceMap_[i][j] << std::endl;

    const int windowWidth = grid_nbColumns_ * grid_tileSize_ ;
	const int windowHeight = grid_nbRows_ * grid_tileSize_;
	const std::string windowTitle = "TETRIS";
	window_ = new Window( windowTitle, windowWidth, windowHeight );
	window_->initialize();


    planche_ = new Surface();
	const std::string image = "./tetris_sprites.bmp";
	planche_->load( image.c_str() );

	for (int i = 0 ; i < 9 ; i++)
	{
		sprites_.emplace_back( new Sprite( planche_, i*(grid_tileSize_), 0, grid_tileSize_, grid_tileSize_ ) );
	}
}

void Game::finalize()
{

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
		new_x = x + p.first * grid_tileSize_;
		new_y = y + p.second * grid_tileSize_;

		placeXinPM = new_x / grid_tileSize_; //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / grid_tileSize_; //On obtient l'indice y dans PresenceMap

		if (presenceMap_[placeYinPM][placeXinPM] != 0)
		{
			return true;
		}

		else if (new_x < 0)
		{
			return true;
		}

		else if (new_x > window_->width()-grid_tileSize_)
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
		new_x = x + (p.first-1) * grid_tileSize_;
		new_y = y + (p.second) * grid_tileSize_;

		if (new_x < 0) // si le coin gauche du carré est inférieur à 0
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / grid_tileSize_;
			placeYinPM = new_y / grid_tileSize_;
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
		new_x = x + (p.first+1) * grid_tileSize_;
		new_y = y + (p.second) * grid_tileSize_;

		if (new_x > window_->width()-grid_tileSize_)
		{
			return true;
		}
		else
		{
			placeXinPM = new_x / grid_tileSize_;
			placeYinPM = new_y / grid_tileSize_;
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
		new_x = x + p.first * grid_tileSize_;
		new_y = y + (p.second+1)*grid_tileSize_;

		placeXinPM = new_x / grid_tileSize_; //On obtient l'indice x dans PresenceMap
		placeYinPM = new_y / grid_tileSize_; //On obtient l'indice y dans PresenceMap

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
		new_x = x + p.first * grid_tileSize_;
		new_y = y + p.second * grid_tileSize_;

		placeXinPM = new_x / grid_tileSize_;
		placeYinPM = new_y / grid_tileSize_;

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
			co -> setPositionX(x-grid_tileSize_);
		}
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		if (!collisionRight()) //test si possible de se deplacer vers la droite
		{
			co -> setPositionX(x+grid_tileSize_);
		}
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		if (!collisionDown(co)) //test si possible de se deplacer vers le bas
		{
			co -> setPositionY(y+grid_tileSize_);
		}
	}
	if (keys[SDL_SCANCODE_SPACE]){
		while (!collisionDown(co))
		{
			co->setPositionY(co->getPositionY()+grid_tileSize_);
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

			/* on prend la surface de tout ce qu'il y a au dessus de cette ligne
			et on la copie une ligne plus bas
			+ on reaffiche le fond en haut */
			Sprite above ( window_->getSurface(), X_OFFSET, Y_OFFSET,
						   grid_nbColumns_ * grid_tileSize_,
						   grid_tileSize_ * i );
			// On décale cette sprite d'une ligne vers le bas : y = grid_tileSize_
			window_->draw( above, Y_OFFSET, grid_tileSize_ );
			drawBg( Y_OFFSET, 1 ); //une ligne de bg en haut de l'écran
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
			presenceMap_[i] = std::vector<int>( grid_nbColumns_, 0 );
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
		carre_x = x + p.first*grid_tileSize_;
		carre_y = y + p.second*grid_tileSize_;

		placeXinPM = carre_x / grid_tileSize_;
		placeYinPM = carre_y / grid_tileSize_;

		presenceMap_[placeYinPM][placeXinPM] = colID;
	}

	return;
}

void Game::drawPresMap()
{
	int i, j;
	int colID;

	for (i=0; i<grid_nbRows_; i++)
	{
		for (j=0; j<grid_nbColumns_; j++)
		{
			colID = presenceMap_[i][j];

			if (colID != 0)
			{
				window_->draw( *sprites_[colID], X_OFFSET+j*grid_tileSize_,
								Y_OFFSET+i*grid_tileSize_);
			}
		}
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

		window_->update();
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
					co -> setPositionY(y + grid_tileSize_);
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
			// Update window (refresh)
			window_->update();
		}

	}
	SDL_Quit();
}

void Game::drawShape(Graphics::GraphicsObject* obj)
{
	const int colorID = obj->getColor();
	Sprite* obj_sprite = sprites_[ colorID ];

	for ( const auto& p : obj->tiles_[ obj->getRotation() ] ) //tous les carrés
	{
		const int x = obj->getPositionX();
		const int y = obj->getPositionY();

		window_->draw( *obj_sprite, X_OFFSET + x + p.first * grid_tileSize_,
			 			Y_OFFSET + y + p.second * grid_tileSize_ );
	}
}

/**
 * Draw a certain number of lines of background at a certain position.
 * @param y       y coordinate of the upper left angle -> position of the line (in the grid ref)
 * @param nbLines number of lines of background we want to draw
 */
void Game::drawBg(int y, int nbLines)
{
	Sprite* sfond = sprites_[ S_GRIS ];
	int height = nbLines * grid_tileSize_;

	for ( int j = y+Y_OFFSET; j < height; j += sfond->height() ) // y
		for ( int i = X_OFFSET ; i <= window_->width(); i += sfond->width() )// x
			window_->draw( *sfond, i, j );
}

/**
 * Draws the shadow of the current piece on the floor
 */
void Game::drawShadow()
{
	// On cherche où serait la pièce au sol ; code de SPACE
	Graphics::GraphicsObject* co =getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();

	Graphics::GraphicsObject shadow = *co; //copie ??

	int y_new = y;
	while (!collisionDown(&shadow))
	{
		y_new += grid_tileSize_;
		shadow.setPositionY(y_new);
	}

	// On dessine l'ombre en noir
	Sprite* obj_sprite = sprites_[ S_SHADOW ];
	for ( const auto& p : shadow.tiles_[ shadow.getRotation() ] ) //tous les carrés
		window_->draw( *obj_sprite, X_OFFSET + x + p.first * grid_tileSize_,
						Y_OFFSET + y_new + p.second * grid_tileSize_ );
}

void Game::draw()
{
	drawBg(0, grid_nbRows_);

	drawShadow();
	drawShape(getCurrObj());

	drawPresMap();

}
