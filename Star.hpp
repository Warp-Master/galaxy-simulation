#ifndef GALAXY_SIMULATION_STAR_HPP
#define GALAXY_SIMULATION_STAR_HPP
#include <vector>
#include "constants.hpp"

class Star {
public:
    std::vector<double> x{dim, 0};
    std::vector<double> v{dim, 0};
    std::vector<double> f{dim, 0};
    double m;

    int size;
    int col;

    Star(const double *coord, const double *velocity, double mass);

    bool isValid() const;

    Star& operator+=(const Star& rhs);
private:
    void updateColor();
    void updateSize();
};

#endif //GALAXY_SIMULATION_STAR_HPP