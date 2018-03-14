// Poker Hands （扑克牌型）
// PC/UVa IDs: 110202/10315, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2016-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int HIGH_CARD = 0, ONE_PAIR = 1, TWO_PAIR = 2, THREE_KIND = 3, STRAIGHT = 4,
    FLUSH = 5, FULL_HOUSE = 6, FOUR_KIND = 7, STRAIGHT_FLUSH = 8;
    
const int TIE = 0, BLACK_WIN = 1, WHITE_WIN = 2;

map<char, int> valueTable = {
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8},
    {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
};

bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    if (a.second != b.second)
        return a.second > b.second;
    else
        return a.first > b.first;
}

// 若牌型相同，按关键牌比较大小。
long long getScore(vector<string>& cards, int card_type)
{
    vector<int> sequences;
    
    if (card_type == ONE_PAIR || card_type == TWO_PAIR ||
        card_type == THREE_KIND || card_type == FOUR_KIND ||
        card_type == FULL_HOUSE)
    {
        map<int, int> counter;
        for (int i = 0; i < 5; i++)
            counter[valueTable[cards[i].front()]]++;
            
        vector<pair<int, int>> counter_next;
        for (auto pair : counter) counter_next.push_back(pair);
        sort(counter_next.begin(), counter_next.end(), cmp);
        
        for (auto pair : counter_next)
        {
            for (int i = 1; i <= pair.second; i++)
                sequences.push_back(pair.first);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
            sequences.push_back(valueTable[cards[i].front()]);
        sort(sequences.begin(), sequences.end(), greater<int>());
    }
    
    long long score = 0;
    for (int i = 0; i < 5; i++)
        score = score * 16 + sequences[i];
    return score * pow(16, card_type);
    
    return score;
}

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
   
    // straight flush, AC 2C 3C 4C 5C is not straight, TC JC QC KC AC is straight flush
    bool is_straight = false;
    string straight = "23456789TJQKA";
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
    return HIGH_CARD;
}

// 比较两手牌的大小，直接比较其牌面值的大小即可。
int compareCard(vector<string>& black, vector<string>& white)
{
    long long black_value = getScore(black, findBestHand(black));
    long long white_value = getScore(white, findBestHand(white));
    if (black_value == white_value) return TIE;
    else if (black_value > white_value) return BLACK_WIN;
    else return WHITE_WIN;
}

int main(int argc, char *argv[])
{
    vector<string> black(5), white(5), info{ "Tie.", "Black wins.", "White wins." };

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        for (int i = 0; i < 5; i++)
            iss >> black[i];
        for (int i = 0; i < 5; i++)
            iss >> white[i];

        cout << info[compareCard(black, white)] << endl;
    }

    return 0;
}
