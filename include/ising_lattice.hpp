#include <vector>
#include <utility>
#include "random.hpp"
#pragma once

class ising_lattice
{
private:
    /* data */
    std::vector<int> spins; // either 1 or -1
    rand_t rng;
    unsigned int Nx, Ny, Nsites;
    unsigned int nAccept, nReject;
    float J, beta;

    /*private methods*/
    unsigned int xyToIndex(unsigned int x, unsigned int y) const;
    std::pair<unsigned int, unsigned int> indexToXY(unsigned int I) const;
    float sumAround(unsigned int I) const;
    void proposeFlip(unsigned int I);

public:
    ising_lattice(unsigned int x, unsigned int y);
    ~ising_lattice();

    float hamiltonian() const;
    float magnetization() const;
    void sweep();
    void coldStart();

    // Gets/Sets
    float getAcceptance() const;
    unsigned int getAccept() const;
    unsigned int getReject() const;
    void setJ(float jIn);
    void setBeta(float betaIn);
};
