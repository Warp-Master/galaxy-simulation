#include "Star.hpp"
#include "constants.hpp"
#include <cmath>

Star::Star(const double *coord, const double *velocity, double mass) {
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
    col = colStar[nColor - 1];
    for (int i = 0; i < nColor - 1; ++i) {
        if (m <= borderMass[i]) {
            col = colStar[i];
            break;
        }
    }
}

void Star::updateSize() {
    double mRatio = m / massSun;
    double mRatio2 = mRatio * mRatio;
    double mRatio3 = mRatio2 * mRatio;
    double rRatio = (0.00154297190393498651*mRatio3) - (0.06457707406352142243*mRatio2) + (0.98859893296201306612*mRatio) + 0.05502363603633853018;
    size = std::floor(sunSize * rRatio);
}