#ifndef DAILY_COVID_DATA_CPP
#define DAILY_COVID_DATA_CPP

#include <string>   // For string handling

using namespace std;

// class to hold our COVID data for a single day (from CSV)
class DailyCovidData 
{
public:
    string date;
    string location;
    long long newCases;
    long long totalCases;
    long long newDeaths;
    long long totalDeaths;
};

#endif