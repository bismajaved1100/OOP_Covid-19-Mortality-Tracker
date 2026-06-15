#include <iostream>
#include <unordered_map>
#include <map>

#include "DailyCovidData.cpp"
#include "CsvFileCovidStats.h"
#include "CsvFileCovidStats.cpp"
#include "InputData.cpp"

using namespace std;

// ----------- Main Program ----------
int main() 
{
    InputData inputHandler;
    vector<DailyCovidData> covidData = inputHandler.readCsv("pakistan_covid_data.csv");

    if (covidData.empty()) 
	{
        cerr << "Exiting: No data available for processing." << endl;
        return 1;
    }

    CovidStats* stats = new CsvFileCovidStats(covidData);

    cout << "\n--- COVID-19 Snapshot (Pakistan) ---\n";
    cout << "Total cases : " << stats->getCases() << "\n";
    cout << "Total deaths: " << stats->getDeaths() << "\n";
    cout << "Death rate  : " << stats->computeDeathRate() << " %\n";

    cout << "\n--- Year-wise Death Rates ---\n";
    CsvFileCovidStats* csvStats = dynamic_cast<CsvFileCovidStats*>(stats);
    if (csvStats) 
	{
        map<int, double> yearlyRates = csvStats->getYearlyDeathRates();
        if (yearlyRates.empty()) 
		{
            cout << "No year-wise data available." << endl;
        } 
		else 
		{
           	int year;
			cout << "Enter the year which death rate you want to see? (2020 - 2023)" << endl;
			cin >> year;
			
			auto it = yearlyRates.find(year);
			if (it != yearlyRates.end()) 
			{
			    cout << "Death rate in " << year << " is: " << it->second << "%" << endl;
			} 
			else 
			{
			    cout << "No data available for year " << year << endl;
			}
        }
    } 
	else 
	{
        cerr << "Error: Could not retrieve year-wise data (dynamic_cast failed)." << endl;
    }

    delete stats;
    return 0;
}
