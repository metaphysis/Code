// Moliu Fractions
// UVa ID: 11148
// Verdict: Accepted
// Submission Date: 2017-07-26
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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

pair<int, int> getFraction(string f)
{
    int a = 0, b = 0, c = 1;
    
    int dash = f.find('-');
    if (dash != f.npos)
    {
        a = stoi(f.substr(0, dash));
        f = f.substr(dash + 1);
    }
    
    int slash = f.find('/');
    if (slash != f.npos)
    {
        b = stoi(f.substr(0, slash));
        c = stoi(f.substr(slash + 1));
    }
    else a = stoi(f);
    
    return make_pair(a * c + b, c);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    regex expression(R"(\d+\-\d+\/\d+|\d+\/\d+|\d+)");

    string line;
    while (getline(cin, line))
    {
        int cases = stoi(line);
        
        for (int c = 1; c <= cases; c++)
        {
            getline(cin, line);

            regex_iterator<string::iterator> it(line.begin(), line.end(), expression);
            regex_iterator<string::iterator> end;
            
            vector<int> numerator, denominator;
            while (it != end)
            {
                pair<int, int> f = getFraction(it->str());
                numerator.push_back(f.first);
                denominator.push_back(f.second);
                it++;
            }
            
            for (int i = 0; i < numerator.size(); i++)
                for (int j = 0; j < denominator.size(); j++)
                {
                    int g = gcd(numerator[i], denominator[j]);
                    numerator[i] /= g, denominator[j] /= g;
                }
            
            int fa = 1, fb = 1;
            for (int i = 0; i < numerator.size(); i++)
                fa *= numerator[i], fb *= denominator[i];
            
            int r = fa / fb;
            
            if (r > 0 || fa == 0)
            {
                cout << r;
                fa %= fb;
            }
            
            if (fa > 0)
            {
                if (r > 0) cout << '-';
                cout << fa << "/" << fb;
            }
            
            cout << '\n';
        }
    }

    return 0;
}
