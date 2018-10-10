#include "MainWorkflowFunctions.h"
#include <iostream>
#include <list>
#include <fstream>
#include <thread>

void primeNumbers(ThreadSafeSet* results, std::pair<int, int> interval)
{
    std::vector<int> temp_result;
    while (interval.first <= interval.second)
    {
        bool flag = true;
        for(int i = 2; i <= interval.first/2; ++i)
        {
            if(interval.first % i == 0)
            {
                flag = false;
                break;
            }
        }

        if (flag == true)
            temp_result.emplace_back(interval.first);

        ++interval.first;
    }
    (*results).addValues(std::move(temp_result));
}

void multithreadProcess(Intervals &intervals, ThreadSafeSet* results)
{
    std::list<std::thread> threads;
        for (size_t i = 0; i < intervals.numberOfIntervals(); ++i)
        {
            threads.emplace_back(primeNumbers, results, intervals.getInterval(i));
        }
        for (auto& thr : threads)
        {
            if(thr.joinable())
                thr.join();
        }
}

void out(ThreadSafeSet* results)
{
    std::ofstream f("D:/Projects/Prime_Numbers/output.xml");
        f << "<root>\n <primes>";
        for (const auto& res : (*results).m_set)
            f << res << ' ';
        f << "</primes>\n</root>";
}
