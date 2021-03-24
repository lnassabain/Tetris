#ifndef _SPRITE_H_
#define _SPRITE_H_

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ******************************** CLASS USED **********************************
 ******************************************************************************/

// Graphics library
struct SDL_Rect;

// Project
class Surface;

/******************************************************************************
 ****************************** CLASS DEFINITION ******************************
 ******************************************************************************/

/**
  * @class Sprite
  *
  * @brief The Sprite class provides interface to the underlying graphics library's sprite management.
  */
class Sprite
{

	/**************************************************************************
	 ***************************** FRIEND SECTION *****************************
	 **************************************************************************/

	friend class Surface;

	/**************************************************************************
	 ***************************** PUBLIC SECTION *****************************
	 **************************************************************************/

public:

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

	Sprite( const Surface* const s, int x, int y, int w, int h );
	virtual ~Sprite();

	int width() const;
	int height() const;

	/**************************************************************************
	 **************************** PROTECTED SECTION ***************************
	 **************************************************************************/

protected:

	/******************************* ATTRIBUTES *******************************/

	/**
	 * Graphics library
	 */
	SDL_Rect* geometry_;

	/**
	 * Associated surface (texture)
	 */
	const Surface* const surface_;

	/******************************** METHODS *********************************/

	/**************************************************************************
	 ***************************** PRIVATE SECTION ****************************
	 **************************************************************************/

private:

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

};

/**************************************************************************
 ***************************** INLINE SECTION *****************************
 **************************************************************************/

//#include "sprite.inl"

#endif
