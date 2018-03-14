// Ananagrams
// UVa ID: 156
// Verdict: Accepted
// Submission Date: 2016-02-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string toLower(string line)
{
    for (int i = 0; i < line.length(); i++)
        line[i] = tolower(line[i]);
    return line;
}

int main(int argc, char *argv[])
{
    vector<string> allWords;
    multiset<string> lowerCase;

    string line;
    while (cin >> line, line != "#")
    {
        allWords.push_back(line);
        line.assign(toLower(line));
        sort(line.begin(), line.end());
        lowerCase.insert(line);
    }

    vector<string> ananagrams;
    for (int i = 0; i < allWords.size(); i++)
    {
        string word = toLower(allWords[i]);
        sort(word.begin(), word.end());
        if (lowerCase.count(word) == 1)
            ananagrams.push_back(allWords[i]);
    }

    sort(ananagrams.begin(), ananagrams.end());
    for (int i = 0; i < ananagrams.size(); i++)
        cout << ananagrams[i] << endl;

    return 0;
}
