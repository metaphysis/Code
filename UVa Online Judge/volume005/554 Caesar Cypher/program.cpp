// Caesar Cypher
// UVa ID: 554
// Verdict: Accepted
// Submission Date: 2017-02-21
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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    set<string> dictionary;
    string word;
    
    while (cin >> word, word != "#") dictionary.insert(word);
        
    string sentence;
    cin.ignore(1024, '\n');
    getline(cin, sentence);
    
    int max_matches = 0, K = 0;
    string plain;

    for (int k = 0; k <= 26; k++)
    {
        int matches = 0;
        string original;

        for (int i = 0; i < sentence.length(); i++)
        {
            int letter = sentence[i] == ' ' ? 0 : (sentence[i] - 64);
            letter = (letter + 27 - k) % 27;

            if (letter == 0) original += ' ';
            else original += (char)(letter + 64);
        }

        istringstream in(original);
        while (in >> word)
            if (dictionary.count(word) == 1)
                matches++;

        if (matches > max_matches)
        {
            max_matches = matches;
            K = k;
            plain = original;
        }
    }

    vector<string> words;
    stringstream out(plain);
    while (out >> word) words.push_back(word);

    int i = 0, j = 0;
    while (i < words.size())
    {
        if (j > 0)
        {
            if ((j + 1 + words[i].length()) >= 60)
            {
                cout << '\n';
                j = 0;
            }
            else
            {
                cout << ' ' << words[i];
                j += (1 + words[i].length());
                i++;
            }
        }
        else
        {
            cout << words[i];
            j += words[i].length();
            i++;
        }
    }
    
    if (j > 0) cout << '\n';

    return 0;
}
