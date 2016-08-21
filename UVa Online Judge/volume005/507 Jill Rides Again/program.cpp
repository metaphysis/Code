// Jill Rides Again
// UVa ID: 507
// Verdict: Accepted
// Submission Date: 2016-08-21
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int r = 1; r <= cases; r++)
    {
        int s, niceness;
        cin >> s >> niceness;
        
        int max = niceness, start = 1, end = 2;
        int maxCurrent = niceness, startCurrent = 1, endCurrent = 2;
        
        s--;
        for (int i = 2; i <= s; i++)
        {
            cin >> niceness;

            endCurrent = i + 1;
            maxCurrent += niceness;
            
            if (niceness > maxCurrent)
            {
                startCurrent = i, endCurrent = i + 1;
                maxCurrent = niceness;
            }

            if (maxCurrent > max || (maxCurrent == max && abs(endCurrent - startCurrent) > abs(end - start)))
            {
                max = maxCurrent;
                start = startCurrent, end = endCurrent;
            }
        }
        
        if (max > 0)
        {
            cout << "The nicest part of route " << r << " is between stops ";
            cout << start << " and " << end << '\n';
        }
        else
            cout << "Route " << r << " has no nice parts\n";
    }
    
	return 0;
}
