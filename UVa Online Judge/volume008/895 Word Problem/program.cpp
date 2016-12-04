// Word Problem
// UVa ID: 895
// Verdict: Accepted
// Submission Date: 2016-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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

    int alpha[1100][26], count = 0;
    string word, puzzle;
    
    memset(alpha, 0, sizeof(alpha));
    
    while (cin >> word, word != "#")
    {
        for (int i = 0; i < word.length(); i++)
            alpha[count][word[i] - 'a']++;
        count++;
    }

    cin.ignore(1024, '\n');

    while (getline(cin, puzzle), puzzle != "#")
    {
        int alpha1[26];
        memset(alpha1, 0, sizeof(alpha1));
        for (int i = 0; i < puzzle.length(); i++)
            if (isalpha(puzzle[i]))
                alpha1[puzzle[i] - 'a']++;
            
        int t = 0;
        for (int i = 0; i < count; i++)
        {
            bool good = true;
            for (int j = 0; j < 26; j++)
                if (alpha[i][j] > alpha1[j])
                {
                    good = false;
                    break;
                }
                
            t += good;
        }
        
        cout << t << '\n';
    }
    
	return 0;
}
