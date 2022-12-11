#include <iostream>
#include "cmath"
#include "Galaxy.hpp"


double rsqrtQuake( double number )
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

void Galaxy::memory_clear() {
    size_t l = 0;
    size_t r = size() - 1;
    while (l < r) {
        if (at(l)) {
            ++l;
            continue;
        }
        if (!at(r)) {
            --r;
            continue;
        }
        std::swap(at(l), at(r));
    }
    std::cout << "memory cleared!" << '\n';
    std::cout << "old size " << size() << '\n';
    std::cout << "new size " << star_cnt << std::endl;
    resize(star_cnt);
    shrink_to_fit();
}

void Galaxy::mergeStars(size_t a, size_t b) {
    *at(a) += *at(b);
    if (at(b) == central_star) central_star = at(a);
    delete at(b);
    at(b) = nullptr;
    --star_cnt;
}


Galaxy::Galaxy(size_t n): star_cnt(n), resizeCnt(n / 2) {
    reserve(n);
    double pos[dim] = {0},
           v[dim] = {0};

    // Creating central object
    central_star = new Star(pos, v, massSun);
    push_back(central_star);

    // Creating other objects
    for (size_t i = 1; i < n; ++i) {
        double R  = rand() * systemRadius / RAND_MAX,
               fi = rand() * 2 * M_PI / RAND_MAX;
        pos[0] = R * cos(fi);
        pos[1] = R * sin(fi);

        // вторая космическая скорость
        double absV = sqrt(G * central_star->m / R);
        v[0] = absV * sin(fi);
        v[1] = -absV * cos(fi); // скорость направлена вдоль окружности с центром в начале координат
        push_back(new Star(pos, v, massEarth / (double) n * (double) (6 * i)));
    }
}

void Galaxy::update() {
    for (Star *star: *this) { // force nullification
        if (!star) continue;
        std::fill_n(star->f, dim, 0);
    }

    for (size_t i = 0; i < size(); ++i) {
        if (!at(i)) continue;
        for (size_t j = i + 1; j < size(); ++j) {
            if (!at(j)) continue;
            // Calculate distance
            double sqrDist = 0;
            double dCoord[dim];
            for (int k = 0; k < dim; ++k) {
                dCoord[k] = at(i)->x[k] - at(j)->x[k];
                sqrDist += dCoord[k] * dCoord[k];
            }

            // Connect if near enough
            if (sqrDist < sqrDistConnect) {
                mergeStars(i, j);
                continue;
            }

            // Update forces
            double inv_dist = rsqrtQuake(sqrDist);
            for (int k = 0; k < dim; ++k) {
                double tmp = G * at(i)->m * at(j)->m / sqrDist;
                at(i)->f[k] -= tmp * dCoord[k] * inv_dist;
                at(j)->f[k] += tmp * dCoord[k] * inv_dist;
            }
        }

        // Update velocity and coords
        for (int k = 0; k < dim; ++k) {
            at(i)->v[k] += dt * at(i)->f[k] / at(i)->m;
            at(i)->x[k] += dt * at(i)->v[k];
        }
    }

    if (star_cnt <= resizeCnt) {
        memory_clear();
        resizeCnt = star_cnt / 2;
    }
}
