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

/*Carre gris, sprites_[0]
Carre rouge, sprites_[1]
Carre jaune, sprites_[2]
Carre vert, sprites_[3]
Carre bleu, sprites_[4]
Carre violet, sprites_[5]
Carre orange, sprites_[6]*/



Game::Game()
:	window_( nullptr )
,	planche_( nullptr )
,	sprites_()
,	presenceMap_()
,	grid_nbRows_( 0 )
,	grid_nbColumns_( 0 )
,	grid_tileSize_( 0 )
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

    const int windowWidth = grid_nbColumns_ * grid_tileSize_ ;
	const int windowHeight = grid_nbRows_ * grid_tileSize_;
	const std::string windowTitle = "TETRIS";
	window_ = new Window( windowTitle, windowWidth, windowHeight );
	window_->initialize();


    planche_ = new Surface();
	const std::string image = "./tetris_sprites.bmp";
	planche_->load( image.c_str() );

	for (int i = 0 ; i < 7 ; i++)
	{
		sprites_.emplace_back( new Sprite( planche_, i*(grid_tileSize_+1), 0, grid_tileSize_, grid_tileSize_ ) );
	}

}

void Game::finalize()
{

}


void Game::keyboard( const std::uint8_t* keys )
{
//	if (keys[SDL_SCANCODE_SPACE])
//	if (keys[SDL_SCANCODE_UP])
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


void Game::draw( double dt )
{
	// background
	Sprite* sfond = sprites_[ S_GRIS ];
    for ( int j = 0, h = window_->height(); j <= h; j += sfond->height() )
    {
        for ( int i = 0, w = window_->width(); i <= w; i += sfond->width() )
        {
            window_->draw( *sfond, i, j );
        }
    }

	{
        static Graphics::ShapeO* shape_test;
        static bool is_shape_initialized = false;
        if ( ! is_shape_initialized )
        {
            shape_test = Graphics::ShapeO::create();

            is_shape_initialized = true;
        }
        int rotationID = 0; //Première rotation, change quand le joueur appuie sur la fleche vers le haut
        //On pourrait mettre rotationID = rot % 4;
        //rot commence à 0 et à chaque fois que le joueur appuie sur la flèche vers le haut,
        //on incremente rot :)
        const Graphics::TShape shapeTiles = shape_test->tiles_[ rotationID ]/*current rotation ID*/;
        for ( const auto& p : shapeTiles )
        {
            const int x = shape_test->getPositionX();
            const int y = shape_test->getPositionY();


            //const int colorID = shape_test->getColorID();
            //Fct à rajouter dans GraphicsObject
            const int colorID = 1;
            Sprite* carre_rouge = sprites_[ colorID ];

            /*int rotation_;
            int nextRotation() { rotation_ = rotation_ % 4 }*/

            window_->draw( *carre_rouge, x + p.first * grid_tileSize_, y + p.second * grid_tileSize_ );
        }
    }

}
