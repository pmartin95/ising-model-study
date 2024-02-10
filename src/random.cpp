#include <random>
#include <chrono>
#include "random.hpp"
int randomSpin(rand_t &rng)
{
    static std::discrete_distribution<int> distribution{1, 0, 1}; // syntax note: the numbers are weights, not values.
    return distribution(rng) - 1;
}
unsigned seedGen()
{
    std::random_device rd;
    return rd();
}