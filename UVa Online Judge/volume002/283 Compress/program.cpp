// Compress
// UVa ID: 283
// Verdict: Accepted
// Submission Date: 2016-06-03
// UVa Run Time: 0.250s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> counter, codes(10);
int minimalBits;

void backtrack(int prefix, int index, int bits)
{
    for (int i = 1; i <= 8; i++)
    {
        if (index + codes[i] >= counter.size())
        {
            int next_bits = bits;
            for (int j = index; j < counter.size(); j++)
                next_bits += counter[j] * (prefix + i);

            minimalBits = min(minimalBits, next_bits);
        }
        else
        {
            int next_index = index, next_bits = bits;
            for (int j = 1; j < codes[i]; j++)
                next_bits += counter[next_index++] * (prefix + i);

            if (next_bits < minimalBits)
                backtrack(prefix + i, next_index, next_bits);
        }
    }
}

int main(int argc, char *argv[])
{
    int cases;

    for (int i = 1; i <= 8; i++)
        codes[i] = pow(2, i);

    string line;
    getline(cin, line);
    cases = stoi(line);

    while (cases--)
    {
        int n;
        getline(cin, line);
        n = stoi(line);

        map < char, int >frequency;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);

            for (int i = 0; i < line.length(); i++)
                frequency[line[i]]++;
        }

        counter.clear();
        for (auto it = frequency.begin(); it != frequency.end(); it++)
            counter.push_back((*it).second);

        sort(counter.begin(), counter.end(), greater<int>());

        minimalBits = numeric_limits < int >::max();
        backtrack(0, 0, 0);

        cout << minimalBits << endl;
    }

    return 0;
}
