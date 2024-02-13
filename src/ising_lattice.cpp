// The `ising_lattice` class models a 2D Ising lattice.
// It is used for simulating the Ising model in statistical mechanics.

#include "ising_lattice.hpp"

ising_lattice::ising_lattice(const std::vector<int> &dim)
{
    latticeDimensions = dim;                                                     // Set the height of the lattice.
    Nsites = std::accumulate(dim.begin(), dim.end(), 1, std::multiplies<int>()); // Calculate the total number of sites.
    spins.reserve(Nsites);                                                       // Reserve space for spin values.
    rng.seed(seedGen());                                                         // Seed the random number generator.
    for (int i = 0; i < Nsites; i++)
        spins.push_back(randomSpin(rng)); // Initialize spins randomly.
    nAccept = 0;                          // Initialize accepted spin flips to zero.
    nReject = 0;                          // Initialize rejected spin flips to zero.
}

// Destructor for the `ising_lattice` class.
ising_lattice::~ising_lattice()
{
}

// Calculate the Hamiltonian (energy) of the lattice.
// @return The Hamiltonian of the current lattice configuration.
float ising_lattice::hamiltonian() const
{
    float cumulative = 0.0;
    for (unsigned int i = 0; i < Nsites; i++)
    {
        std::vector<int> coordinates = getCoordinates(i);
        // Sum the interactions with right and down neighbors.
        for (int j = 0; j < latticeDimensions.size(); j++)
        {
            coordinates[j]++;
            cumulative += spins[i] * spins[getLinearIndex(coordinates)];
            coordinates[j]--;
        }
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
    std::vector<int> coordinates = getCoordinates(I);
    // Sum the spins of the nearest neighbors.
    for (int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = (coordinates[i] + latticeDimensions[i] + 1) / latticeDimensions[i];
        cumulative += spins[getLinearIndex(coordinates)];
        coordinates[i] = (coordinates[i] + latticeDimensions[i] - 2) / latticeDimensions[i];
        cumulative += spins[getLinearIndex(coordinates)];
    }
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

unsigned int ising_lattice::getLinearIndex(const std::vector<int> &coords) const
{
    unsigned int index = 0;
    unsigned int dimensionFactor = 1;
    for (int i = 0; i < coords.size(); ++i)
    {
        index += coords[i] * dimensionFactor;
        dimensionFactor *= latticeDimensions[i];
    }
    return index;
}
std::vector<int> ising_lattice::getCoordinates(unsigned int linearIndex) const
{
    std::vector<int> coords(latticeDimensions.size(), 0);

    for (int i = 0; i < latticeDimensions.size(); ++i)
    {
        coords[i] = linearIndex % latticeDimensions[i];
        linearIndex /= latticeDimensions[i];
    }

    return coords;
}
void ising_lattice::getCoordinates(unsigned int linearIndex, std::vector<int> coordinates) const
{
    coordinates = std::vector<int>(latticeDimensions.size(), 0);

    for (int i = 0; i < latticeDimensions.size(); ++i)
    {
        coordinates[i] = linearIndex % latticeDimensions[i];
        linearIndex /= latticeDimensions[i];
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
