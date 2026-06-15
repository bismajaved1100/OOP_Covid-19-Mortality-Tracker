#ifndef INPUTDATA_CPP
#define INPUTDATA_CPP

#include "DailyCovidData.cpp" // Include the DailyCovidData class definition
#include <iostream> // For input/output operations
#include <string>   // For string handling
#include <vector>   // For vector container 
#include <fstream>  // For file input/output
#include <sstream>  // For string stream operations 


using namespace std;

class InputData 
{
private:
    // Helper function to convert string to long long, handling empty/invalid strings
    long long parseLongLong(const string& s) 
	{
        if (s.empty()) 
		{
            return 0; // Treat empty strings as 0
        }
        try 
		{
            return stoll(s); // Standard library function to convert string to long long
        } 
		catch (const invalid_argument& e) 
		{
            cerr << "Warning: Invalid number format encountered: '" << s << "'. Setting to 0." << endl;
            return 0;
        } 
		catch (const out_of_range& e) 
		{
            cerr << "Warning: Number out of range for long long: '" << s << "'. Setting to 0." << endl;
            return 0;
        }
    }
    
public:
    // Reads and parses COVID-19 data from a CSV file.
    // Returns a vector of DailyCovidData structs.
    // Handles file opening errors and data parsing issues.
    vector<DailyCovidData> readCsv(const string& filePath) 
	{
        vector<DailyCovidData> data;
        ifstream inputFile(filePath);

        if (!inputFile.is_open()) 
		{
            cerr << "Error: Could not open the file " << filePath << endl;
            // Return an empty vector to indicate failure, allowing calling code to handle it.
            return data;
        }
		else
		{
	        string line;
	        // Read and discard header row
	        getline(inputFile, line);
	
	        while (getline(inputFile, line))
			{
	            stringstream ss(line);
	            string segment;
	            vector<string> segments;
	
	            // Split the line by comma and store segments
	            while(getline(ss, segment, ',')) 
				{
	                segments.push_back(segment);
	            }
	
	            // Define column indices based on your 'pakistan_covid_data.csv' structure
	            const int LOCATION_COL = 2;     // 'location'
	            const int DATE_COL = 3;         // 'date' (e.g., M/D/YYYY or MM/DD/YYYY)
	            const int TOTAL_CASES_COL = 4;  // 'total_cases'
	            const int NEW_CASES_COL = 5;    // 'new_cases'
	            const int TOTAL_DEATHS_COL = 6; // 'total_deaths'
	            const int NEW_DEATHS_COL = 7;   // 'new_deaths'
	
	            // Ensure we have enough segments to parse the required data
	            if (segments.size() > NEW_DEATHS_COL) 
				{
	                DailyCovidData currentDay;
	                currentDay.location = segments[LOCATION_COL];
	                currentDay.date = segments[DATE_COL];
	                currentDay.totalCases = parseLongLong(segments[TOTAL_CASES_COL]);
	                currentDay.newCases = parseLongLong(segments[NEW_CASES_COL]);
	                currentDay.totalDeaths = parseLongLong(segments[TOTAL_DEATHS_COL]);
	                currentDay.newDeaths = parseLongLong(segments[NEW_DEATHS_COL]);
	
	                data.push_back(currentDay);
	            } 
				else 
				{
	                cerr << "Warning: Skipping malformed line (not enough columns): " << line << endl;
	            }
	        }
	
	        inputFile.close();
	        return data;
    	}
    }
  
};

#endif