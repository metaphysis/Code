// Beggar My Neighbour
// UVa ID: 162
// Verdict: Accepted
// Submission Date: 2016-02-10
// UVa Run Time: 0.033s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<char> nonDealer;
vector<char> dealer;
vector<char> piles;
int cardNeeded, newCardNeeded, exposer;
char card;

void display()
{
    cout << "non-dealer: ";
    for (int i = 0; i < nonDealer.size(); i++)
        cout << nonDealer[i] << " ";
    cout << endl;
    
    cout << "dealer: ";
    for (int i = 0; i < dealer.size(); i++)
        cout << dealer[i] << " ";
    cout << endl;  
    
    cout << "piles: ";
    for (int i = 0; i < piles.size(); i++)
        cout << piles[i] << " ";
    cout << endl;  
}

void collect()
{
    if (exposer == 1)
        nonDealer.insert(nonDealer.end(), piles.begin(), piles.end());
    else
        dealer.insert(dealer.end(), piles.begin(), piles.end());
    piles.clear();
    
    //display();
}

void play()
{
    string cover = "JQKA";
    reverse(nonDealer.begin(), nonDealer.end());
    reverse(dealer.begin(), dealer.end());
    piles.clear();
    cardNeeded = 1;
    exposer = 0;
    
firstPlayer:    
    while (nonDealer.size() > 0)
    {
        cardNeeded--;
        card = nonDealer[0];
        piles.push_back(nonDealer[0]);
        nonDealer.erase(nonDealer.begin());
        
        //display();
        
        if ((newCardNeeded = cover.find(card)) != cover.npos)
        {
            exposer = 1;
            cardNeeded = newCardNeeded + 1;
            goto secondPlayer;
        }
        
        if (cardNeeded == 0)
        {
            cardNeeded = 1;
            if (exposer > 0)
            {
                collect();
                if (exposer == 1)
                {
                    exposer = 0;
                    goto firstPlayer;
                }
                else
                {
                    exposer = 0;
                    goto secondPlayer;
                }
            }
            else
                goto secondPlayer;
        }
    }
    
    cout << "1" << setw(3) << right << dealer.size() << endl;
    
    goto end;
    
secondPlayer:
    while (dealer.size() > 0)
    {
        cardNeeded--;
        card = dealer[0];
        piles.push_back(dealer[0]);
        dealer.erase(dealer.begin());
        
        //display();
        
        if ((newCardNeeded = cover.find(card)) != cover.npos)
        {
            exposer = 2;
            cardNeeded = newCardNeeded + 1;
            goto firstPlayer;
        }
        
        if (cardNeeded == 0)
        {
            cardNeeded = 1;
            if (exposer > 0)
            {
                collect();
                if (exposer == 1)
                {
                    exposer = 0;
                    goto firstPlayer;
                }
                else
                {
                    exposer = 0;
                    goto secondPlayer;
                }
            }
            else
                goto firstPlayer;
        }
    }

    cout << "2" << setw(3) << right << nonDealer.size() << endl;
    
end:
    ;
}

int main(int argc, char* argv[])
{
    string card;
    int index = 1;
    while (cin >> card, card != "#")
    {
        if ((index++ % 2) == 1)
            nonDealer.push_back(card[1]);
        else
            dealer.push_back(card[1]);
        
        if (dealer.size() == 26)
        {
            play();
            
            nonDealer.clear();
            dealer.clear();
            index = 1;
        }
    }
    
	return 0;
}
