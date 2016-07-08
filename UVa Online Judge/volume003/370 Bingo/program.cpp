// Bingo
// UVa IDs: 370
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.210s
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
#include <vector>

using namespace std;

vector<int> sum(13), operation(25), backup(25);
map<int, vector<int>> mapping;
map<int, vector<int>> indexer;
map<int, vector<int>> location;

void display()
{
    for (int i = 0; i < 13; i++)
    {
        if (sum[i] == 0)
        {
            if (i <= 4) cout << "BINGO #1" << endl;
            else if (i <= 9) cout << "BINGO #2" << endl;
            else if (i == 10)  cout << "BINGO #3" << endl;
            else cout << "BINGO #4" << endl;

            for (auto position : indexer[i])
            {
                cout << (position / 5 + 1) << "," << (position % 5 + 1) << ",";
                if (backup[position] == 0) cout << "FREE";
                else cout << backup[position];
                cout << endl;
            }
        }
    }
}

bool isBingo()
{
    for (auto element : sum)
        if (element == 0)
        {
            display();
            return true;
        }
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    for (int position = 0; position < 25; position++)
    {
        int i = position / 5, j = position % 5;
        mapping[position].push_back(i);
        indexer[i].push_back(position);

        mapping[position].push_back(j + 5);
        indexer[j + 5].push_back(position);

        if (i == j)
        {
            mapping[position].push_back(11);
            indexer[11].push_back(position);
        }

        if (i + j == 4)
        {
            mapping[position].push_back(12);
            indexer[12].push_back(position);
        }

        if ((i == 0 && j == 0) || (i == 0 && j == 4) ||
            (i == 4 && j == 0) || (i == 4 && j == 4))
        {
            mapping[position].push_back(10);
            indexer[10].push_back(position);
        }
    }
    
    int number, called;
    while (cin >> number)
    {
        fill(sum.begin(), sum.end(), 0);

        location.clear();
        int readedNumber = 0, row, column;
        do
        {
            operation[readedNumber] = number;
            backup[readedNumber] = operation[readedNumber];
            location[number].push_back(readedNumber);

            for (auto position : mapping[readedNumber])
                sum[position] += number;
            readedNumber++;
        } while (readedNumber < 25 && (cin >> number));

        bool ignore = isBingo();
        while (cin >> called, called)
        {
            if (ignore) continue;
            for (auto located : location[called])
            {
                operation[located] = 0;
                for (auto position : mapping[located])
                    sum[position] -= called;
            }
            ignore = isBingo();
        }

        if (!ignore) cout << "No BINGO on this card." << endl << endl;
        else cout << endl;
    }

	return 0;
}
