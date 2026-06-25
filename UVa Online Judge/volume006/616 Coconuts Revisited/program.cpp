// Coconuts, Revisited
// UVa ID: 616
// Verdict: Accepted
// Submission Date: 2016-08-28
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, nn;
    while (cin >> n, n >= 0)
    {
        nn = n;
        
        if (n <= 2)
        {
            cout << n << " coconuts, no solution\n";
            continue;
        }
        
        if (n == 3)
        {
            cout << "3 coconuts, 2 people and 1 monkey\n";
            continue;
        }
        
        n--;
        vector<int> bigger, smaller;
        int up_limit = sqrt(n);
        for (int i = 2; i <= up_limit; i++)
            if (n % i == 0)
            {
                bigger.push_back(n / i);
                smaller.insert(smaller.begin(), i);
            }
        
        for (int i = 0; i < smaller.size(); i++)
            bigger.push_back(smaller[i]);
            
        bool solutionFound = false;
        for (int i = 0; i < bigger.size(); i++)
        {
            int times = 0, people = bigger[i];
            
            n = nn;
            while (true)
            {
                n--;
                if (n % people == 0)
                    n = (n / people) * (people - 1);
                else
                    break;
                
                times++;
                
                if (n % people == 0 || times > people)
                    break;
            }
            
            if (times == people && n % people == 0)
            {
                cout << nn << " coconuts, " << people << " people and 1 monkey\n";
                solutionFound = true;
                break;
            }
        }
        
        if (!solutionFound)
            cout << nn << " coconuts, no solution\n";
    }
    
	return 0;
}
