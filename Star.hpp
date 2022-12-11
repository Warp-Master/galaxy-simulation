#ifndef GALAXY_SIMULATION_STAR_HPP
#define GALAXY_SIMULATION_STAR_HPP
#include "constants.hpp"

class Star {
public:
    double x[dim]{0};
    double v[dim]{0};
    double m;
    double f[dim]{0};
    int size = sunSize;
    int col;

    Star(const double *coord, const double *velocity, double mass);

    Star& operator+=(const Star& rhs);
private:
    void updateColor();
    void updateSize();
};

#endif //GALAXY_SIMULATION_STAR_HPP