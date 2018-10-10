#include "Intervals.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void Intervals::initialise(std::string xmlpath)
{
    std::ifstream fin;
    fin.open(xmlpath.c_str(), std::ios::in);
    if(!fin)
        throw "Failure while opening the file. It is either corrupted or given filepath is not correct.\n";
    std::regex low ("^[ ]*<low>[ ]*[0123456789]+[ ]*</low>$");
    std::regex high ("^[ ]*<high>[ ]*[0123456789]+[ ]*</high>$");
    while(!fin.eof())
    {
        std::string start_line, low_line, high_line;
        std::getline(fin, start_line);
        if(start_line.find("<interval>") != std::string::npos)
        {
            std::getline(fin, low_line);
            std::getline(fin, high_line);
            if(std::regex_match(low_line, low) && std::regex_match(high_line, high))
            {
                int left, right;
                std::stringstream s_low, s_high;
                s_low << low_line.substr(low_line.find_first_of('>')+1, low_line.find_last_of('<'));
                s_high << high_line.substr(high_line.find_first_of('>')+1, high_line.find_last_of('<'));
                s_low >> left;
                s_high >> right;
                if(left < INT_MAX && right < INT_MAX)
                    addInterval(left, right);
                else
                    throw "Too large number was given in one of two sections.\n";
                s_low.str("");
                s_high.str("");
                s_low.clear();
                s_high.clear();
            }
            else
                throw "Incorrect entry in \"interval\" section:\n"
                "1. A syntax error took place?\n"
                "2. \"low\" or \"high\" section contains a negative or non-integer value?\n"
                "3. \"low\" or \"high\" section contains another non-numeric character?\n"
                "4. More than one number were mentioned in a single section?\n";
        }
    }
    if(noIntervals())
        throw "No \"interval\" section found. Probably a syntax error or an incorrect xml file was passed.\n";
}

bool Intervals::noIntervals()
{
    return (m_intervals.empty());
}

std::pair<int, int> Intervals::getInterval(size_t index)
{
    return m_intervals[index];
}

void Intervals::addInterval(int left, int right)
{
    if(left <= right)
        m_intervals.emplace_back(std::make_pair(left, right));
    else
        m_intervals.emplace_back(std::make_pair(right, left));

}

size_t Intervals::numberOfIntervals()
{
    return m_intervals.size();
}
