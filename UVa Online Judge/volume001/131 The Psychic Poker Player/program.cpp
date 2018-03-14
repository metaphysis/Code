// The Psychic Poker Player
// UVa ID: 131
// Verdict: Accepted
// Submission Date: 2015-12-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NOTHING = 8, ONE_PAIR = 7, TWO_PAIR = 6, THREE_KIND = 5, STRAIGHT = 4,
    FLUSH = 3, FULL_HOUSE = 2, FOUR_KIND = 1, STRAIGHT_FLUSH = 0;
    
int findBestHand(vector<string>& cards)
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
   
    // straight flush, AC 2C 3C 4C 5C, TC JC QC KC AC are straight flush
    bool is_straight = false;
    string straight = "A23456789TJQKA";
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

int minCardIndex;
bool fetched[5];
vector<string> cardInHand, cardInDeck;

void backtrack(int start, int target)
{
    if (start == target)
    {
        vector<string> cards;
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
