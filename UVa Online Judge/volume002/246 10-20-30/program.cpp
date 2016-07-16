// 10-20-30
// UVa ID: 246
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <set>

using namespace std;

string deck;
vector < string > piles;
set < string > appeared;

void display(int times)
{
    cout << "TIMES:" << times << endl;
    cout << "DECK:";
    for (int i = 0; i < deck.size(); i++)
        cout << " " << deck[i];
    cout << endl;
    
    for (int i = 0; i < piles.size(); i++)
    {
        cout << (i + 1) << ":";
        for (int j = 0; j < piles[i].size(); j++)
            cout << " " << piles[i][j];
        cout << endl;
    }
    cout << endl;
    
}

string cards = "ABCDEFGHIJK";

int main(int argc, char *argv[])
{
    int card;
    while (cin >> card, card)
    {
        appeared.clear();
        deck.clear();
        piles.clear();
        piles.resize(7);
        
        deck.push_back(cards[card]);
        for (int i = 1; i <= 51; i++)
        {
            cin >> card;
            deck.push_back(cards[card]);
        }
        
        int currentPile = 0, times = 0;
        bool draw = false;
        while (deck.size())
        {
            string tag = deck;
            tag += '*';
            for (int i = 0; i < piles.size(); i++)
            {
                tag += piles[i];
                tag += '#';
            }
            tag += '$';
            tag += to_string(currentPile);
            
            //cout << tag << endl;
            
            if (appeared.count(tag) > 0)
            {
                draw = true;
                break;
            }
            else
                appeared.insert(tag);
                
            card = deck.front();
            
            piles[currentPile].push_back(card);
            deck.erase(deck.begin());
            
            times++;
                
            if (piles[currentPile].size() < 3)
            {
                currentPile++;
                currentPile = currentPile % piles.size();
                continue;
            }
            
            while (piles[currentPile].size() >= 3)
            {
                //display(times);
                
                // first two and last one
                int combination = (piles[currentPile][0] - 'A') +
                    (piles[currentPile][1] - 'A') + (piles[currentPile].back() - 'A');
                if (combination == 10 || combination == 20 || combination == 30)
                {
                    deck.push_back(piles[currentPile][0]);
                    deck.push_back(piles[currentPile][1]);
                    deck.push_back(piles[currentPile].back());
                    
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    piles[currentPile].erase(piles[currentPile].begin());
                    piles[currentPile].erase(piles[currentPile].begin());
                    
                    continue;
                }
                
                // first one and last two
                combination = (piles[currentPile].front() - 'A') +
                    (piles[currentPile][piles[currentPile].size() - 2] - 'A') +
                    (piles[currentPile][piles[currentPile].size() - 1] - 'A');
                if (combination == 10 || combination == 20 || combination == 30)
                {
                    deck.push_back(piles[currentPile].front());
                    deck.push_back(piles[currentPile][piles[currentPile].size() - 2]);
                    deck.push_back(piles[currentPile][piles[currentPile].size() - 1]);
                    
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    piles[currentPile].erase(piles[currentPile].begin());
                    
                    continue;
                }
                
                // last three cards
                combination = (piles[currentPile][piles[currentPile].size() - 3] - 'A') +
                    (piles[currentPile][piles[currentPile].size() - 2] - 'A') +
                    (piles[currentPile][piles[currentPile].size() - 1] - 'A');
                if (combination == 10 || combination == 20 || combination == 30)
                {
                    deck.push_back(piles[currentPile][piles[currentPile].size() - 3]);
                    deck.push_back(piles[currentPile][piles[currentPile].size() - 2]);
                    deck.push_back(piles[currentPile][piles[currentPile].size() - 1]);
                    
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    piles[currentPile].erase(piles[currentPile].end() - 1);
                    
                    continue;
                }
                
                break;
            }
            
            if (piles[currentPile].size() == 0)
            {
                piles.erase(piles.begin() + currentPile);
                if (currentPile >= piles.size())
                    currentPile = 0;
            }
            else
            {
                currentPile++;
                currentPile = currentPile % piles.size();
            }
            
            if (piles.size() == 0)
                break;
        }
        
        if (draw)
            cout << "Draw: " << times << endl;
        else if (deck.size() && piles.size() == 0)
            cout << "Win : " << times << endl;
        else if (deck.size() == 0 && piles.size())
            cout << "Loss: " << times << endl;
    }
    
	return 0;
}
