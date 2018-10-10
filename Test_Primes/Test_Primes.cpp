
#include <iostream>
#include "MainWorkflowFunctions.h"

int main()
{
  try
  {
    Intervals intervals;
    intervals.initialise("D:/Projects/Prime_Numbers/test.xml");
    ThreadSafeSet results;
    multithreadProcess(intervals, &results);
    out(&results);
  }
  catch (const char* msg)
  {
    std::cout << msg << std::endl;
  }

  return 0;
}