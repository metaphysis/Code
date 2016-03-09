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
vector < string > followerCards;
vector < int > scores;
string face = "23456789TJQKA", suit = "CDHS";
int leader = 0, winner, trump;
string winnerCard;
bool trumped;

bool followerCmp(string x, string y)
{
    int face1 = face.find(x[0]);
    int face2 = face.find(y[0]);
    int suit1 = suit.find(x[1]);
    int suit2 = suit.find(y[1]);
    
    if (face1 != face2)
        return face1 > face2;
    else
        return suit1 > suit2;
}

void getWinnerCard(int index, string followerCard)
{
    int face1 = face.find(winnerCard[0]);
    int face2 = face.find(followerCard[0]);
    int suit1 = suit.find(winnerCard[1]);
    int suit2 = suit.find(followerCard[1]);
    
    if (suit2 != suit1)
    {
        if (suit2 == trump)
        {
            winner = index;
            winnerCard = followerCard;
        }
        //else if (suit1 != trump && suit2 != trump)
        //{
            //if (face2 > face1 || (face1 == face2 && suit2 > suit1))
            //{
                //winner = index;
                //winnerCard = followerCard;
            //}
        //}
    }
    else
    {
        if (face2 > face1)
        {
            winner = index;
            winnerCard = followerCard;
        }
    }        
}

string getFollowerCard(int index, string leaderCard)
{   
    cout << "leader card: " << leaderCard << " ";
    
    string followerCard;
    sort(players[index].begin(), players[index].end(), followerCmp);
    
    // find correct suit card
    bool found = false;
    for (int i = 0; i < players[index].size(); i++)
        if (players[index][i][1] == leaderCard[1])
        {
            followerCard = players[index][i];
            players[index].erase(players[index].begin() + i);
            found = true;
            break;
        }
    
    // find highest trump card
    if (found == false)
    {
        for (int i = 0; i < players[index].size(); i++)
        {
            //cout << players[index][i] << " " << suit[trump] << endl;
            if (players[index][i][1] == suit[trump])
            {
                followerCard = players[index][i];
                players[index].erase(players[index].begin() + i);
                found = true;
                break;
            }
        }      
    }
    
    // find highest card
    if (found == false)
    {
        followerCard = players[index][0];
        players[index].erase(players[index].begin());        
    }
    
    getWinnerCard(index, followerCard);
    
    cout << "follower " << index << " card: " << followerCard << endl;
    
    return followerCard;
}

bool leaderCmp(string x, string y)
{
    int face1 = face.find(x[0]);
    int face2 = face.find(y[0]);
    int suit1 = suit.find(x[1]);
    int suit2 = suit.find(y[1]);
    
    if (face1 != face2)
        return face1 > face2;
    else
    {
        if (suit1 == trump && suit2 != trump)
            return true;
            
        if (suit1 != trump && suit2 == trump)
            return false;
            
        return suit1 > suit2;
    }
}

string getLeaderCard(int index)
{
    sort(players[index].begin(), players[index].end(), leaderCmp);
    string leaderCard = players[index][0];
    players[index].erase(players[index].begin());
    trumped = leaderCard[1] == suit[trump];
    return leaderCard;
}

void showCard()
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < players[i].size(); j++)
            cout << players[i][j] << " ";
        cout << endl;
    }
}

void play()
{
    followerCards.clear();
    followerCards.push_back(getLeaderCard(leader));
    
    cout << "  leader " << leader << " card: " << followerCards[0] << endl;
    
    winner = leader;
    winnerCard = followerCards[0];
    
    for (int i = 1; i <= 4; i++)
    {
        leader = (leader + 1) % 5;
        followerCards.push_back(getFollowerCard(leader, followerCards[0]));
    }
    
    cout << endl;
    cout << "winner: " << winner << " scores: " << scores[winner] << endl;
    
    for (int i = 0; i < followerCards.size(); i++)
        if (followerCards[i][1] == 'H')
        {
            scores[winner] += (face.find(followerCards[i][0]) + 2);
            cout << "found " << followerCards[i] << " " << scores[winner] << endl;
        }
    
    showCard();
            
    leader = winner;
}

int main(int argc, char *argv[])
{
    string line, deck;
    int lineNumber = 0;
    
    for (int i = 1; i <= 5; i++)
    {
        vector < string > cards;
        players.push_back(cards);
        scores.push_back(0);
    }
    
    while (getline(cin, line), line != "#")
    {
        lineNumber++;
        deck += line;
        
        //cout << line << endl;
        
        if (lineNumber == 4)
        {
            for (int i = deck.length() - 1; i >= 0; i--)
                if (isblank(deck[i]))
                    deck.erase(deck.begin() + i);
            
            cout << deck << endl;
            
            //for (int i = 0; i < players.size(); i++)
                //players[i].clear();
                
            int marker = 0;
            for (int i = 0; i < deck.length() - 4; i += 2)
            {
                players[marker % 5].push_back(deck.substr(i, 2));
                marker++;
            }
            
            string last1 = deck.substr(102, 2);
            string last2 = deck.substr(100, 2);
            
            cout << last1 << " " << last2 << endl;
            
            int face1 = face.find(last1[0]);
            int face2 = face.find(last2[0]);
            int suit1 = suit.find(last1[1]);
            int suit2 = suit.find(last2[1]);
            
            char cTrump;
            if (face1 == face2)
                cTrump = suit1 > suit2 ? suit[suit1] : suit[suit2];
            else
                cTrump = face1 > face2 ? last1[1] : last2[1];
            
            trump = suit.find(cTrump);
            
            cout << suit[trump] << endl;
            
            for (int i = 0; i < players.size(); i++)
                sort(players[i].begin(), players[i].end(), leaderCmp);
                
            showCard();
                  
            fill(scores.begin(), scores.end(), 0);
            
            for (int i = 1; i <= 10; i++)
                play();
            
            cout << setw(3) << right << scores[4];
            for (int i = 0; i <= 3; i++)
                cout << setw(3) << right << scores[i];
            cout << endl;
            
            deck.clear();
            lineNumber = 0;
            leader = 0;
        }
    }
    
	return 0;
}
