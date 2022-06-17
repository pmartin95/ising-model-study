#include <random>
#include <chrono>
#include "random.hpp"
int randomSpin(rand_t &rng)
{
    std::discrete_distribution<int> distribution{1, 0, 1};
    return distribution(rng) - 1;
}
unsigned seedGen()
{
    auto now = std::chrono::system_clock::now();

    time_t tnow = std::chrono::system_clock::to_time_t(now);
    tm *date = std::localtime(&tnow);
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    unsigned int dur;

    auto midnight = std::chrono::system_clock::from_time_t(std::mktime(date));
    auto since_midnight = now - midnight;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(since_midnight);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(since_midnight - hours);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_midnight - hours - minutes);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(since_midnight - hours - minutes - seconds);
    dur = hours.count() * 60 + minutes.count();
    dur = dur * 60 + seconds.count();
    dur = dur * 1000 + milliseconds.count();
    return dur;
}