#ifndef THREADSAFESET_H_INCLUDED
#define THREADSAFESET_H_INCLUDED

#include <mutex>
#include <set>
#include <vector>

struct ThreadSafeSet
{
    std::mutex m_mutex;
    std::set<int> m_set;
    void addValues(std::vector<int> values)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        m_set.insert(values.begin(), values.end());
    }

};

#endif // THREADSAFESET_H_INCLUDED
