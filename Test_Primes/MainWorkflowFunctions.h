#ifndef MAINWORKFLOWFUNCTIONS_H_INCLUDED
#define MAINWORKFLOWFUNCTIONS_H_INCLUDED

#include "ThreadSafeSet.h"
#include "Intervals.h"

void primeNumbers(ThreadSafeSet* results, std::pair<int, int> interval);

void multithreadProcess(Intervals &intervals, ThreadSafeSet* results);

void out(ThreadSafeSet* results);

#endif // MAINWORKFLOWFUNCTIONS_H_INCLUDED
