// Include class definition
#include "GraphicsObject.h"

using namespace Graphics;

// Constructor
GraphicsObject::GraphicsObject():	x( 0 ),	y( 0 )
{
}

// Destructor
GraphicsObject::~GraphicsObject()
{
}

// Position
int GraphicsObject::getPositionX() const
{
	return x;
}

int GraphicsObject::getPositionY() const
{
	return y;
}

void GraphicsObject::setPositionX( int pValue )
{
	x = pValue;
}

void GraphicsObject::setPositionY( int pValue )
{
	y = pValue;
}

///////////////SHAPE I////////////////////


ShapeI* ShapeI::create()
{
	return new ShapeI();
}

ShapeI::ShapeI()
:	GraphicsObject()
{
	tiles_.resize( 4/*nb rotations*/ );
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 2, 0 ),
		            std::make_pair( 3, 0 ) };
	tiles_[ 1 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 0, 2 ),
		            std::make_pair( 0, 3 ) };
	tiles_[ 2 ] = tiles_[ 0 ];
	tiles_[ 3 ] = tiles_[ 1 ];
}
ShapeI::~ShapeI()
{
}
//////////////////////////////////////////

///////////////SHAPE O////////////////////
ShapeO* ShapeO::create()
{
	return new ShapeO();
}
ShapeO::ShapeO()
:	GraphicsObject()
{
	tiles_.resize(4);
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
					std::make_pair( 0, 1 ),
					std::make_pair( 1, 0 ),
					std::make_pair( 1, 1 ) };
	tiles_[ 1 ] = tiles_[ 0 ];
	tiles_[ 2 ] = tiles_[ 0 ];
	tiles_[ 3 ] = tiles_[ 0 ];
}
ShapeO::~ShapeO()
{
}
//////////////////////////////////////////

///////////////SHAPE T////////////////////
ShapeT* ShapeT::create()
{
	return new ShapeT();
}
ShapeT::ShapeT()
:	GraphicsObject()
{
	tiles_.resize( 4 );
	tiles_[ 0 ] = { std::make_pair( -1, 0 ),
                    std::make_pair( 0, 0 ),
                    std::make_pair( 1, 0 ),
                    std::make_pair( 0, 1 ) };

	tiles_[ 1 ] = { std::make_pair( -1, 1 ),
                    std::make_pair( 0, 0 ),
                    std::make_pair( 0, 1 ),
                    std::make_pair( 0, 2 ) };

	tiles_[ 2 ] = { std::make_pair( 0, 0 ),
                    std::make_pair( -1, 1 ),
                    std::make_pair( 0, 1 ),
                    std::make_pair( 1, 1 ) };

	tiles_[ 3 ] = { std::make_pair( -1, 0 ),
                    std::make_pair( -1, 1 ),
                    std::make_pair( -1, 2 ),
                    std::make_pair( 0, 1 ) };
}
ShapeT::~ShapeT()
{
}

/*
//////////////////////////////////////////

///////////////SHAPE J////////////////////
...
...
//////////////////////////////////////////

///////////////SHAPE L////////////////////
...
...
//////////////////////////////////////////

///////////////SHAPE S////////////////////
...
...
//////////////////////////////////////////

///////////////SHAPE Z////////////////////
...
...
//////////////////////////////////////////
*/
