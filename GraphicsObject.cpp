// Include class definition
#include "GraphicsObject.h"

using namespace Graphics;

// Constructor
GraphicsObject::GraphicsObject():	x( 0 ),	y( 0 ), c( c_gris )
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

const Color GraphicsObject::getColor() const {
	return c;
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

	c = c_bleu;
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

	c = c_jaune;
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
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
                    std::make_pair( 1, 0 ),
                    std::make_pair( 2, 0 ),
                    std::make_pair( 1, 1 ) };

	tiles_[ 1 ] = { std::make_pair( 1, 0 ),
                    std::make_pair( 1, 1 ),
                    std::make_pair( 0, 1 ),
                    std::make_pair( 1, 2 ) };

	tiles_[ 2 ] = { std::make_pair( 0, 1 ),
                    std::make_pair( 1, 1 ),
                    std::make_pair( 1, 0 ),
                    std::make_pair( 2, 1 ) };

	tiles_[ 3 ] = { std::make_pair( 0, 0 ),
                    std::make_pair( 0, 1 ),
                    std::make_pair( 1, 1 ),
                    std::make_pair( 0, 2 ) };

	c = c_violet;
}
ShapeT::~ShapeT()
{
}


//////////////////////////////////////////

///////////////SHAPE J////////////////////
ShapeJ* ShapeJ::create()
{
	return new ShapeJ();
}

ShapeJ::ShapeJ()
:	GraphicsObject()
{
	tiles_.resize( 4/*nb rotations*/ );
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 2, 0 ),
		            std::make_pair( 2, 1 ) };
	tiles_[ 1 ] = { std::make_pair( 0, 2 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 1, 2 ) };
	tiles_[ 2 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 2, 1 ) };
	tiles_[ 3 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 0, 2 ),
		            std::make_pair( 1, 0 ) };

	c = c_bleu;
}
ShapeJ::~ShapeJ()
{
}

//////////////////////////////////////////

///////////////SHAPE L////////////////////
ShapeL* ShapeL::create()
{
	return new ShapeL();
}

ShapeL::ShapeL()
:	GraphicsObject()
{
	tiles_.resize( 4/*nb rotations*/ );
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 2, 0 ) };
	tiles_[ 1 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 1, 2 ) };
	tiles_[ 2 ] = { std::make_pair( 0, 1 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 2, 1 ),
		            std::make_pair( 2, 0 ) };
	tiles_[ 3 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 0, 2 ),
		            std::make_pair( 1, 2 ) };

	c = c_orange;
}
ShapeL::~ShapeL()
{
}

//////////////////////////////////////////

///////////////SHAPE S////////////////////
ShapeS* ShapeS::create()
{
	return new ShapeS();
}

ShapeS::ShapeS()
:	GraphicsObject()
{
	tiles_.resize( 4/*nb rotations*/ );
	tiles_[ 0 ] = { std::make_pair( 0, 1 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 2, 0 ) };
	tiles_[ 1 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 0, 1 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 1, 2 ) };
	tiles_[ 2 ] = tiles_[ 0 ];
	tiles_[ 3 ] = tiles_[ 1 ];

	c = c_vert;
}
ShapeS::~ShapeS()
{
}

//////////////////////////////////////////

///////////////SHAPE Z////////////////////
ShapeZ* ShapeZ::create()
{
	return new ShapeZ();
}

ShapeZ::ShapeZ()
:	GraphicsObject()
{
	tiles_.resize( 4/*nb rotations*/ );
	tiles_[ 0 ] = { std::make_pair( 0, 0 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 1, 1 ),
		            std::make_pair( 2, 1 ) };
	tiles_[ 1 ] = { std::make_pair( 0, 1 ),
		            std::make_pair( 0, 2 ),
		            std::make_pair( 1, 0 ),
		            std::make_pair( 1, 1 ) };
	tiles_[ 2 ] = tiles_[ 0 ];
	tiles_[ 3 ] = tiles_[ 1 ];

	c = c_rouge;
}
ShapeZ::~ShapeZ()
{
}

//////////////////////////////////////////
