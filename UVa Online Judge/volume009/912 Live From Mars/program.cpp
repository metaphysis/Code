// Live From Mars
// UVa ID: 912
// Verdict: Accepted
// Submission Date: 2017-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int m, cases = 0;
    
    while (cin >> m)
    {
        vector<string> dna1, dna2;
        string element;
        
        for (int i = 1; i <= m; i++)
        {
            cin >> element;
            dna1.push_back(element);
        }
        
        for (int i = 1; i <= m; i++)
        {
            cin >> element;
            dna2.push_back(element);
        }
        
        bool yes = true;
        map<string, string> mutation;
        
        while (true)
        {
            bool updated = false;
            for (int i = 0; i < m; i++)
            {
                if (isalpha(dna1[i].front()) && isalpha(dna2[i].front()))
                {
                    if (dna1[i] != dna2[i])
                    {
                        yes = false;
                        goto print;
                    }
                }
                else if (isdigit(dna1[i].front()) && isdigit(dna2[i].front()))
                {
                }
                else
                {
                    if (isdigit(dna1[i].front()))
                    {
                        if (mutation.find(dna1[i]) != mutation.end())
                        {
                            if (mutation[dna1[i]] != dna2[i])
                            {
                                yes = false;
                                goto print;
                            }
                        }
                        else
                        {
                            mutation[dna1[i]] = dna2[i];
                            updated = true;
                        }
                    }
                    else
                    {
                        if (mutation.find(dna2[i]) != mutation.end())
                        {
                            if (mutation[dna2[i]] != dna1[i])
                            {
                                yes = false;
                                goto print;
                            }
                        }
                        else
                        {
                            mutation[dna2[i]] = dna1[i];
                            updated = true;
                        }
                    }
                }
            }
            
            for (int i = 0; i < m; i++)
            {
                if (isdigit(dna1[i].front()) && mutation.find(dna1[i]) != mutation.end())
                    dna1[i] = mutation[dna1[i]];
                if (isdigit(dna2[i].front()) && mutation.find(dna2[i]) != mutation.end())
                    dna2[i] = mutation[dna2[i]];
            }
            
            if (!updated) break;
        }
        
        print:
        if (cases++ > 0) cout << '\n';
        if (yes)
        {
            cout << "YES\n";
            for (auto m : mutation) cout << m.first << ' ' << m.second << '\n';
        }
        else cout << "NO\n";
    }
    
    return 0;
}
