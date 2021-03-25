#include "coordonate.hpp"

const double Coordonate::get_x() const {
    return x;
}
const double Coordonate::get_y() const {
    return y;
}

Coordonate::Coordonate(double x, double y) : x(x), y(y) {}

Coordonate Coordonate::addition(Coordonate const & b) const {
    return Coordonate (this->x + b.x, this->y + b.y);
}


Coordonate operator+ (Coordonate const& a, Coordonate const& b) {
    return (a.addition(b));
}
