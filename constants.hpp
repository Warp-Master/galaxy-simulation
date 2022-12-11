#ifndef GALAXY_SIMULATION_CONSTANTS_HPP
#define GALAXY_SIMULATION_CONSTANTS_HPP
const int topX0 = 100, topY0 = 100, h = 800, length = 800;

const int dim = 2;
const int numStars = 4000;
const int borderMassC = 1;
const double G = 6.67408e-11,
        systemRadius = 1e12,
        sqrDistConnect = 1e9 * 1e9 * 4,
        dt = 10000;
const double massSun = 1.98892e30,
        massJup = 1898.6e24,
        massUran = 86.832e24,
        massEarth = 5.9742e24,
        massVenus = 4.867e24;

const int sunSize = 50; // pixels
#endif //GALAXY_SIMULATION_CONSTANTS_HPP
