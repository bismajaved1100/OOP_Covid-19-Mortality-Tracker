#ifndef CSVFILECOVIDSTATS_CPP
#define CSVFILECOVIDSTATS_CPP

#include "CsvFileCovidStats.h" // Include the header file for CsvFileCovidStats

#include <iostream>
#include <string>   // For string handling
#include <vector>   // For vector container
#include <fstream>  // For file input/output
#include <unordered_map> // For efficient key-value storage (for yearly sums)
#include <map>       // For sorted key-value storage (for sorted yearly rates output)

using namespace std;

// Constructor for CsvFileCovidStats
CsvFileCovidStats::CsvFileCovidStats(const vector<DailyCovidData>& data) : historicalData(data), latestTotalCases(0), latestTotalDeaths(0) 
{
    if (!historicalData.empty()) 
    {
        latestTotalCases = historicalData.back().totalCases;
        latestTotalDeaths = historicalData.back().totalDeaths;

        for (const auto& record : historicalData) 
        {
            int year = 0;
            // Extract year from M/D/YYYY or MM/DD/YYYY format
            size_t lastSlashPos = record.date.rfind('/'); // Find the last '/'
            if (lastSlashPos != string::npos && record.date.length() >= lastSlashPos + 5) 
            {
                string yearStr = record.date.substr(lastSlashPos + 1, 4);
                try 
                {
                    year = stoi(yearStr);
                } 
                catch (const invalid_argument& e) 
                {
                    cerr << "Warning: Invalid year format in date '" << record.date << "'. Skipping record." << endl;
                    continue;
                } 
                catch (const out_of_range& e) 
                {
                    cerr << "Warning: Year value out of range in date '" << record.date << "'. Skipping record." << endl;
                    continue;
                }
            } 
            else 
            {
                cerr << "Warning: Date string format unexpected for year extraction: '" << record.date << "'. Skipping record." << endl;
                continue;
            }

            yearlyNewCases[year] += record.newCases;
            yearlyNewDeaths[year] += record.newDeaths;
        }
    } 
    else 
    {
        cerr << "Warning: No valid data provided to CsvFileCovidStats constructor." << endl;
    }
}

double CsvFileCovidStats::computeDeathRate() 
{
    if (latestTotalCases == 0) return 0.0;
    return (double)latestTotalDeaths / latestTotalCases * 100.0;
}

long long CsvFileCovidStats::getCases() const 
{
    return latestTotalCases;
}

long long CsvFileCovidStats::getDeaths() const 
{
    return latestTotalDeaths;
}

map<int, double> CsvFileCovidStats::getYearlyDeathRates() const 
{
    map<int, double> rates; 

    for (const auto& pair : yearlyNewCases) 
    {
        int year = pair.first;
        long long cases = pair.second;
        long long deaths = 0;

        auto it = yearlyNewDeaths.find(year);
        if (it != yearlyNewDeaths.end()) 
        {
            deaths = it->second;
        }

        if (cases == 0)
            rates[year] = 0.0;
        else
            rates[year] = (double)deaths / cases * 100.0;
    }
    return rates;
}

#endif