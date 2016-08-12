// Bridge Hands
// UVa ID: 555
// Verdict: Accepted
// Submission Date: 2016-08-12
// UVa Run Time: 0.040s
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

map<char, int> suits = {{'C', 0}, {'D', 1}, {'S', 2}, {'H', 3}};
map<char, int> ranks = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4},
    {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
    {'Q', 10}, {'K', 11}, {'A', 12}
};
map<int, char> dealers = {{0, 'S'}, {1, 'W'}, {2, 'N'}, {3, 'E'}};
map<char, int> offset = {{'S', 3}, {'W', 2}, {'N', 1}, {'E', 0}};

string suit_text = "CDSH", rank_text = "23456789TJQKA";

struct card
{
    int suit, rank;
    
    bool operator<(const card& another) const
    {
        if (suit != another.suit)
            return suit < another.suit;
        else
            return rank < another.rank;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char dealer, suit, rank;
    while (cin >> dealer, dealer != '#')
    {
        vector<vector<card>> cards(4, vector<card>(13));
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 4; j++)
            {
                cin >> suit >> rank;
                cards[j][i].suit = suits[suit];
                cards[j][i].rank = ranks[rank];
            }
                
        for (int i = 0; i < 4; i++)
            sort(cards[i].begin(), cards[i].end());
            
        for (auto d : dealers)
        {
            cout << d.second << ':';
            for (auto c : cards[(offset[dealer] + d.first) % 4])
                cout << ' ' << suit_text[c.suit] << rank_text[c.rank];
            cout << '\n';
        }
    }
    
	return 0;
}
