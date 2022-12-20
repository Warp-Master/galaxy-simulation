#ifndef GALAXY_SIMULATION_GALAXY_HPP
#define GALAXY_SIMULATION_GALAXY_HPP
#include <vector>

#include "Star.hpp"


class Galaxy : std::vector<Star *> {
private:
    void memory_clear();
    void flush_tail();
    void mergeStars(size_t a, size_t b);
    void removeStar(size_t i);
public:
    using vector::begin;
    using vector::end;
    size_t starCnt;
    size_t resizeCnt;
    Star *centralStar;

    explicit Galaxy(size_t n = numStars);
    void update();
    std::pair<std::vector<Star *>::iterator,
            std::vector<Star *>::iterator> getTopKMass(const size_t &k);
    ~Galaxy() { delete centralStar; };
};

#endif //GALAXY_SIMULATION_GALAXY_HPP