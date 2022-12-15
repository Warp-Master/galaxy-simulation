#include <cmath>
#include <algorithm>

#include "Star.hpp"
#include "constants.hpp"


const double borderMass[] = {borderMassC * massVenus, borderMassC * massEarth, borderMassC * massUran,
                             borderMassC * massJup, borderMassC * massSun};
const int starColors[] = {0x264653,
                          0x2a9d8f,
                          0xe9c46a,
                          0xf4a261,
                          0xe76f51,
                          0xe63946};
const int nBorders = sizeof(borderMass) / sizeof(borderMass[0]);

Star::Star(const double *coord, const double *velocity, double mass): size(0), col(0xffffff) {
    for (int k = 0; k < dim; ++k) {
        x[k] = coord[k];
        v[k] = velocity[k];
    }
    m = mass;
    updateColor();
    updateSize();
}


bool Star::isValid() const {
    return std::any_of(x.begin(),
                       x.end(),
                       [](double k){ return std::abs(k) < systemRadius; });
}

Star& Star::operator+=(const Star &rhs) {
    for (int i = 0; i < dim;++i) {
        v[i] = (v[i] * m + rhs.v[i] * rhs.m) / (m + rhs.m);
    }
    m += rhs.m;
    updateColor();
    updateSize();
    return *this;
}

void Star::updateColor() {
    int i = 0;
    while (i + 1 < nBorders && borderMass[i] < m) ++i;
    col = starColors[i];
}

void Star::updateSize() {
    int i = 0;
    while (i + 1 < nBorders && borderMass[i] < m) ++i;
    i += (int)fmin(3, floor(m / massSun));
    size = i + 1;
}