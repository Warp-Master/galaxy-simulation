#ifndef GALAXY_SIMULATION_GALAXY_HPP
#define GALAXY_SIMULATION_GALAXY_HPP
#include <vector>

#include "Star.hpp"


class Galaxy : std::vector<Star *> {
private:
    void memory_clear();
    void mergeStars(size_t a, size_t b);
public:
    using vector::begin;
    using vector::end;
    size_t star_cnt;
    size_t resizeCnt;
    Star *central_star;

    explicit Galaxy(size_t n = numStars);
    void update();
    ~Galaxy() { delete central_star; };
};

#endif //GALAXY_SIMULATION_GALAXY_HPP