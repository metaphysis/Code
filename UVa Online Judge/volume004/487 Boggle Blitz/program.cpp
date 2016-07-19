// Boggle Blitz
// UVa ID: 487
// Verdict: Accepted
// Submission Date: 2016-07-19
// UVa Run Time: 0.110s
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

struct state
{
    int i, j;
    string word;
};

bool cmp(string& a, string& b)
{
    if (a.length() != b.length())
        return a.length() < b.length();
    else
        return a < b;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << '\n';
        
        char table[20][20];

        int n;
        cin >> n;
        
        string line;
        for (int j = 1; j <= n; j++)
        {
            cin >> line;
            for (int k = 0; k < line.length(); k++)
                table[j -  1][k] = line[k];
        }
        
        set<string> words, tags;
        
        queue<state> unvisited;
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
            {
                state start;
                start.i = j, start.j = k;
                start.word += table[j][k];
                unvisited.push(start);
            }
            
        while (unvisited.empty() == false)
        {
            state current = unvisited.front();
            unvisited.pop();
            
            for (int offsetx = -1; offsetx <= 1; offsetx++)
                for (int offsety = -1; offsety <= 1; offsety++)
                {
                    if (offsetx == 0 && offsety == 0)
                        continue;
                        
                    int nexti = current.i + offsetx, nextj = current.j + offsety;
                    if (nexti >= 0 && nexti < n && nextj >= 0 && nextj < n && table[nexti][nextj] > current.word.back())
                    {
                        string next_word = current.word + table[nexti][nextj];
                        if (next_word.length() >= 3)
                        {
                            string tag = next_word + to_string(nexti) + to_string(nextj);
                            if (tags.find(tag) == tags.end())
                            {
                                tags.insert(tag);
                                words.insert(next_word);
                                unvisited.push((state){nexti, nextj, next_word});
                            }
                        }
                        else
                        {
                            unvisited.push((state){nexti, nextj, next_word});
                        }
                    }
                }
        }
        
        vector<string> allWords;

        for (auto word : words)
            allWords.push_back(word);
            
        sort(allWords.begin(), allWords.end(), cmp);
        for (auto word : allWords)
            cout << word << '\n';
    }
    
	return 0;
}
