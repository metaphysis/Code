// Luggage
// UVa ID: 10664
// Verdict: Accepted
// Submission Date: 2017-11-06
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);
    
    int sum[320], weight[30];

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        istringstream iss(line);
        
        int cnt = 0, total = 0;
        
        while (iss >> weight[cnt])
        {
            total += weight[cnt];
            cnt++;
        }
        
        if ((total % 2) == 1) 
        {
            cout << "NO\n";
            continue;
        }
        
        memset(sum, 0, sizeof(sum));
        sum[0] = 1;
        
        for (int i = 0; i < cnt; i++)
            for (int j = 200; j >= 0; j--)
                if (sum[j])
                    sum[j + weight[i]] = 1;
                
        if (sum[total / 2]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
