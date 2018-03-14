// Document Analyzer
// UVa ID: 11860
// Verdict: Accepted
// Submission Date: 2018-01-15
// UVa Run Time: 0.160s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    for (int c = 1; c <= cases; c++)
    {
        queue<pair<int, string>> cache;
        unordered_map<string, int> interval;
        int p, q, difference, total = 0, cnt = 0;

        while (getline(cin, line), line != "END")
        {
            line += '\n';            
            for (int i = 0; i < line.length(); i++)
                if (isalpha(line[i]))
                {
                    string token;
                    while (isalpha(line[i])) token += line[i++];
                    
                    cache.push(make_pair(cnt, token));
                    interval[token]++;

                    if (interval.size() <= total)
                    {
                        while (interval[cache.front().second] > 1)
                        {
                            interval[cache.front().second]--;
                            cache.pop();
                        }
                    }

                    if (interval.size() > total || cnt - cache.front().first < difference)
                    {
                        q = cnt, p = cache.front().first;
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
