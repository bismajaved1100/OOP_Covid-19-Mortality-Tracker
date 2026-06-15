#ifndef CSVFILECOVIDSTATS_H
#define CSVFILECOVIDSTATS_H

#include "DailyCovidData.cpp" // Include the DailyCovidData class definition
#include "CovidStats.cpp"

#include <iostream> // For input/output operations
#include <string>   // For string handling
#include <vector>   // For vector container
#include <fstream>  // For file input/output
#include <unordered_map> // For efficient key-value storage (for yearly sums)
#include <map>       // For sorted key-value storage (for sorted yearly rates output)

using namespace std;

// DERIVED CLASS
// Class to handle COVID statistics from a CSV file.
class CsvFileCovidStats : public CovidStats
{
private:
    vector<DailyCovidData> historicalData;
    long long latestTotalCases;
    long long latestTotalDeaths;

    unordered_map<int, long long> yearlyNewCases;
    unordered_map<int, long long> yearlyNewDeaths;

public:
    CsvFileCovidStats(const vector<DailyCovidData>&);
    ~CsvFileCovidStats() = default;
    double computeDeathRate() override;
    long long getCases() const override;
    long long getDeaths() const override;
    map<int, double> getYearlyDeathRates() const; 
};

#endif