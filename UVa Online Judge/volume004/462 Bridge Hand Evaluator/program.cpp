// Bridge Hand Evaluator
// UVa ID: 462
// Verdict: Accepted
// Submission Date: 2016-07-23
// UVa Run Time: 0.030s
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

    map<char, int> suits = {{'S', 0}, {'H', 1}, {'D', 2}, {'C', 3}};
    map<char, int> point = {{'A', 4}, {'K', 3}, {'Q', 2}, {'J', 1}};
    map<char, int> faces = {{'A', 0}, {'K', 1}, {'Q', 2}, {'J', 3}};

    string line, card;
    while (getline(cin, line))
    {
        istringstream iss(line);
        int countOfSuits[4] = {}, countOfFaces[4][4] = {};

        // rule 1
        int points = 0;
        while (iss >> card)
        {
            if (point.find(card.front()) != point.end())
            {
                points += point[card.front()];
                countOfFaces[suits[card.back()]][faces[card.front()]]++;
            }
            countOfSuits[suits[card.back()]]++;
        }

        // rule 2, 3, 4
        for (int i = 0; i < 4; i++)
        {
            if (countOfFaces[i][1] > 0 && countOfFaces[i][1] == countOfSuits[i])
                points -= countOfFaces[i][1];
            if (countOfFaces[i][2] > 0 && countOfFaces[i][2] >= countOfSuits[i] - 1)
                points -= countOfFaces[i][2];
            if (countOfFaces[i][3] > 0 && countOfFaces[i][3] >= countOfSuits[i] - 2)
                points -= countOfFaces[i][3];
        }

        // no trump
        bool all_stopped = true;
        for (int i = 0; i < 4; i++)
            all_stopped = all_stopped && (countOfFaces[i][0] >= 1 ||
            (countOfFaces[i][1] >= 1 && countOfFaces[i][1] <= countOfSuits[i] - 1) ||
            (countOfFaces[i][2] >= 1 && countOfFaces[i][2] <= countOfSuits[i] - 2));

        if (all_stopped && points >= 16)
        {
            cout << "BID NO-TRUMP\n";
            continue;
        }

        // rule 5, 6, 7
        for (int i = 0; i < 4; i++)
            if (countOfSuits[i] == 2) points += 1;
            else if (countOfSuits[i] <= 1) points += 2;

        if (points < 14)
        {
            cout << "PASS\n";
            continue;
        }

        // bid some suit
        int max_length = *max_element(countOfSuits, countOfSuits + 4);
        if (countOfSuits[0] == max_length) cout << "BID S\n";
        else if (countOfSuits[1] == max_length) cout << "BID H\n";
        else if (countOfSuits[2] == max_length) cout << "BID D\n";
        else cout << "BID C\n";
    }
    
	return 0;
}
