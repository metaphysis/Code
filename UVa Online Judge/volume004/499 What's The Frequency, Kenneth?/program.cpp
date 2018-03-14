// What's The Frequency, Kenneth?
// UVa ID: 499
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        vector<int> counter(52);
        fill(counter.begin(), counter.end(), 0);
        for (int i = 0; i < line.length(); i++)
            if (islower(line[i]))
                counter[line[i] - 'a' + 26]++;
            else if (isupper(line[i]))
                counter[line[i] - 'A']++;
        int max_frequency = *max_element(counter.begin(), counter.end());
        for (int i = 0; i < counter.size(); i++)
            if (counter[i] == max_frequency)
                cout << (char)((i < 26 ? 'A' : 'a') + (i < 26 ? i : (i - 26)));
        cout << " " << max_frequency << endl;
    }
    
	return 0;
}
