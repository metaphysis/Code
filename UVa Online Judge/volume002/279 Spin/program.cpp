// Spin
// UVa ID: 279
// Verdict: Accepted
// Submission Date: 2016-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> steps;
    steps.push_back(0);
    
    for (int i = 1; i <= 29; i++)
        steps.push_back(2 * steps.back() + 2 * i - 1);
        
    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        int length, position;
        string orientation;
        cin >> length >> orientation >> position;
        
        int totalSteps = 0, sign = 1;
        for (int i = 0; i < orientation.length(); i++)
            if (orientation[i] == 'v')
            {
                totalSteps += steps[length - i] * sign;
                sign *= -1;
            }
        
        // if the number of disk is even, subtract it otherwise plus it
        sign *= -1;
        totalSteps += (length - position) * sign;    
        totalSteps += length + 1;
        
        cout << totalSteps << endl;
    }
    
	return 0;
}
