#ifndef RANDOMSOURCE_H
#define RANDOMSOURCE_H

#include <QtGlobal>

class RandomSource
{
    RandomSource();
    Q_DISABLE_COPY(RandomSource)
public:
    static RandomSource &instance();
    int nextRand(int start, int end, int &cur) const;
    int nextRand(int start, int end) const;
};

#endif // RANDOMSOURCE_H
