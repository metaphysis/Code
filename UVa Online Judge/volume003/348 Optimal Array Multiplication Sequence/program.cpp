// Optimal Array Multiplication Sequence
// UVa ID: 348
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 1.140s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

string answer;
int record = -1;

void backtrack(list<pair<int, int>> arrays, list<string> sequences, int times)
{
    if (record > 0 && times > record)
        return;

    if (arrays.size() == 1)
    {
        if (record == -1 || times < record)
        {
            record = times;
            answer = sequences.front();
        }

        return;
    }

    auto a = begin(arrays);
    auto b = begin(sequences);
    
    for (; a != --end(arrays) && b != --end(sequences); a++, b++)
    {
        auto nextA = a;
        advance(nextA, 1);

        int added = (*a).first * (*a).second * (*nextA).second;

        list<pair<int, int>> nextArrays;
        for (auto i = begin(arrays); i != a; i++)
            nextArrays.push_back(*i);

        nextArrays.push_back(make_pair((*a).first, (*nextA).second));

        advance(nextA, 1);
        for (auto i = nextA; i != end(arrays); i++)
            nextArrays.push_back(*i);

        list<string> nextSequences;
        auto nextB = b;
        advance(nextB, 1);
        for (auto i = begin(sequences); i != b; i++)
            nextSequences.push_back(*i);

        nextSequences.push_back("(" + (*b) + " x " + (*nextB) + ")");

        advance(nextB, 1);
        for (auto i = nextB; i != end(sequences); i++)
            nextSequences.push_back(*i);
            
        backtrack(nextArrays, nextSequences, times + added);
    }
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        list<pair<int, int>> arrays;
        for (int i = 1; i <= n; i++)
        {
            int row, column;
            cin >> row >> column;
            arrays.push_back(make_pair(row, column));
        }

        list<string> sequences;
        for (int i = 1; i <= n; i++)
            sequences.push_back("A" + to_string(i));

        record = -1;
        backtrack(arrays, sequences, 0);

        cout << "Case " << ++cases << ": " << answer << endl;
    }

	return 0;
}
