#ifndef STAR_HPP
#define STAR_HPP
#include "constants.hpp"

class Star {
public:
    double x[dim]{0};
    double v[dim]{0};
    double m;
    double f[dim]{0};
    int size = sunSize;
    QColor col;

    Star(const double *coord, const double *velocity, double mass);

    Star& operator+=(const Star& rhs);
private:
    void updateColor();
    void updateSize();
};

#endif //STAR_HPP