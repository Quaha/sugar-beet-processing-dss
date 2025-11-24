#include "utils.hpp"

#include <random>

const double EPS = 1e-9;
const int DAYS_PER_STAGE = 7;

double GetRandomDouble(double min, double max) {
    static std::mt19937 gen;
    std::uniform_real_distribution<double> dist(min + EPS, max - EPS);
    return dist(gen);
}
