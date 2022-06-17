#include <iostream>
#include <random>
#include "ising_lattice.hpp"
#include "random.hpp"
int main()
{
    ising_lattice hotSim(10, 10);

    hotSim.setJ(1.0);
    for (float BetaTemp = 0.4; BetaTemp < 0.6; BetaTemp += 0.001)
    {
        std::vector<float> data;
        hotSim.setBeta(BetaTemp);
        // thermalize
        for (int i = 0; i < 30; i++)
            hotSim.sweep();
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                hotSim.sweep();
            }
            data.push_back(hotSim.magnetization());
        }
        float aveMagnetization = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        std::cout << 1.0 / BetaTemp << ": " << aveMagnetization << std::endl;
    }

    return 0;
}