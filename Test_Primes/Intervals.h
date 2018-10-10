#ifndef INTERVALS_H_INCLUDED
#define INTERVALS_H_INCLUDED

#include <vector>
#include <string>

struct Intervals
{
    std::vector<std::pair<int, int>> m_intervals;
    bool noIntervals();
    std::pair<int, int> getInterval(size_t index);
    void addInterval(int left, int right);
    size_t numberOfIntervals();
    void initialise(std::string xmlpath);
};

#endif // INTERVALS_H_INCLUDED
