// The `ising_lattice` class models a 2D Ising lattice.
// It is used for simulating the Ising model in statistical mechanics.

#include "ising_lattice.hpp"

// Constructor for the `ising_lattice` class.
// Initializes a lattice of size x by y.
// @param x The width of the lattice.
// @param y The height of the lattice.
ising_lattice::ising_lattice(unsigned int x, unsigned int y)
{
    Nx = x; // Set the width of the lattice.
    Ny = y; // Set the height of the lattice.
    Nsites = Nx * Ny; // Calculate the total number of sites.
    spins.reserve(Nsites); // Reserve space for spin values.
    rng.seed(seedGen()); // Seed the random number generator.
    for (int i = 0; i < Nsites; i++)
        spins.push_back(randomSpin(rng)); // Initialize spins randomly.
    nAccept = 0; // Initialize accepted spin flips to zero.
    nReject = 0; // Initialize rejected spin flips to zero.
}

// Destructor for the `ising_lattice` class.
ising_lattice::~ising_lattice()
{
}

// Convert x, y coordinates to a linear index.
// @param x The x-coordinate.
// @param y The y-coordinate.
// @return The linear index corresponding to the (x, y) coordinates.
unsigned int ising_lattice::xyToIndex(unsigned int x, unsigned int y) const
{
    return Ny * x + y;
}

// Convert a linear index to x, y coordinates.
// @param I The linear index.
// @return A pair of unsigned ints representing the (x, y) coordinates.
std::pair<unsigned int, unsigned int> ising_lattice::indexToXY(unsigned int I) const
{
    std::pair<unsigned int, unsigned int> result;
    result.first = I / Ny; // Calculate the x-coordinate.
    result.second = I % Ny; // Calculate the y-coordinate.
    return result;
}

// Calculate the Hamiltonian (energy) of the lattice.
// @return The Hamiltonian of the current lattice configuration.
float ising_lattice::hamiltonian() const
{
    float cumulative = 0.0;
    for (unsigned int i = 0; i < Nsites; i++)
    {
        std::pair XY = indexToXY(i);
        // Sum the interactions with right and down neighbors.
        cumulative += spins[i] * spins[xyToIndex((XY.first + 1) % Nx, XY.second)];
        cumulative += spins[i] * spins[xyToIndex(XY.first, (XY.second + 1) % Ny)];
    }
    return -J * cumulative; // Return the negative of the coupling constant times the cumulative sum.
}

// Calculate the total magnetization of the lattice.
// @return The magnetization of the current lattice configuration.
float ising_lattice::magnetization() const
{
    float cumulative = 0.0;
    for (unsigned int i = 0; i < Nsites; i++)
    {
        cumulative += spins[i]; // Sum all spins.
    }
    return cumulative / Nsites; // Return the average spin.
}

// Calculate the sum of the spins around a given index.
// @param I The index of the central spin.
// @return The sum of the spins around the central spin.
float ising_lattice::sumAround(unsigned int I) const
{
    float cumulative = 0.0;
    std::pair XY = indexToXY(I);
    // Sum the spins of the nearest neighbors.
    cumulative += spins[xyToIndex((XY.first + 1) % Nx, XY.second)];
    cumulative += spins[xyToIndex(XY.first, (XY.second + 1) % Ny)];
    cumulative += spins[xyToIndex((XY.first - 1 + Nx) % Nx, XY.second)];
    cumulative += spins[xyToIndex(XY.first, (XY.second - 1 + Ny) % Ny)];
    return cumulative;
}

// Proposes a flip of the spin at index I.
// Accepts or rejects the flip based on the Metropolis algorithm.
// @param I The index of the spin to flip.
void ising_lattice::proposeFlip(unsigned int I)
{
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    float dE = std::min(std::exp(-2.0 * J * beta * spins[I] * sumAround(I)), 1.0);
    // Flip the spin if the random number is less than dE.
    if (dE > distribution(rng))
    {
        spins[I] = -spins[I];
        nAccept++; // Increment the count of accepted flips.
    }
    else
    {
        nReject++; // Increment the count of rejected flips.
    }
}

// Performs a sweep of the lattice, proposing a flip at each site.
void ising_lattice::sweep()
{
    for (int i = 0; i < Nsites; i++)
        proposeFlip(i);
}

// Initializes all spins in the lattice to 1 (cold start).
void ising_lattice::coldStart()
{
    for (int i = 0; i < Nsites; i++)
        spins[i] = 1.0;
}

// Getter and setter methods.
float ising_lattice::getAcceptance() const
{
    return static_cast<float>(nAccept) / static_cast<float>(nAccept + nReject);
}
unsigned int ising_lattice::getAccept() const
{
    return nAccept;
}
unsigned int ising_lattice::getReject() const
{
    return nReject;
}
void ising_lattice::setJ(float jIn)
{
    J = jIn;
}
void ising_lattice::setBeta(float betaIn)
{
    beta = betaIn;
}
