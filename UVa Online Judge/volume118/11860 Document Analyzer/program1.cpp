// Document Analyzer
// UVa ID: 11860
// Verdict: Accepted
// Submission Date: 2018-01-15
// UVa Run Time: 0.550s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    
    for (int c = 1; c <= cases; c++)
    {
        map<int, string> cache;
        pair<int, string> pr;
        map<string, int> interval;
        int p, q, difference, total = 0, cnt = 0;

        while (getline(cin, line), line != "END")
        {
            line += '\n';            
            for (int i = 0; i < line.length(); i++)
                if (isalpha(line[i]))
                {
                    string token;
                    while (isalpha(line[i])) token += line[i++];
                    
                    cache[cnt] = token;
                    interval[token]++;

                    if (interval.size() <= total)
                    {
                        while (interval[(pr = *cache.begin()).second] > 1)
                        {
                            interval[(pr = *cache.begin()).second]--;
                            cache.erase(cache.begin());
                        }
                    }
                    
                    pr = *cache.begin();
                    if (interval.size() > total || cnt - pr.first < difference)
                    {
                        q = cnt, p = pr.first;
                        difference = q - p;
                        total = interval.size();
                    }

                    cnt++;
                }
        }

        cout << "Document " << c << ": " << (p + 1) << ' ' << (q + 1) << '\n';
    }

    return 0;
}
