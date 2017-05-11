// Simply proportion
// UVa ID: 553
// Verdict: Accepted
// Submission Date: 2017-05-11
// UVa Run Time: 0.020s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<char, int> widths{{'A', 18}, {'B', 17}, {'I', 10}, {'M', 20}, {'S', 16}, {'Y', 13}};
    int N;
    string line;
    
    while (true)
    {
        getline(cin, line);
        N = stoi(line);
        if (N == 0) break;
        
        getline(cin, line);
        
        int widthOfLetters = 0, gapsOfWord = 0, gapsOfLetter = 0;
        vector<string> words;
        
        string word;
        istringstream iss(line);
        while (iss >> word)
        {
            for (auto c : word) widthOfLetters += widths[c];
            gapsOfLetter += word.length() - 1;
            words.push_back(word);
        }
        
        gapsOfWord = words.size() - 1;
        
        int dotBetweenLetter = 3, dotBetweenWord = 10, backup = dotBetweenLetter;
        
        while (true)
        {
            dotBetweenWord = (N - widthOfLetters - gapsOfLetter * dotBetweenLetter) / gapsOfWord;
            if (dotBetweenWord < 10 || dotBetweenWord < 3 * dotBetweenLetter)
                break;
            backup = dotBetweenLetter;
            dotBetweenLetter++;
        }
        
        dotBetweenLetter = backup;
        dotBetweenWord = (N - widthOfLetters - gapsOfLetter * dotBetweenLetter) / gapsOfWord;
        int remainDot = N - widthOfLetters - gapsOfLetter * dotBetweenLetter - gapsOfWord * dotBetweenWord;
        int beginAddDot = gapsOfWord - remainDot;
        
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].length(); j++)
            {
                cout << words[i][j];
                if (j < words[i].length() - 1)
                {
                    cout << '/';
                    cout << '(' << dotBetweenLetter << ')';
                }
            }
            
            if (i < words.size() - 1)
            {
                cout << '/';
                cout << '(';
                if (remainDot > 0 && i >= beginAddDot)
                    cout << (dotBetweenWord + 1);
                else
                    cout << dotBetweenWord;
                cout << ')';
            }
        }
        
        cout << '\n';
    }
    
    return 0;
}
