// The Psychic Poker Player
// UVa IDs: 131
// Verdict: Accepted
// Submission Date: 2015-12-11
// UVa Run Time: 0.059s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int findIndex(char a)
{
    string value = "0123456789TJQKA";
    for (int i = 0; i < value.length(); i++)
        if (a == value[i])
            return i;
    return 0;
}

bool cmp(string a, string b)
{
    return (a[0] == b[0]) ? (a[1] < b[1]) : (findIndex(a[0]) < findIndex(b[0]));
}

// 注意 AC 2C 3C 4C 5C 和 TC JC QC KC AC 都是同花顺。
bool isStraightFlush(vector < string > cards)
{
    sort(cards.begin(), cards.begin() + cards.size(), cmp);
    
    bool result = true;
    for (int i = 0; i < cards.size() - 1; i++)
        if (cards[i + 1][1] != cards[i][1] ||
            findIndex(cards[i + 1][0]) != (findIndex(cards[i][0]) + 1))
        {
            result = false;
            break;
        }
    
    if (result == false && cards[4][0] == 'A')
    {
        vector < string > newCards(cards);
        newCards[4][0] = '1';
        return isStraightFlush(newCards);
    }
    
    return result;
}

bool isSameKind(vector < string > cards, int number, int index)
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

bool isFourKind(vector < string > cards)
{
    return isSameKind(cards, 4, 0);
}

bool isOnePair(vector < string > cards)
{
    for (int i = 0; i < cards.size(); i++)
        for (int j = i + 1; j < cards.size(); j++)
            if (cards[i][0] == cards[j][0])
                return true;
    return false;
}

bool isFullHouse(vector < string > cards)
{
    for (int i = 0; i < cards.size(); i++)
        for (int j = i + 1; j < cards.size(); j++)
            if (cards[i][0] == cards[j][0])
            {
                cards.erase(cards.begin() + j);
                cards.erase(cards.begin() + i);
                return isSameKind(cards, 3, 0);
            }
    return false;
}

bool isFlush(vector < string > cards)
{
    return isSameKind(cards, 5, 1);
}

bool isStraight(vector < string > cards)
{
    for (int i = 0; i < cards.size(); i++)
        cards[i][1] = 'C';
    return isStraightFlush(cards);
}

bool isThreeKind(vector < string > cards)
{
    return isSameKind(cards, 3, 0);
}

bool isTwoPair(vector < string > cards)
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

int findBestHand(vector < string > cards)
{
    bool(*isSomeHand[8]) (vector < string >) = {
        isStraightFlush, isFourKind, isFullHouse,
        isFlush, isStraight, isThreeKind, isTwoPair, isOnePair
    };

    for (int i = 0; i <= 7; i++)
        if (isSomeHand[i] (cards))
            return i;
    return 8;
}

int minCardIndex;
bool fetched[5];
vector < string > cardInHand, cardInDeck;

void backtrack(int start, int target)
{
    if (start == target)
    {
        vector < string > cards;
        for (int i = 0; i < 5; i++)
            if (fetched[i])
                cards.push_back(cardInHand[i]);
        for (int j = 0; j < (5 - target); j++)
            cards.push_back(cardInDeck[j]);
        minCardIndex = min(minCardIndex, findBestHand(cards));
    }
    else
    {
        for (int i = 0; i < 5; i++)
            if (fetched[i] == false)
            {
                fetched[i] = true;
                backtrack(start + 1, target);
                fetched[i] = false;
            }
    }
}

int main(int argc, char *argv[])
{
    string line;
    string result[9] = {
        "straight-flush", "four-of-a-kind", "full-house", "flush", "straight",
        "three-of-a-kind", "two-pairs", "one-pair", "highest-card"
    };

    while (getline(cin, line), line.length() > 0)
    {
        
        cardInHand.clear();
        cardInDeck.clear();
        
        string card;
        istringstream iss(line);
        while (iss >> card && cardInHand.size() < 5)
            cardInHand.push_back(card);
        
        cardInDeck.push_back(card);
        while (iss >> card)
            cardInDeck.push_back(card);
            
        minCardIndex = 8;
        for (int i = 0; i <= 5; i++)
        {
            memset(fetched, 0, sizeof(fetched));
            backtrack(0, i);
        }
        
        line = "Hand: " + line.insert(15, "Deck: ") + " Best hand: ";
        line = line + result[minCardIndex];
        cout << line << endl;
    }

    return 0;
}
