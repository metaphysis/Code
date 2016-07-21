// Poker Solitaire Evaluator
// UVa ID: 451
// Verdict: Accepted
// Submission Date: 2016-07-20
// UVa Run Time: 0.070s
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

const int NOTHING = 1, ONE_PAIR = 2, TWO_PAIR = 3, THREE_KIND = 4, STRAIGHT = 5,
    FLUSH = 6, FULL_HOUSE = 7, FOUR_KIND = 8, STRAIGHT_FLUSH = 9;
    
int findHand(vector<string>& cards)
{
    map<char, int> ranks;
    set<char> suits;
    vector<int> sequence;

    for (int i = 0; i < 5; i++)
    {
        ranks[cards[i].front()]++;
        suits.insert(cards[i].back());
    }
    for (auto pair : ranks) sequence.push_back(pair.second);
   
    // straight flush
    // AC 2C 3C 4C 5C, TC JC QC KC AC, JC QC KC AC 2C are straight flush
    bool is_straight = false;
    string straight = "23456789XJQKA2345";
    for (int i = 0; i <= straight.length() - 5; i++)
    {
        is_straight = true;
        for (int j = i; j <= i + 4; j++)
            if (ranks.find(straight[j]) == ranks.end())
            {
                is_straight = false;
                break;
            }
        if (is_straight) break;
    }
    bool is_flush = (suits.size() == 1);
    if (is_straight && is_flush) return STRAIGHT_FLUSH;

    // four of a kind
    bool four_kind = *max_element(sequence.begin(), sequence.end()) >= 4;
    if (four_kind) return FOUR_KIND;

    // full house
    bool is_full_house = (ranks.size() == 2 && accumulate(sequence.begin(), sequence.end(), int(0)) == 5);
    if (is_full_house) return FULL_HOUSE;

    // flush
    if (is_flush) return FLUSH;

    // straight
    if (is_straight) return STRAIGHT;

    // three of a kind
    bool three_kind = *max_element(sequence.begin(), sequence.end()) >= 3;
    if (three_kind) return THREE_KIND;

    // two pair
    bool is_two_pair = ranks.size() == 3;
    if (is_two_pair) return TWO_PAIR;

    // one pair
    bool is_one_pair = *max_element(sequence.begin(), sequence.end()) >= 2;
    if (is_one_pair) return ONE_PAIR;

    // nothing
    return NOTHING;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
        
    int cases;
    vector<int> hands(10);
    vector<vector<string>> cards(10, vector<string>(5));
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                cin >> cards[i][j];
        
        for (int i = 5, j = 0; i < 10; i++, j++)
            for (int k = 0; k < 5; k++)
                cards[i][k] = cards[k][j];
        
        fill(hands.begin(), hands.end(), 0);
        for (int i = 0; i < 10; i++)
            hands[findHand(cards[i])]++;
        
        for (int j = 1; j <= 9; j++)
        {
            if (j > 1) cout << ", ";
            cout << hands[j];
        }
        cout << '\n';
    }
    
	return 0;
}
