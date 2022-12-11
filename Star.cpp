#include <cmath>

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
const int nColor = sizeof(starColors) / sizeof(starColors[0]);

Star::Star(const double *coord, const double *velocity, double mass): col(0xffffff) {
    for (int k = 0; k < dim; ++k) {
        x[k] = coord[k];
        v[k] = velocity[k];
    }
    m = mass;
    updateColor();
    updateSize();
}

Star& Star::operator+=(const Star &rhs) {
    for (int i = 0; i < dim;++i) {
        v[i] = (v[i]*m + rhs.v[i]*rhs.m) / (m + rhs.m);
    }
    m += rhs.m;
    updateColor();
    updateSize();
    return *this;
}

void Star::updateColor() {
    int i = 0;
    while (borderMass[i] < m && i + 1 < nColor) ++i;
    col = starColors[i];
}

void Star::updateSize() {
    double mRatio = m / massSun;
    size = floor(exp(mRatio) + 2);
//    double mRatio2 = mRatio * mRatio;
//    double mRatio3 = mRatio2 * mRatio;
//    double rRatio = (0.00154297190393498651*mRatio3) - (0.06457707406352142243*mRatio2) + (0.98859893296201306612*mRatio) + 0.05502363603633853018;
//    size = std::floor(sunSize * 2 * rRatio);
//
//    int i = 0;
//    while (borderMass[i] < m && i + 1 < nColor) ++i;
//    size = (i+1)*2;
}