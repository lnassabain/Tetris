
class Coordonate
{
private:
    double x;
    double y;

public:
    const double get_x() const;
    const double get_y() const;
    void set_x();
    void set_y();

    Coordonate(double x, double y);
    ~Coordonate();

    Coordonate addition(Coordonate const & b) const;
};

Coordonate operator+ (Coordonate const& a, Coordonate const& b);
