#include "gtest/gtest.h"
#include "../Test_Primes/MainWorkflowFunctions.h"
#include "../Test_Primes/Intervals.cpp"
#include "../Test_Primes/MainWorkflowFunctions.cpp"

class IntervalsTest : public ::testing::Test
{
protected:
  
  void SetUp() override
  {
    single_interval.initialise("D:/Projects/Test_Primes/test_xml/test_single.xml");
    equal_intervals.initialise("D:/Projects/Test_Primes/test_xml/test_equal.xml");
    multiple_intervals.initialise("D:/Projects/Test_Primes/test_xml/test_multiple.xml");
    reversed_interval.initialise("D:/Projects/Test_Primes/test_xml/test_reversed.xml");
  }
  std::vector<std::pair<int, int>> single{ std::make_pair(2, 10) }, multiple{ std::make_pair(2, 10), std::make_pair(5, 15) },
    equal{ std::make_pair(100, 200), std::make_pair(100, 200) }, reversed{ std::make_pair(100, 200) };
  Intervals single_interval, equal_intervals, multiple_intervals, reversed_interval;
};

class IntervalsExceptionsTest : public ::testing::Test
{
protected:
  Intervals invalid;
};

class ResultsOnePrimeTest : public ::testing::Test
{
protected:

  void SetUp() override
  {
    prime.initialise("D:/Projects/Test_Primes/test_xml/test_prime.xml");

    primeNumbers(&results, prime.getInterval(0));
  }

  ThreadSafeSet results;
  Intervals prime;
  std::set<int> exp{ 29 };
};

class EmptyResultsTest : public ::testing::Test
{
protected:

  void SetUp() override
  {
    not_prime.initialise("D:/Projects/Test_Primes/test_xml/test_not_prime.xml");
    
    primeNumbers(&results, not_prime.getInterval(0));

  }

  ThreadSafeSet results;
  Intervals not_prime;
  std::set<int> exp;
}; 

class ResultsOneIntervalTest : public ::testing::Test
{
protected:

  void SetUp() override
  {
    simple_interval.initialise("D:/Projects/Test_Primes/test_xml/test_single.xml");

    primeNumbers(&results, simple_interval.getInterval(0));
  }

  ThreadSafeSet results;
  Intervals simple_interval;
  std::set<int> exp{2, 3, 5, 7};
}; 

class ResultsIntervalWithOneTest : public ::testing::Test
{
protected:

  void SetUp() override
  {
    interval_with_1.initialise("D:/Projects/Test_Primes/test_xml/test_with_1.xml");
    
    primeNumbers(&results, interval_with_1.getInterval(0));
  }

  ThreadSafeSet results;
  Intervals interval_with_1;
  std::set<int> exp{ 1, 2, 3, 5, 7 };
}; 

class ResultsMultiThreadTest : public ::testing::Test
{
protected:

  void SetUp() override
  {
    two_intervals.initialise("D:/Projects/Test_Primes/test_xml/test_multiple.xml");
    
    multithreadProcess(two_intervals, &results);
  }

  ThreadSafeSet results;
  Intervals two_intervals;
  std::set<int> exp{ 2, 3, 5, 7, 11, 13 };
};

TEST_F(IntervalsTest, SingleIntervalGenerated)
{
  EXPECT_EQ(single_interval.m_intervals, single);
}

TEST_F(IntervalsTest, EqualIntervalsGenerated)
{
  EXPECT_EQ(equal_intervals.m_intervals, equal);
}

TEST_F(IntervalsTest, MultipleIntervalsGenerated)
{
  EXPECT_EQ(multiple_intervals.m_intervals, multiple);
}

TEST_F(IntervalsTest, ReversedIntervalGeneratedProperly)
{
  EXPECT_EQ(reversed_interval.m_intervals, reversed);
}

TEST_F(IntervalsExceptionsTest, InvalidPathError)
{
  EXPECT_THROW(invalid.initialise(""), const char*);
}

TEST_F(IntervalsExceptionsTest, SyntaxError)
{
  EXPECT_THROW(invalid.initialise("D:/Projects/Test_Primes/test_xml/test_syntax_error.xml"), const char*);
}

TEST_F(IntervalsExceptionsTest, NoIntervalTagFoundError)
{
  EXPECT_THROW(invalid.initialise("D:/Projects/Test_Primes/test_xml/test_no_intervals.xml"), const char*);
}

TEST_F(IntervalsExceptionsTest, NegativeNumberError)
{
  EXPECT_THROW(invalid.initialise("D:/Projects/Test_Primes/test_xml/test_negative.xml"), const char*);
}

TEST_F(IntervalsExceptionsTest, NonIntegerNumberError)
{
  EXPECT_THROW(invalid.initialise("D:/Projects/Test_Primes/test_xml/test_non_integer.xml"), const char*);
}

TEST_F(IntervalsExceptionsTest, NonNumericCharacterError)
{
  EXPECT_THROW(invalid.initialise("D:/Projects/Test_Primes/test_xml/test_non_numeric.xml"), const char*);
}

TEST_F(ResultsOnePrimeTest, OnePrimeInResults)
{
  EXPECT_EQ(results.m_set, exp);
}

TEST_F(EmptyResultsTest, NoPrimeAddedToResults)
{
  EXPECT_EQ(results.m_set, exp);
}

TEST_F(ResultsOneIntervalTest, ActuallyPrimeNumbersAddedToResults)
{
  EXPECT_EQ(results.m_set, exp);
}

TEST_F(ResultsIntervalWithOneTest, OneIsAddedToResults)
{
  EXPECT_EQ(results.m_set, exp);
}

TEST_F(ResultsMultiThreadTest, AfterProcessProperUniqueNumbersStored)
{
  EXPECT_EQ(results.m_set, exp);
}



int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}