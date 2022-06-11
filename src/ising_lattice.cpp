#include "ising_lattice.hpp"

ising_lattice::ising_lattice(unsigned int x, unsigned int y)
{
    Nx = x;
    Ny = y;
    Nsites = Nx * Ny;
    spins.reserve(Nsites);
    rng.seed(seedGen());
    for (int i = 0; i < Nsites; i++)
        spins.push_back(randomSpin(rng));
}

ising_lattice::~ising_lattice()
{
}

unsigned int ising_lattice::xyToIndex(unsigned int x, unsigned int y) const
{
    return Ny * x + y;
}

std::pair<unsigned int, unsigned int> ising_lattice::indexToXY(unsigned int I) const
{
    std::pair<unsigned int, unsigned int> result;
    result.first = I / Ny;
    result.second = I % Ny;
    return result;
}

float ising_lattice::hamiltonian() const
{
    float cumulative = 0.0;
    for (unsigned int i = 0; i < Nsites; i++)
    {
        std::pair XY = indexToXY(i);
        cumulative += spins[i] * spins[xyToIndex((XY.first + 1) % Nx, (XY.second) % Ny)];
        cumulative += spins[i] * spins[xyToIndex((XY.first) % Nx, (XY.second + 1) % Ny)];
    }
    return -J * cumulative;
}

float ising_lattice::magnetization() const
{
    float cumulative = 0.0;
    for (unsigned int i = 0; i < Nsites; i++)
    {
        cumulative += spins[i];
    }
    return cumulative / Nsites;
}

float ising_lattice::sumAround(unsigned int I) const
{
    float cumulative = 0.0;
    std::pair XY = indexToXY(I);
    cumulative += spins[xyToIndex((XY.first + 1) % Nx, XY.second)];
    cumulative += spins[xyToIndex(XY.first, (XY.second + 1) % Ny)];
    cumulative += spins[xyToIndex((XY.first - 1 + Nx) % Nx, XY.second)];
    cumulative += spins[xyToIndex(XY.first, (XY.second - 1 + Ny) % Ny)];
    return cumulative;
}

void ising_lattice::proposeFlip(unsigned int I)
{
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    float dE = std::min(std::exp(-2.0 * J * spins[I] * sumAround(I)), 1.0);
    if (dE > distribution(rng))
        spins[I] = -spins[I];
}

void ising_lattice::sweep()
{
    for (int i = 0; i < Nsites; i++)
        proposeFlip(i);
}

void ising_lattice::coldStart()
{
    for (int i = 0; i < Nsites; i++)
        spins[i] = 1.0;
}