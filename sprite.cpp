#include "sprite.h"

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// Graphics library
#include <SDL.h>

// Project
#include "surface.h"

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
 * Constructor
 ******************************************************************************/
Sprite::Sprite( const Surface* const s, int x, int y, int w, int h )
:	surface_( s )
,	geometry_( nullptr )
{
	geometry_ = new SDL_Rect();
	geometry_->x = x;
	geometry_->y = y;
	geometry_->w = w;
	geometry_->h = h;
}

/******************************************************************************
 * Destructor
 ******************************************************************************/
Sprite::~Sprite()
{
	delete geometry_;
	geometry_ = nullptr;
}

 /******************************************************************************
  * ...
  ******************************************************************************/
int Sprite::width() const
{
	return geometry_->w;
}

/******************************************************************************
 * ...
 ******************************************************************************/
int Sprite::height() const
{
	return geometry_->h;
}
