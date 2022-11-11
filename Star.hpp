#pragma once

#include "cmath"
#include "constants.hpp"
#include <QPainter>

class Star {
public:
    double x[dim]{0};
    double v[dim]{0};
    double m;
    double f[dim]{0};
    QColor col;

    Star(const double *coord, const double *speed, double mass);

    Star& operator+=(const Star& rhs);
private:
    void updateColor();
};

Star::Star(const double *coord, const double *speed, double mass) {
    for (int k = 0; k < dim; ++k) {
        x[k] = coord[k];
        v[k] = speed[k];
    }
    m = mass;
    updateColor();
}

Star& Star::operator+=(const Star &rhs) {
    for (int i = 0; i < dim;++i) {
        f[i] += rhs.f[i];
        v[i] = (v[i]*m + rhs.v[i]*rhs.m) / (m + rhs.m);
    }
    m += rhs.m;
    updateColor();
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
