#include <iostream>
#include <cmath>
#include <algorithm>
#include "Galaxy.hpp"

double rsqrtQuake(double number) {
    double y = number;
    double x2 = y * 0.5;
    int64_t i = *(int64_t *) &y;  // evil floating point bit level hacking
    i = 0x5fe6eb50c7b537a9 - (i >> 1);      // what the fuck?
    y = *(double *) &i;
    y = y * (1.5 - (x2 * y * y));           // 1st iteration
//  y  = y * ( 1.5 - ( x2 * y * y ) );      // 2nd iteration, this can be removed
    return y;
}

void updateForce(const double *delta, double sqrDist, Star *a, Star *b) {
    double invDist = rsqrtQuake(sqrDist);
    double tmp = G * a->m * b->m * invDist * invDist * invDist;
    for (int k = 0; k < dim; ++k) {
        a->f[k] -= tmp * delta[k];
        b->f[k] += tmp * delta[k];
    }
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
        std::swap(at(l++), at(r--));
    }
    resize(starCnt);
    shrink_to_fit();
}

void Galaxy::mergeStars(size_t a, size_t b) {
    *at(a) += *at(b);
    if (at(b) == centralStar) centralStar = at(a);
    removeStar(b);
}

void Galaxy::removeStar(size_t i) {
    delete at(i);
    at(i) = nullptr;
    --starCnt;
}


Galaxy::Galaxy(size_t n): starCnt(n), resizeCnt(n / 2) {
    reserve(n);
    double pos[dim]{0};
    double v[dim]{0};
    // Creating central object
    centralStar = new Star(pos, v, massSun);
    push_back(centralStar);

    double baseMass = massEarth / (double)n * 6;
    // Creating other objects
    for (size_t i = 1; i < n; ++i) {
        double R  = rand() * spawnRadius / RAND_MAX,
               fi = rand() * 2 * M_PI / RAND_MAX;
        pos[0] = R * cos(fi);
        pos[1] = R * sin(fi);

        // вторая космическая скорость
        double absV = sqrt(G * centralStar->m / R);
        v[0] = absV * sin(fi);
        v[1] = -absV * cos(fi); // скорость направлена вдоль окружности с центром в начале координат
        push_back(new Star(pos, v, baseMass * (double)i));
    }
}

void Galaxy::update() {
    for (size_t i = 0; i < size(); ++i) {
        if (!at(i)) continue;
        if (!at(i)->isValid()) {
            if (at(i) == centralStar) {
                std::cout << "[WARN] central star out of range" << std::endl;
                return;
            }
            removeStar(i);
            continue;
        }

        for (size_t j = i + 1; j < size(); ++j) {
            if (!at(j)) continue;
            double delta[dim];
            double sqrDist = at(i)->getSqrDistTo(at(j), delta);
            // Connect if near enough
            if (sqrDist < sqrDistConnect) {
                mergeStars(i, j);
                continue;
            }
            updateForce(delta, sqrDist, at(i), at(j));
        }

        at(i)->updateVelAndCoords();
    }

    if (starCnt <= resizeCnt) {
        memory_clear();
        std::cout << "memory cleared!" << '\n';
        resizeCnt = starCnt / 2;
    }
}
