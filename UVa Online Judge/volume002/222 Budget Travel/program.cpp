// Budget Travel
// UVa ID: 222
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct station
{
    int index;
    double milesFromOrigin, pricePerGallon;
    int minimumCost;
};

struct driver
{
    int index;
    double milesTravel;
    int totalCost;
};

double totalDistance, capacityOfTank, costAtStart;
double milesPerGallon, milesFromOrigin, pricePerGallon;
int counter, minimumCost;

vector<station> stations;

void dfs(driver aDriver)
{
    double end = aDriver.milesTravel + capacityOfTank * milesPerGallon;
    
    if (end >= totalDistance)
    {
        if (minimumCost < 0 || aDriver.totalCost < minimumCost)
            minimumCost = aDriver.totalCost;
        return;
    }

    for (int i = aDriver.index + 1; i < stations.size() - 1; i++)
    {
        if (end >= stations[i].milesFromOrigin)
        {
            double gasolineUsed = (stations[i].milesFromOrigin - aDriver.milesTravel) / milesPerGallon;
            double travel = (capacityOfTank - gasolineUsed) * milesPerGallon;
            
            if (travel >= (stations[i + 1].milesFromOrigin - stations[i].milesFromOrigin) &&
                2 * gasolineUsed <= capacityOfTank)
                continue;
            
            driver newDriver = aDriver;
            newDriver.totalCost += round(gasolineUsed * stations[i].pricePerGallon);
            newDriver.totalCost += 200;
            
            if (stations[i].minimumCost > 0 && stations[i].minimumCost < newDriver.totalCost)
                continue;
            
            stations[i].minimumCost = newDriver.totalCost;
            newDriver.milesTravel = stations[i].milesFromOrigin;
            newDriver.index = i;
            
            dfs(newDriver);
        }
        else
            break;
    }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    
    while (cin >> totalDistance)
    {
        if (totalDistance < 0.0)
            break;
            
        stations.clear();
        
        cin >> capacityOfTank >>  milesPerGallon >> costAtStart >> counter;
        
        stations.push_back((station){0, milesFromOrigin, pricePerGallon, 0});
        for (int i = 1; i <= counter; i++)
        {
            cin >> milesFromOrigin >> pricePerGallon;
            stations.push_back((station){i, milesFromOrigin, pricePerGallon, -1});
        }
        stations.push_back((station){counter + 1, totalDistance, 0.0, -1});
        
        cout << "Data Set #" << ++cases << endl;
        
        minimumCost = -1;
        
        driver aDriver;
        aDriver.index = 0;
        aDriver.totalCost = (int)(costAtStart * 100.0);
        aDriver.milesTravel = 0.0;
        
        dfs(aDriver);
        
        cout << "minimum cost = $";
        cout << (minimumCost / 100);
        cout << ".";
        if (minimumCost % 100 < 10)
            cout << "0";
        cout << (minimumCost % 100);
        cout << endl;
    }
    
	return 0;
}
