// Decode
// UVa ID: 726
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct frequency
{
    char letter;
    int cnt;
    frequency (char letter = 0, int cnt = 0): letter(letter), cnt(cnt) {}
    bool operator<(const frequency &f) const
    {
        if (cnt != f.cnt) return cnt > f.cnt;
        return letter < f.letter;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    map<char, int> known, unknown;

    while (getline(cin, line), line.length() > 0)
    {
        for (auto c : line)
            if (isalpha(c))
                known[tolower(c)]++;
    }
    
    string message;
    while (getline(cin, line))
    {
        message += line;
        message += '\n';
        for (auto c : line)
            if (isalpha(c))
                unknown[tolower(c)]++;
    }

    vector<frequency> f1, f2;
    for (auto p : known) f1.push_back(frequency(p.first, p.second));
    for (auto p : unknown) f2.push_back(frequency(p.first, p.second));
    sort(f1.begin(), f1.end());
    sort(f2.begin(), f2.end());

    map<char, char> mapping;
    for (int i = 0; i < f1.size(); i++)
        mapping[f2[i].letter] = f1[i].letter;
        
    for (auto c : message)
        if (isalpha(c))
        {
            char mapped = mapping[tolower(c)];
            if (isupper(c)) mapped = toupper(mapped);
            cout << mapped;
        }
        else
            cout << c;

    return 0;
}
