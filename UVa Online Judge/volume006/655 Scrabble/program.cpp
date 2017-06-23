// Scrabble
// UVa ID: 655
// Verdict: Accepted
// Submission Date: 2017-06-23
// UVa Run Time: 0.380s
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

int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int board[15][15] = {
    {5, 1, 1, 2, 1, 1, 1, 5, 1, 1, 1, 2, 1, 1, 5},
    {1, 4, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 4, 1},
    {1, 1, 4, 1, 1, 1, 2, 1, 2, 1, 1, 1, 4, 1, 1},
    {2, 1, 1, 4, 1, 1, 1, 2, 1, 1, 1, 4, 1, 1, 2},
    {1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1},
    {1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1},
    {1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1},
    {5, 1, 1, 2, 1, 1, 1, 4, 1, 1, 1, 2, 1, 1, 5},
    {1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1},
    {1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1},
    {1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1},
    {2, 1, 1, 4, 1, 1, 1, 2, 1, 1, 1, 4, 1, 1, 2},
    {1, 1, 4, 1, 1, 1, 2, 1, 2, 1, 1, 1, 4, 1, 1},
    {1, 4, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 4, 1},
    {5, 1, 1, 2, 1, 1, 1, 5, 1, 1, 1, 2, 1, 1, 5}
};

bool contains(string &word, string &candidates)
{
    string nextWord(word);
    for (int k = 0; k < candidates.length(); k++)
    {
        int idx = nextWord.find(candidates[k]);
        if (idx == nextWord.npos)
           return false;
        else
           nextWord[idx] = '1';
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    vector<string> puzzles, dictionary;

    while (cin >> line, line.length() > 8) puzzles.push_back(line);
    dictionary.push_back(line);
    while (cin >> line) dictionary.push_back(line);

    string candidates, previous;
    int head;

    for (auto entry : puzzles)
    {
        for (int i = 0; i < entry.length(); i++)
            if (isdigit(entry[i]))
            {
                candidates = entry.substr(0, i);
                previous = entry.substr(i + 1);
                head = entry[i] - '0';
                break;
            }

        string bestWord, nextWord;
        int bestScores = 0, bestI, bestJ;

        int column = 8 - head;
        for (int i = 0; i < previous.length(); i++)
        {
            for (auto word : dictionary)
            {
                // Check whether word can be formed or not by using candidates
                // letters plus a letter used by opponent.
                nextWord.assign(candidates), nextWord.push_back(previous[i]);
                if (!contains(nextWord, word)) continue;
                
                for (int j = 0; j < word.length(); j++)
                    if (word[j] == previous[i])
                    {
                        int tempScores = 0, times = 1;
                        int row = 7 - j;
                        for (int k = 0; k < word.length(); k++)
                        {
                            int feature = board[row + k][column + i];
                            int score = scores[word[k] - 'A'];

                            // Feature used by opponent can not be used again.
                            if (feature <= 3)
                            {
                                // Double or triple letter position.
                                if (k != j) score *= feature;
                            }
                            else
                            {
                                if (k != j) times *= (feature - 2);
                            }

                            tempScores += score;
                        }

                        // Double word or triple word.
                        tempScores *= times;

                        // Check bonus point.
                        nextWord.assign(word), nextWord[j] = '1';
                        if (contains(nextWord, candidates)) tempScores += 50;
                        
                        if (tempScores > bestScores)
                        {
                            bestScores = tempScores;
                            bestWord = word;
                            bestI = i + 1;
                            bestJ = j + 1;
                        }
                    }
            }
        }
        
        cout << setw(8) << left << bestWord;
        cout << setw(2) << right << bestI;
        cout << setw(2) << right << bestJ;
        cout << setw(4) << right << bestScores << '\n';
    }
    
    return 0;
}
