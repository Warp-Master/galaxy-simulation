#pragma once

#include "cmath"
#include "constants.hpp"
#include <QPainter>

class Star {
public:
    static size_t starCounter;
    double x[dim]{};
    double v[dim]{};
    double m;
    double f[dim]{};
    QColor col;

    Star(const double *coord, const double *speed, double mass);

    ~Star() { starCounter--; }
    Star& operator+=(const Star& rhs);
private:
    void updateColor();
};

size_t Star::starCounter = 0;

Star::Star(const double *coord, const double *speed, double mass) {
    for (int k = 0; k < dim; ++k) {
        x[k] = coord[k];
        v[k] = speed[k];
    }
    m = mass;
    updateColor();
    starCounter++;
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
