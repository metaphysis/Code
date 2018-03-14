// Clock Patience
// UVa ID: 170
// Verdict: Accepted
// Submission Date: 2016-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct card
{
    string text;
    int index;
};

string cardValue = "A23456789TJQK";
vector < card > cards;
vector < vector < card > > piles;

void display()
{
    for (int i = 0; i < piles.size(); i++)
    {
        cout << "index " << i + 1 << ": ";
        for (int j = 0; j < piles[i].size(); j++)
            cout << piles[i][j].text << " ";
        cout << endl;
    }
}

void play()
{
    reverse(cards.begin(), cards.end());
    
    for (int i = 0; i <= 12; i++)
        piles[i].clear();
        
    for (int i = 0; i <= 12; i++)
        for (int j = 0; j <= 3; j++)
            piles[i].push_back(cards[j * 13 + i]);
            
    for (int i = 0; i < piles.size(); i++)
        reverse(piles[i].begin(), piles[i].end());
    
    display();
    
    int index = 13;
    int exposed = 0;
    string last;
    
    while (true)
    {
        if (piles[index - 1].size())
        {
            last = piles[index - 1][0].text;
            int temp = piles[index - 1][0].index;
            piles[index - 1].erase(piles[index - 1].begin());
            index = temp;
            exposed++;
        }
        else
            break;
    }
    
    cout << setw(2) << setfill('0') << exposed << "," << last << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    for (int i = 1; i <= 13; i++)
    {
        vector < card > pile;
        piles.push_back(pile);
    }
    
    string oneCard;
    int counter = 0;
    while (cin >> oneCard, oneCard != "#")
    {
        cards.push_back((card){oneCard, cardValue.find(oneCard[0]) + 1});
        counter++;
        
        if (counter == 52)
        {
            play();
            cards.clear();
            counter = 0;
        }
    }
    
	return 0;
}
