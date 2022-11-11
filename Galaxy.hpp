#pragma once

#include "cmath"
#include <QPainter>
#include <unordered_set>
#include <cstdint>


double invsqrtQuake( double number )
{
    double y = number;
    double x2 = y * 0.5;
    std::int64_t i = *(std::int64_t *) &y;  // evil floating point bit level hacking
    i = 0x5fe6eb50c7b537a9 - (i >> 1);      // what the fuck?
    y = *(double *) &i;
    y = y * (1.5 - (x2 * y * y));           // 1st iteration
//  y  = y * ( 1.5 - ( x2 * y * y ) );      // 2nd iteration, this can be removed
    return y;
}


class Galaxy {
public:
    size_t num;
    std::unordered_set<Star *> stars;
    Star *central_star;

    explicit Galaxy(size_t n = numStars) : num(n) {
        double x1[dim] = {0},
                v1[dim] = {0};
        central_star = new Star(x1, v1, massSun); // Creating central object
        stars.insert(central_star);
        // Creating other objects
        for (size_t i = 1; i < num; ++i) {
            double rad = 0;
            double R = rand() * systemRadius / RAND_MAX,
                    fi = (2 * M_PI * rand()) / RAND_MAX,
                    theta = (M_PI * rand()) / RAND_MAX;
            x1[0] = R * cos(fi);
            x1[1] = R * sin(fi);

//            if (dim == 3) {
//                x1[0] *= sin(theta);
//                x1[1] *= sin(theta);
//                x1[3] = R * cos(theta);
//            }

            for (double k: x1) {
                rad += k * k;
            }

            // вторая космическая скорость
            double absV = sqrt(G * central_star->m / sqrt(rad)),
                    alpha = (2 * M_PI * rand()) / RAND_MAX;
            // если размерность 3, нужен еще один угол как для координат(два угла годятся и для плоскости, желающие могут сделать)
            // v1[0] = absV * cos(alpha);
            // v1[1] = absV * sin(alpha);
            v1[0] = absV * sin(fi);
            v1[1] = -absV * cos(fi); // скорость направлена вдоль окружности с центром в начале координат
            stars.insert(new Star(x1, v1, massEarth / (double) num * (double) (6 * i)));
        }
    };

    ~Galaxy() { delete central_star; };

    void update() {
        double sqrDist;
        double dCoord[dim];

        for (Star *star_i: stars) { // force nullification
            std::fill_n(star_i->f, dim, 0);
        }

        for (auto star_i = stars.begin(); star_i != stars.end(); ++star_i) {
            for (auto star_j = std::next(star_i); star_j != stars.end();) {
                sqrDist = 0;
                for (int k = 0; k < dim; ++k) {
                    dCoord[k] = (*star_i)->x[k] - (*star_j)->x[k];
                    sqrDist += dCoord[k] * dCoord[k];
                }

                if (sqrDist < sqrDistConnect) {
                    // Connect if near enough
                    **star_i += **star_j;
                    if (*star_j == central_star) central_star = *star_i;
                    delete *star_j;
                    star_j = stars.erase(star_j);
                } else {
                    // Else update forces
                    double inv_dist = invsqrtQuake(sqrDist);
                    for (int k = 0; k < dim; ++k) {
                        double tmp = G * (*star_i)->m * (*star_j)->m / sqrDist;
                        (*star_i)->f[k] -= tmp * dCoord[k] * inv_dist;
                        (*star_j)->f[k] += tmp * dCoord[k] * inv_dist;
                    }
                    ++star_j;
                }
            }
            for (int k = 0; k < dim; ++k) {
                // Update velocity and coords
                (*star_i)->v[k] += dt * (*star_i)->f[k] / (*star_i)->m;
                (*star_i)->x[k] += dt * (*star_i)->v[k];
            }
        }
    }
};
