// Blackboard Bonanza
// UVa ID: 11548
// Verdict: Accepted
// Submission Date: 2017-11-09
// UVa Run Time: 0.220s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getMax(string &a, string &b)
{
    int most = 0;
    
    for (int i = 1; i < b.length(); i++)
    {
        int matched = 0;
        for (int j = 0; j < i; j++)
            if (a[j] == b[b.length() - i + j])
                matched++;
        most = max(most, matched);
    }
    
    for (int i = 0; i <= (a.length() - b.length()); i++)
    {
        int matched = 0;
        for (int j = 0; j < b.length(); j++)
            if (a[i + j] == b[j])
                matched++;
        most = max(most, matched);
    }
    
    for (int i = b.length() - 1; i >= 1; i--)
    {
        int matched = 0;
        for (int j = 0; j < i; j++)
            if (a[a.length() - i + j] == b[j])
                matched++;
        most = max(most, matched);
    }
    
    return most;
}

bool cmp(string a, string b)
{
    return a.length() > b.length();
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    vector<string> words;
    string word;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        words.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.push_back(word);
        }

        sort(words.begin(), words.end(), cmp);

        int most = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                if (most >= words[j].length()) continue;
                most = max(most, getMax(words[i], words[j]));
            }
                
        cout << most << '\n';
    }

    return 0;
}
