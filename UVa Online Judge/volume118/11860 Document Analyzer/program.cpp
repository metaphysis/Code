// Document Analyzer
// UVa ID: 11860
// Verdict: Accepted
// Submission Date: 2018-01-15
// UVa Run Time: 0.980s
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
        vector<string> words;
        set<string> allKinds;

        while (getline(cin, line), line != "END")
        {
            string token;
            for (int i = 0; i < line.length(); i++)
            {
                if (isalpha(line[i])) token += line[i];
                else
                {
                    if (token.length())
                    {
                        words.push_back(token);
                        allKinds.insert(token);
                        token.clear();
                    }
                }
            }
            if (token.length())
            {
                words.push_back(token);
                allKinds.insert(token);
            } 
        }

        int p = 0, q = 0, difference = 0, total = allKinds.size();

        vector<int> cache;
        map<string, int> interval;

        for (int i = 0; i < words.size(); i++)
        {
            cache.push_back(i);
            interval[words[i]]++;

            // Add all kinds of words to interval.
            if (interval.size() < total)
            {
                q = i + 1, p = 0;
                difference = q - p;
                continue;
            }

            // Is this word saw before?
            while (interval[words[cache.front()]] > 1)
            {
                interval[words[cache.front()]]--;
                cache.erase(cache.begin());
            }

            // Can the difference of p and q be better?
            if (i - cache.front() < difference)
            {
                q = i, p = cache.front();
                difference = q - p;
            }
        }

        cout << "Document " << c << ": " << (p + 1) << ' ' << (q + 1) << '\n';
    }

    return 0;
}
