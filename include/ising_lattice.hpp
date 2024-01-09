#pragma once
#include <vector>
#include <utility>
#include "random.hpp"

// The ising_lattice class models a 2D Ising model lattice.
class ising_lattice {
private:
    std::vector<int> spins; // Stores the spin values (1 or -1) of each lattice site.
    rand_t rng; // Random number generator for spin manipulation.
    unsigned int Nx, Ny; // Dimensions of the lattice: Nx (width) and Ny (height).
    unsigned int Nsites; // Total number of sites in the lattice (Nx * Ny).
    unsigned int nAccept, nReject; // Counters for accepted and rejected spin flips.
    float J; // Coupling constant in the Ising model.
    float beta; // Inverse temperature parameter in the Ising model.

    // Converts 2D lattice coordinates (x, y) to a 1D array index.
    unsigned int xyToIndex(unsigned int x, unsigned int y) const;
    // Converts a 1D array index to 2D lattice coordinates (x, y).
    std::pair<unsigned int, unsigned int> indexToXY(unsigned int I) const;
    // Sums the spins of neighboring sites around site I.
    float sumAround(unsigned int I) const;
    // Proposes a spin flip at site I and decides whether to accept it.
    void proposeFlip(unsigned int I);

public:
    // Constructor: Initializes a lattice of size x by y.
    ising_lattice(unsigned int x, unsigned int y);
    // Destructor: Currently not used but included for future scalability.
    ~ising_lattice();

    // Calculates the Hamiltonian (energy) of the lattice.
    float hamiltonian() const;
    // Calculates the magnetization of the lattice.
    float magnetization() const;
    // Performs a sweep: attempts to flip each spin in the lattice once.
    void sweep();
    // Sets all spins to 1, representing a system at low temperature.
    void coldStart();

    // Getter for the acceptance ratio of spin flips.
    float getAcceptance() const;
    // Getter for the number of accepted spin flips.
    unsigned int getAccept() const;
    // Getter for the number of rejected spin flips.
    unsigned int getReject() const;
    // Setter for the coupling constant J.
    void setJ(float jIn);
    // Setter for the inverse temperature parameter beta.
    void setBeta(float betaIn);
};
