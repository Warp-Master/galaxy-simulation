#ifndef GALAXY_SIMULATION_CONSTANTS_HPP
#define GALAXY_SIMULATION_CONSTANTS_HPP
const int topX0 = 100, topY0 = 100, height = 800, width = 800;

const int dim = 2;
const int numStars = 4000;
const int borderMassC = 1;
const double G = 6.67408e-11,
             spawnRadius = 3e11,
             systemRadius = spawnRadius * 1.5,
             sqrDistConnect = 1e9 * 1e9,
             dt = 10000;
const double massSun = 1.98892e30,
             massJup = 1898.6e24,
             massUran = 86.832e24,
             massEarth = 5.9742e24,
             massVenus = 4.867e24;

const int centerX = width / 2;
const double coefX = (double) width / 2 / spawnRadius;
#endif //GALAXY_SIMULATION_CONSTANTS_HPP
