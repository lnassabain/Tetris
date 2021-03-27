#ifndef _GRAPHICS_OBJECT_H_
#define _GRAPHICS_OBJECT_H_

#include <vector>
#include <utility>


enum Color : char {c_gris, c_rouge, c_jaune, c_vert, c_bleu, c_violet, c_orange, c_cyan};

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
	const int getPositionX() const;
	const int getPositionY() const;

	const int getRotation() const;

	TRotatedShapes tiles_;

	const Color getColor() const;

	void move(int newX, int newY);
	void rotate();

protected:

	// Constructor
	GraphicsObject();
	Color c;
	void setPositionX( int pValue );
	void setPositionY( int pValue );


private:

    // Position
	int x;
	int y;
	int rotation;


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

class ShapeJ : public GraphicsObject
{
public:
	static ShapeJ* create();
	virtual ~ShapeJ();
protected:
	ShapeJ();
private:
};


class ShapeL : public GraphicsObject
{
public:
	static ShapeL* create();
	virtual ~ShapeL();
protected:
	ShapeL();
private:
};


class ShapeS : public GraphicsObject
{
public:
	static ShapeS* create();
	virtual ~ShapeS();
protected:
	ShapeS();
private:
};


class ShapeZ : public GraphicsObject
{
public:
	static ShapeZ* create();
	virtual ~ShapeZ();
protected:
	ShapeZ();
private:
};



}

#endif
