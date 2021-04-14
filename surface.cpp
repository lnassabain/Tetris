#include "surface.h"

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// Graphics library
#include <SDL.h>

// Project
#include "sprite.h"

/******************************************************************************
 ****************************** NAMESPACE SECTION *****************************
 ******************************************************************************/

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

/******************************************************************************
 * Default constructor
 ******************************************************************************/
Surface::Surface()
:	surface_( nullptr )
,	manageSurface_( true )
{
}

/******************************************************************************
 * Constructor
 ******************************************************************************/
Surface::Surface( const std::string& bmp_file )
:	surface_( nullptr )
,	manageSurface_( true )
{
	surface_ = SDL_LoadBMP( "./sprites.bmp" );
	if (SDL_SetColorKey( surface_, SDL_FALSE, 255 ) != 0)
		SDL_GetError();
	//SDL_SetColorKey( surface_, true, SDL_MapRGB(surface_->format, 255, 255, 255) );
}

/******************************************************************************
 * Constructor
 ******************************************************************************/
Surface::Surface( SDL_Surface* surface )
:	surface_( surface )
,	manageSurface_( false )
{
}

/******************************************************************************
 * Destructor
 ******************************************************************************/
Surface::~Surface()
{
	if ( manageSurface_ )
	{
		SDL_FreeSurface( surface_ );
	}
}

/******************************************************************************
 * Initialize
 ******************************************************************************/
void Surface::initialize()
{
}

/******************************************************************************
 * Finalize
 ******************************************************************************/
void Surface::finalize()
{
	// TODO
	// ...
}

/******************************************************************************
 * Load()
 ******************************************************************************/
void Surface::load( const std::string& bmp_file )
{
	surface_ = SDL_LoadBMP( bmp_file.c_str() );
	SDL_SetColorKey( surface_, true, 0 ); // 0: 00/00/00 noir -> transparent
}

/******************************************************************************
 * draw()
 ******************************************************************************/
void Surface::draw( const Sprite& sprite, int x, int y )
{
	SDL_Rect dst{ x, y, 0, 0 };
	SDL_BlitSurface( sprite.surface_->surface_, sprite.geometry_,
				surface_, &dst );
}

int a = 0xFFA5;
