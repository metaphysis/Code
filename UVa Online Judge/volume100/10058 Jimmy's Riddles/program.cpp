// Jimmy's Riddles
// UVa ID: 10058
// Verdict: Accepted
// Submission Date: 2017-12-27
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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int NONE = -1, COMMA = 0, AND = 1, VERB = 2, NOUN = 3, ARTICLE = 4, ACTOR = 5,
    ACTIVE_LIST = 6, ACTION = 7, STATEMENT = 8;

vector<int> S; vector<string> W;

int T[7][4] = {
    {ARTICLE, NONE, NOUN, ACTOR}, {NOUN, NONE, NONE, ACTOR},
    {ACTOR, NONE, NONE, ACTIVE_LIST}, {AND, ACTIVE_LIST, ACTIVE_LIST, ACTIVE_LIST},
    {VERB, ACTIVE_LIST, ACTIVE_LIST, ACTION},
    {ACTION, NONE, NONE, STATEMENT}, {COMMA, STATEMENT, STATEMENT, STATEMENT}, 
};

int getSymbol(string word)
{
    if (word == ",") return COMMA;
    if (word == "and") return AND;
    if (word == "hate" || word == "hates" || word == "love" || word == "loves" ||
        word == "know" || word == "knows" || word == "like" || word == "likes")
        return VERB;
    if (word == "tom" || word == "jerry" || word == "goofy" || word == "mickey" ||
        word == "jimmy" || word == "dog" || word == "cat" || word == "mouse")
        return NOUN;
    if (word == "a" || word == "the")
        return ARTICLE;
    return NONE;
}

bool parse()
{
    S.clear();
    for (int i = 0; i < W.size(); i++)
    {
        int symbol = getSymbol(W[i]);
        if (symbol == NONE) return false;
        else S.push_back(symbol);
    }
    return true;
}

bool good()
{
    if (!parse()) return false;

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < S.size();)
        {
            if ((S[j] != T[i][0]) ||
                (~T[i][1] && (!j || S[j - 1] != T[i][1])) ||
                (~T[i][2] && (j == (S.size() - 1) || S[j + 1] != T[i][2])))
            {
                j++;
                continue;
            }
            j = ~T[i][1] ? S.erase(S.begin() + j - 1) - S.begin() : j;
            j = ~T[i][2] ? S.erase(S.begin() + j + 1) - S.begin() - 1 : j;
            S[j] = T[i][3];
        }

    return (S.size() == 1 && S[0] == STATEMENT);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, word;
    while (getline(cin, line))
    {
        string block;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',') block += " , ";
            else block += line[i];
        }
        istringstream iss(block);
        while (iss >> word) W.push_back(word);
        cout << (good()? "YES I WILL" : "NO I WON'T") << '\n';
        W.clear();
    }
    return 0;
}
