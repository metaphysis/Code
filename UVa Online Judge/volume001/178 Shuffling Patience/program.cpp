// Shuffling Patience
// UVa ID: 178
// Verdict: Accepted
// Submission Date: 2016-02-22
// UVa Run Time: 0.012s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct card
{
    string face;
    int value;
};

struct topCard
{
    int value, index;
};

bool operator <(topCard x, topCard y)
{
    return x.value < y.value;
}

string cardValue = "A23456789TJQK";
vector<card> cards;
vector<topCard> top;
vector<vector<card>> piles(16);
int twoPair[2], threePair[3];
int testcase = 0;

void display()
{
    for (int i = 0; i < piles.size(); i++)
    {
        if (piles[i].size() > 0)
            cout << piles[i].back().face;
        else
            cout << "0";
            
        cout << " ";
        
        if ((i + 1) % 4 == 0)
            cout << endl;
    }
}

void getTop()
{
    top.clear();
    for (int i = 0; i < piles.size(); i++)
        if (piles[i].size() > 0)
            top.push_back((topCard){piles[i].back().value, i});
}

bool findTwoPair()
{
    if (top.size() <= 1)
        return false;
        
    for (int i = 0; i < top.size() - 1; i++)
    {
        if (top[i].value >= 1 && top[i].value <= 10)
        {
            for (int j = i + 1; j < top.size(); j++)
                if (top[j].value >= 1 && top[j].value <= 10 &&
                    (top[i].value + top[j].value) == 11)
                {
                    twoPair[0] = top[i].index;
                    twoPair[1] = top[j].index;
                    //cout << "two pair found: " << twoPair[0] << " " << twoPair[1] << endl;
                    return true;
                }
        }
    }
            
    return false;       
}

bool findThreePair()
{
    if (top.size() <= 2)
        return false;
        
    stable_sort(top.begin(), top.end());

    //cout << "top sequence: ";
    //for (int i = 0; i < top.size(); i++)
        //cout << top[i].value << " " << top[i].index << " ";
    //cout << endl;
    
    for (int i = 0; i < 3; i++)
    {
        bool found = false;
        for (int j = 0; j < top.size(); j++)
            if (top[j].value == (i + 11))
            {
                threePair[i] = top[j].index;
                found = true;
                break;
            }
        if (found == false)
            return false;
    }
    
    sort(threePair, threePair + 3);
    
    //cout << "found: ";
    //for (int i = 0; i < 3; i++)
        //cout << threePair[i] << " ";
    //cout << endl;
    
    return true;
}

void play()
{
    for (int i = 0; i <= 15; i++)
        piles[i].clear();

    int index = 0, currentPile = 0;
    while (index < cards.size())
    {
        //display();
        
        //cout << "current card: " << cards[index].face << " " << cards[index].value << endl;

        getTop();

        bool twoPairFound = findTwoPair();
        bool threePairFound = findThreePair();
    
        
        if ((twoPairFound == true && threePairFound == false)
            || (twoPairFound == true && threePairFound == true
                && twoPair[0] < threePair[0]))
        {
            //cout << "find two pair: " << piles[twoPair[0]].back().face << " " << piles[twoPair[1]].back().face << endl;
            int number = 0;
            while (index < cards.size() && number < 2)
            {
                piles[twoPair[number++]].push_back(cards[index]);
                index++;
            }

            //display();
            
            if (number < 2)
                break;
        }
        else if ((twoPairFound == false && threePairFound == true)
            || (twoPairFound == true && threePairFound == true
                && twoPair[0] > threePair[0]))
        {
            //cout << "find three pair: " << piles[threePair[0]].back().face << " " << piles[threePair[1]].back().face << " " << piles[threePair[2]].back().face << endl;
            int number = 0;
            while (index < cards.size() && number < 3)
            {
                piles[threePair[number++]].push_back(cards[index]);
                index++;
            }

            //display();
            
            if (number < 3)
                break;
        }
        else
        {
            if (currentPile >= 16)
                break;

            piles[currentPile++].push_back(cards[index]);
            index++;
            
            //cout << "not found pair!" << endl;
            //display();
        }
    }

    cout << setw(3) << right << testcase << ":";
    if (index == cards.size())
    {
        for (int i = 0; i < piles.size(); i++)
            if (piles[i].size() > 0)
                cout << setw(3) << right << piles[i].size();
        cout << "\n";
    }
    else
    {
        cout << " Overflowed on card no";
        cout << setw(3) << right << (index + 1) << "\n";
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string oneCard;
    int counter = 0;
    while (cin >> oneCard, oneCard != "#")
    {
        cards.push_back((card){oneCard, cardValue.find(oneCard[0]) + 1});
        counter++;

        if (counter == 52)
        {
            testcase++;
            play();
            cards.clear();
            counter = 0;
        }
    }

    return 0;
}
