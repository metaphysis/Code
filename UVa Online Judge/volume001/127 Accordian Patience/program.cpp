// "Accordian" Patience
// UVa ID: 127
// Verdict: Accepted
// Submission Date: 2015-11-28
// UVa Run Time: 1.159s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

vector< vector<string> > piles;

void print()
{
    cout << piles.size();
    cout << (piles.size() > 1 ? " piles" : " pile") <<" remaining:";
    for (int i = 0; i < piles.size(); i++) cout << " " << piles[i].size();
    cout << endl;
}

void getCards(string line)
{
    istringstream iss(line);

    string card;
    while (iss >> card)
    {
        vector<string> pile;
        pile.push_back(card);
        piles.push_back(pile);
    }
}

bool canMoveToLeft(int index)
{
    return (index > 0 && (piles[index].back()[0] == piles[index - 1].back()[0] ||
        piles[index].back()[1] == piles[index - 1].back()[1]));
}

bool canMoveToThirdLeft(int index)
{
    return (index > 2 && (piles[index].back()[0] == piles[index - 3].back()[0] ||
        piles[index].back()[1] == piles[index - 3].back()[1]));
}

void play()
{
    while (true)
    {
        for (int i = piles.size() - 1; i >= 0; i--)
            if (piles[i].size() == 0)
                piles.erase(piles.begin() + i);

        int index = 0;
        bool moved = false;
        while (index >= 0 && index < piles.size())
        {
            if (piles[index].size() == 0) break;
                
            if (canMoveToThirdLeft(index))
            {
                piles[index - 3].push_back(piles[index].back());
                piles[index].erase(piles[index].end());
                index -= 3;
                moved = true;
                continue;
            }
            
            if (canMoveToLeft(index))
            {   
                piles[index - 1].push_back(piles[index].back());
                piles[index].erase(piles[index].end());
                index -= 1;
                moved = true;
                continue;
            }

            index++;
        }
        
        if (!moved) break;
    }
}

int main(int argc, char *argv[])
{
    string line1, line2;
    while (true)
    {
        piles.clear();

        getline(cin, line1);
        if (line1.front() == '#') break;
        getCards(line1);
        
        getline(cin, line2);
        getCards(line2);
        
        play();

        print();
    }
    
	return 0;
}
