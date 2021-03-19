

using TCoordinate = std::pair <int, int>; //Les coordonnées de chaque carré, x et y/
using TShape = std::vector<TCoordinate>; //Chaque forme est représentée par un vecteur de carrés


class GraphicsObject
{
protected:
    Tshape shape;

public:
    virtual void move();
    virtual void rotate();

    using TCoordinate = std::pair <int, int>; /*Les coordonnées de chaque carré, x et y*/
    using TShape = std::vector<TCoordinate>; /*Chaque forme est représentée par un vecteur de carrés*/
    using TRotatedShapes = std::vector<TShape>; /*Un vecteur pour représenter toutes les rotations d’une forme*/
//Ensuite on pourrait déclarer un objet de la forme:
//TRotatedShapes tiles_;

}

class ShapeI : public GraphicsObject
{
public:
    ShapeI()
    {
        shape.push_back()
    }
}

class ShapeJ : public GraphicsObject
{

}

class ShapeL : public GraphicsObject
{

}

class ShapeO : public GraphicsObject
{

}

class ShapeS : public GraphicsObject
{

}

class ShapeT : public GraphicsObject
{

}

class ShapeZ : public GraphicsObject
{

}
