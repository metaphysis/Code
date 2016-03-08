// Hearts
// UVa IDs: 181
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

vector < vector < string > > players;
vector < int > scores;
string face = "23456789TJQKA", suit = "CDHS";
int leader = 0;
char trump;

bool cmp(string x, string y)
{
    
}

void play()
{
    string leaderCard;
}

int main(int argc, char *argv[])
{
    string line, deck;
    int lineNumber = 0;
    
    for (int i = 1; i <= 5; i++)
    {
        vector < string > cards;
        for (int i = 1; i <= 10; i++)
            cards.push_back("1H");
        players.push_back(cards);
        scores.push_back(0);
    }
    
    while (getline(cin, line), line != "#")
    {
        lineNumber++;
        deck += line;
        
        if (lineNumber == 4)
        {
            for (int i = deck.length() - 1; i >= 0; i--)
                if (isblank(deck[i]))
                    deck.erase(deck.begin() + i);
            
            int marker = 0, index = 0;
            for (int i = 0; i < deck.length() - 4; i += 2)
            {
                players[marker % 5][index] = deck.substr(i, 2);
                marker++;
                if (marker % 5 == 0)
                    index++;
            }
            
            string last1 = deck.substr(102, 2);
            string last2 = deck.substr(100, 2);
            
            cout << last1 << " " << last2 << endl;
            
            int face1 = face.find(last1[0]);
            int face2 = face.find(last2[0]);
            int suit1 = suit.find(last1[1]);
            int suit2 = suit.find(last2[1]);
            
            if (face1 == face2)
                trump = suit1 > suit2 ? suit[suit1] : suit[suit2];
            else
                trump = face1 > face2 ? last1[1] : last2[1];
                
            cout << trump << endl;
            
            for (int i = 0; i < players.size(); i++)
            {
                for (int j = 0; j < players[i].size(); j++)
                    cout << players[i][j] << " ";
                cout << endl;
            }
                  
            fill(scores.begin(), scores.end(), 0);
            
            for (int i = 1; i <= 10; i++)
                play();
            
            cout << setw(3) << right << scores[4];
            for (int i = 0; i < 4; i++)
                cout << setw(3) << right << scores[i];
            cout << endl;
            
            deck.clear();
            lineNumber = 0;
            leader = 1;
        }
    }
    
	return 0;
}
