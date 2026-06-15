#ifndef COVIDSTATS_CPP
#define COVIDSTATS_CPP

using namespace std;

// BASE CLASS
// Abstract class to define the interface for COVID statistics computation.
// It provides methods to compute death rates and retrieve case/death counts.
class CovidStats 
{
public:
    virtual ~CovidStats() = default;
    virtual double computeDeathRate() = 0;
    virtual long long getCases() const = 0;
    virtual long long getDeaths() const = 0;
};

#endif