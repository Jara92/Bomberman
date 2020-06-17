/**
 * @author Jaroslav Fikar
*/

#pragma once
#include <chrono>
#include <random>

class CRandom
{
public:
    /**
     * Generate random number in given range.
     * @param min Minimum value which can be generated.
     * @param max Minimum value which CANNOT BE GENERATED.
     * @return Rendom number.
     */
    static unsigned int Random(unsigned int min, unsigned int max)
    {
        // Set random movement timer with random delay.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
        std::default_random_engine randomEngine(seed);
        unsigned int randomNumber = (randomEngine() % (max - min)) + min;

        return randomNumber;
    }
};

