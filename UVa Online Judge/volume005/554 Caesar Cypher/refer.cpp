// Caesar Cypher
// UVa ID: 554
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    
    istringstream out(plain);
    string token;
    int col = 0;
    int first = 0;
    while(out >> token) {
        if(col + token.length() >= 60)
            cout << '\n', col = 0, first = 0;
        if(first)   cout << ' ';
        first = 1;
        col += first + token.length();
        cout << token;
    }
    //cout << '\n';

    return 0;
}
