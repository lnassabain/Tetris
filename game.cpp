#include <SDL.h>
#include <string>
#include "game.hpp"


Game::Game()
:	window_( nullptr )
,	planche_( nullptr )
,	sprites_()
//,	balls_()
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
	grid_tileSize_ = 24;
    /*Pour modeliser la grille, on cree une matrice booleenne. Lorsque l'objet
    arrete de bouger (touche le fond), on met la matrice à cette zone à true.
    De la même maniere, lorsqu'on deplace un objet, s'il touche une zone qui
    est a true, il y a collision*/
    presenceMap_.resize( grid_nbRows_, std::vector< bool >( grid_nbColumns_, false ) );

    /*Pourqoi le prof fait * 2 pour windowWidth ?*/
    const int windowWidth = grid_nbColumns_ * grid_tileSize_ * 2;
	const int windowHeight = grid_nbRows_ * grid_tileSize_;
	const std::string windowTitle = "TETRIS";
	window_ = new Window( windowTitle, windowWidth, windowHeight );
	window_->initialize();


    planche_ = new Surface();
	const std::string image = "./tetrissprite.bmp";
	planche_->load( image.c_str() );

    /*Carre rouge, sprites_[0]*/
    sprites_.emplace_back( new Sprite( planche_, 0, 0, 52, 52 ) );
    /*Carre jaune, sprites_[1]*/
    sprites_.emplace_back( new Sprite( planche_, 53, 0, 52, 52 ) );
    /*Carre vert, sprites_[2]*/
    sprites_.emplace_back( new Sprite( planche_, 106, 0, 52, 52 ) );
    /*Carre bleu, sprites_[3]*/
    sprites_.emplace_back( new Sprite( planche_, 159, 0, 52, 52 ) );
    /*Carre violet, sprites_[4]*/
    sprites_.emplace_back( new Sprite( planche_, 212, 0, 52, 52 ) );
    /*Carre orange, sprites_[5]*/
    sprites_.emplace_back( new Sprite( planche_, 265, 0, 52, 52 ) );

	//image de fond
	Surface* gris_surf = new Surface();
	const std::string gris_im = "./gris.bmp";
	gris_surf->load( gris_im.c_str() );
	sprites_.emplace_back( new Sprite( gris_surf, 0, 0, 52, 52 ) );

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

	// creation de la surface à afficher

	//affichage
	window_->draw(*sprites_[6], 0,0);

	Sprite* sfond = sprites_[ 0 ];
	    for ( int j = 0, h = window_->height(); j <= h; j += sfond->height() )
	    {
	        for ( int i = 0, w = window_->width(); i <= w; i += sfond->width() )
	        {
	            window_->draw( *sfond, i, j );
	        }
	    }



}
