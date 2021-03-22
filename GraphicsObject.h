#ifndef _GRAPHICS_OBJECT_H_
#define _GRAPHICS_OBJECT_H_

#include <vector>
#include <utility>

namespace Graphics
{

class GraphicsObject
{

public:

	// Desctructor
	virtual ~GraphicsObject();

	// Position
	int getPositionX() const;
	int getPositionY() const;
	void setPositionX( int pValue );
	void setPositionY( int pValue );

	using TCoordinate = std::pair< int, int >;
	using TShape = std::vector< TCoordinate >;
	using TRotatedShapes = std::vector< TShape >;
	TRotatedShapes tiles_;

protected:

	// Constructor
	GraphicsObject();

private:

    // Position
	int x;
	int y;

};

}

#endif
