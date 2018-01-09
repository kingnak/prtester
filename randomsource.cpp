#include "randomsource.h"
#include <ctime>

RandomSource::RandomSource()
{
    srand(time(nullptr));
}

RandomSource &RandomSource::instance()
{
    static RandomSource inst_;
    return inst_;
}

int RandomSource::nextRand(int start, int end, int &cur) const
{
    int v = cur;
    do {
        v = nextRand(start, end);
    } while (v == cur);
    cur = v;
    return cur;
}

int RandomSource::nextRand(int start, int end) const
{
    int range = end-start;
    return rand()%range+start;
}
