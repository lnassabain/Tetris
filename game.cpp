#include <SDL.h>
#include <string>
#include <iostream>
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


Game::Game()
:	window_( nullptr )
,	planche_( nullptr )
,	sprites_()
,	presenceMap_()
,	grid_nbRows_( 0 )
,	grid_nbColumns_( 0 )
,	grid_tileSize_( 0 )
,	current_obj( nullptr )
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
    presenceMap_.resize( grid_nbRows_, std::vector< bool >( grid_nbColumns_, false ) );
	presenceMap_.push_back( std::vector< bool >( grid_nbColumns_, true ) ); //le sol

    const int windowWidth = grid_nbColumns_ * grid_tileSize_ ;
	const int windowHeight = grid_nbRows_ * grid_tileSize_;
	const std::string windowTitle = "TETRIS";
	window_ = new Window( windowTitle, windowWidth, windowHeight );
	window_->initialize();


    planche_ = new Surface();
	const std::string image = "./tetris_sprites.bmp";
	planche_->load( image.c_str() );

	for (int i = 0 ; i < 8 ; i++)
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

void Game::keyboard( const std::uint8_t* keys )
{
	Graphics::GraphicsObject* co;
	co = getCurrObj();
	int x = co->getPositionX();
	int y = co->getPositionY();
	if (keys[SDL_SCANCODE_UP]){
		co -> rotate();
	}
	if (keys[SDL_SCANCODE_LEFT]){
		co -> setPositionX(x-grid_tileSize_);
	}
	if (keys[SDL_SCANCODE_RIGHT]){
		co -> setPositionX(x+grid_tileSize_);
	}
	if (keys[SDL_SCANCODE_DOWN]){
		co -> setPositionY(y+grid_tileSize_);
	}
	if (keys[SDL_SCANCODE_SPACE]){
		//l'objet tombe et touche le fond
	}
	return;
}

Graphics::GraphicsObject* Game::shapeRand(){
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
 * Check if there are lines to remove and do it.
 * @return number of erased lines
 */
int Game::eraseLine() //pour le moment detecte seulement
{
	int nb_complete = 0;
	// parcourt toutes les lignes de presenceMap_ sauf la derniere qui est le sol
	for (size_t i = 0 ; i < presenceMap_.size()-1 ; i++)
	{
		std::vector< bool > line = presenceMap_[i];
		size_t j = 0;

		while (j < line.size() && line[j])
			j++;

		if (j == line.size()) //ligne complete de true
		{
			nb_complete++;
			/* on prend la surface de tout ce qu'il y a au dessus de cette ligne
			et on la copie une ligne plus bas
			+ on reaffiche le fond en haut
			*/
			int line_idx = i;
			Sprite above ( window_->getSurface(), 0, 0,
						grid_nbColumns_ * grid_tileSize_,
						grid_tileSize_ * line_idx );
			window_->draw( above, 0, grid_tileSize_ ); //une ligne plus bas
			drawBg( 0, 1 ); //une ligne de bg en haut
		}
	}
	return nb_complete;
}



void Game::loop()
{
	Uint64 now = SDL_GetPerformanceCounter(); // timers
	Uint64 prev = now;

	bool quit = false;
	while ( !quit )
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
			}
		}
		//On cree l'objet courant
		Graphics::GraphicsObject* co;
		co = shapeRand();
		setCurrObj(co);

		// Keyboard management
		const Uint8* state = SDL_GetKeyboardState(NULL);
		keyboard( state );
		quit |= state[ SDL_SCANCODE_ESCAPE ];

		// TETRIS algo
		// - erase lines
		// - insert lines

		// Rendering stage
		prev = now;
		now = SDL_GetPerformanceCounter();
		double delta_t = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());
		draw( delta_t );

		// Update window (refresh)
		window_->update();
	}
	//SDL_Quit();
}

void Game::drawShape(Graphics::GraphicsObject* obj)
{
	for ( const auto& p : obj->tiles_[ obj->getRotation() ] ) //tous les carrés
	{
		const int x = obj->getPositionX();
		const int y = obj->getPositionY();
		const int colorID = obj->getColor();
		Sprite* obj_sprite = sprites_[ colorID ];

		window_->draw( *obj_sprite, x + p.first * grid_tileSize_, y + p.second * grid_tileSize_ );
	}
}

/**
 * Draw a certain number of lines of background at a certain position.
 * @param y       y coordinate of the upper left angle -> position of the line
 * @param nbLines number of lines of background we want to draw
 */
void Game::drawBg(int y, int nbLines)
{
	Sprite* sfond = sprites_[ S_GRIS ];
	int height = nbLines * grid_tileSize_;

	for ( int j = y, h = height; j <= h; j += sfond->height() ) // y
	{
		for ( int i = 0, w = window_->width(); i <= w; i += sfond->width() )// x
		{
			window_->draw( *sfond, i, j );
		}
	}
}

void Game::draw( double dt )
{
	drawBg(0, grid_nbRows_);

	//Affichage piece courante
	drawShape(current_obj);
	SDL_Delay(500);

/* Affichage des 4 rotations d'une pièce
	{
        static Graphics::ShapeL* shape_test;
        static bool is_shape_initialized = false;
        if ( ! is_shape_initialized )
        {
            shape_test = Graphics::ShapeL::create();

            is_shape_initialized = true;
        }

		for (size_t i = 0 ; i < 4 ; i++)
		{
			//int rotationID = i; //Première rotation, change quand le joueur appuie sur la fleche vers le haut
			//On pourrait mettre rotationID = rot % 4;
			//rot commence à 0 et à chaque fois que le joueur appuie sur la flèche vers le haut,
			//on incremente rot :)

			const Graphics::TShape shapeTiles = shape_test->tiles_[ shape_test->getRotation() ]; //current rotation ID;
			for ( const auto& p : shapeTiles ) //tous les carrés
			{
				const int x = shape_test->getPositionX();
				const int y = shape_test->getPositionY();


				const int colorID = shape_test->getColor();
				Sprite* carre_rouge = sprites_[ colorID ];


				window_->draw( *carre_rouge, x + p.first * grid_tileSize_, y + (p.second +i*4)%20 * grid_tileSize_ );
			}

			shape_test->rotate();
			// shape_test->move(grid_tileSize_*4, grid_tileSize_*4);
			// std::cout << shape_test->getPositionX() << std::endl;
		}
    }*/
}
