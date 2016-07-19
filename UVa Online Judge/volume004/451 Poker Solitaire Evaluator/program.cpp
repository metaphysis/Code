// Poker Solitaire Evaluator
// UVa ID: 451
// Verdict: Accepted
// Submission Date: 2016-07-19
// UVa Run Time: 0.180s
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

// 注意 AC 2C 3C 4C 5C 和 TC JC QC KC AC 和 JC QC KC AC 2C 都是同花顺。
bool isStraightFlush(vector<string> cards)
{
    for (int i = 0; i < cards.size() - 1; i++)
        if (cards[i + 1][1] != cards[i][1])
            return false;
    
    string sample = "23456789XJQKA2345";
    set<char> card;
    for (int i = 0; i < cards.size(); i++)
        card.insert(cards[i][0]);
    for (int i = 0; i < sample.length() - 4; i++)
    {
        bool flag = true;
        for (int j = i; j < i + 5; j++)
            if (card.find(sample[j]) == card.end())
            {
                flag = false;
                break;
            }
        if (flag) return true;
    }
    return false;
}

bool isSameKind(vector<string> cards, int number, int index)
{
    for (int i = 0; i < cards.size(); i++)
    {
        int counter = 0;
        for (int j = 0; j < cards.size(); j++)
            if (cards[j][index] == cards[i][index])
                counter++;
        if (counter >= number)
            return true;
    }
    return false;
}

bool isFourKind(vector<string> cards)
{
    return isSameKind(cards, 4, 0);
}

bool isOnePair(vector<string> cards)
{
    for (int i = 0; i < cards.size(); i++)
        for (int j = i + 1; j < cards.size(); j++)
            if (cards[i][0] == cards[j][0])
                return true;
    return false;
}

bool isFullHouse(vector<string> cards)
{
    map<char, int> card;
    for (int i = 0; i < cards.size(); i++)
        card[cards[i][0]]++;
    int sum = 0;
    for (auto counter : card)
        sum += counter.second;
    return card.size() == 2 && sum == 5;
}

bool isFlush(vector<string> cards)
{
    return isSameKind(cards, 5, 1);
}

bool isStraight(vector<string> cards)
{
    for (int i = 0; i < cards.size(); i++)
        cards[i][1] = 'C';
    return isStraightFlush(cards);
}

bool isThreeKind(vector<string> cards)
{
    return isSameKind(cards, 3, 0);
}

bool isTwoPair(vector<string> cards)
{
    for (int i = 0; i < cards.size(); i++)
        for (int j = i + 1; j < cards.size(); j++)
            if (cards[i][0] == cards[j][0])
            {
                cards.erase(cards.begin() + j);
                cards.erase(cards.begin() + i);
                return isOnePair(cards);
            }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    bool(*isSomeHand[8]) (vector<string>) = {
        isStraightFlush, isFourKind, isFullHouse,
        isFlush, isStraight, isThreeKind, isTwoPair, isOnePair
    };
        
    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        vector<vector<string>> cards(11);
        string card;
        for (int i = 1; i <= 5; i++)
            for (int j = 1; j <= 5; j++)
            {
                cin >> card;
                cards[i].push_back(card);
            }
        
        for (int i = 6, j = 0; i <= 10; i++, j++)
            for (int k = 1; k <= 5; k++)
                cards[i].push_back(cards[k][j]);
        
        vector<int> hands(9);
        fill(hands.begin(), hands.end(), 0);
        
        for (int i = 1; i <= 10; i++)
        {
            bool handFound = false;
            for (int j = 0; j < 8; j++)
                if (isSomeHand[j](cards[i]))
                {
                    handFound = true;
                    hands[8 - j]++;
                    break;
                }
                
            if (handFound == false)
                hands[0]++;
        }
        
        for (int j = 0; j < 9; j++)
        {
            if (j > 0) cout << ", ";
            cout << hands[j];
        }
        cout << '\n';
    }
    
	return 0;
}
