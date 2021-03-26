#ifndef _GRAPHICS_OBJECT_H_
#define _GRAPHICS_OBJECT_H_

#include <vector>
#include <utility>

namespace Graphics
{
	using TCoordinate = std::pair< int, int >;
	using TShape = std::vector< TCoordinate >;
	using TRotatedShapes = std::vector< TShape >;


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

	TRotatedShapes tiles_;

protected:

	// Constructor
	GraphicsObject();

private:

    // Position
	int x;
	int y;

};

class ShapeI : public GraphicsObject
{
public:
	static ShapeI* create();
	virtual ~ShapeI();
protected:
	ShapeI();
private:
};

class ShapeO : public GraphicsObject
{
public:
	static ShapeO* create();
	virtual ~ShapeO();
protected:
	ShapeO();
private:
};

class ShapeT : public GraphicsObject
{
public:
	static ShapeT* create();
	virtual ~ShapeT();
protected:
	ShapeT();
private:
};


}

#endif
