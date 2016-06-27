// Maya Calendar
// UVa IDs: 300
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> monthsOfHaab = {
        "pop", "no", "zip", "zotz", "tzec",
        "xul", "yoxkin", "mol", "chen", "yax",
        "zac", "ceh", "mac", "kankin", "muan",
        "pax", "koyab", "cumhu", "uayet"
    };
    
    vector<string> monthsOfTzolkin = {
        "ahau", "imix", "ik", "akbal", "kan", "chicchan",
        "cimi", "manik", "lamat", "muluk", "ok",
        "chuen", "eb", "ben", "ix", "mem",
        "cib", "caban", "eznab", "canac"
    };
    
    string numberOfTheDay, month, year;
    
    int n;
    cin >> n;
    
    cout << n << endl;
    
    while (cin >> numberOfTheDay >> month >> year)
    {
        int days = stoi(year) * 365;
        days += (find(monthsOfHaab.begin(), monthsOfHaab.end(), month) - monthsOfHaab.begin()) * 20;
        days += stoi(numberOfTheDay.substr(0, numberOfTheDay.length() - 1)) + 1;
        
        int yearValue = days / 260;
        if (days % 260 == 0)
        {
            yearValue = (days - 260) / 260;
            days = 260;
        }
        int monthValue = days % 20;
        int numberOfTheDayValue = days % 13;
        if (numberOfTheDayValue == 0) numberOfTheDayValue = 13;
            
        cout << numberOfTheDayValue << " " << monthsOfTzolkin[monthValue] << " " << yearValue << endl;
    }
    
	return 0;
}
