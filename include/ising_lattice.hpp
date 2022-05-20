#include <vector>
#include "random.hpp"
class ising_lattice
{
private:
    /* data */
    std::vector<int> spins; // either 1 or -1
    std::vector<int> dims;  // size is the number of dimensions, the value the number of sites in that direction
    rand_t rng;

public:
    ising_lattice(/* args */);
    ~ising_lattice();
};

ising_lattice::ising_lattice(/* args */)
{
}

ising_lattice::~ising_lattice()
{
}
