#include <random>
#pragma once
typedef std::mt19937_64 rand_t;

int randomSpin(rand_t &rng);
unsigned seedGen();