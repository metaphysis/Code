// Hearts
// UVa ID: 181
// Verdict: Accepted
// Submission Date: 2016-03-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct card
{
    string text;
    int face, suit;
};

vector<vector<card>> players;
vector<card> followerCards;
vector<int> scores;
string faces = "23456789TJQKA", suits = "CDHS";
int leader, winner, trump;
card winnerCard;

void getWinnerCard(int index, card followerCard)
{
    if ((followerCard.suit != winnerCard.suit && followerCard.suit == trump) ||
            (followerCard.suit == winnerCard.suit && followerCard.face > winnerCard.face))
    {
        winner = index;
        winnerCard = followerCard;
    }
}

bool followerCmp(card x, card y)
{
    return (x.face != y.face) ? x.face > y.face : x.suit > y.suit;
}

card getFollowerCard(int index, card leaderCard)
{
    card followerCard;
    sort(players[index].begin(), players[index].end(), followerCmp);

    // find highest correct suit card
    bool found = false;
    for (int i = 0; i < players[index].size(); i++)
        if (players[index][i].suit == leaderCard.suit)
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
            if (players[index][i].suit == trump)
            {
                followerCard = players[index][i];
                players[index].erase(players[index].begin() + i);
                found = true;
                break;
            }
    }

    // find highest card
    if (found == false)
    {
        followerCard = players[index][0];
        players[index].erase(players[index].begin());
    }

    getWinnerCard(index, followerCard);

    return followerCard;
}

bool leaderCmp(card x, card y)
{
    if (x.face != y.face)
        return x.face > y.face;
    else
    {
        if (x.suit == trump && y.suit != trump)
            return true;

        if (x.suit != trump && y.suit == trump)
            return false;

        return x.suit > y.suit;
    }
}

card getLeaderCard(int index)
{
    sort(players[index].begin(), players[index].end(), leaderCmp);
    card leaderCard = players[index][0];
    players[index].erase(players[index].begin());
    return leaderCard;
}

void play()
{
    followerCards.clear();
    followerCards.push_back(getLeaderCard(leader));

    winner = leader;
    winnerCard = followerCards.front();

    for (int i = 1; i <= 4; i++)
    {
        leader = (leader + 1) % 5;
        followerCards.push_back(getFollowerCard(leader, followerCards.front()));
    }

    for (int i = 0; i < followerCards.size(); i++)
        if (followerCards[i].text[1] == 'H')
            scores[winner] += (followerCards[i].face + 2);

    leader = winner;
}

int main(int argc, char *argv[])
{
    string line, deck;
    int lineNumber = 0;

    for (int i = 1; i <= 5; i++)
    {
        vector < card > cards;
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

            for (int i = 0, j = 0; i < deck.length() - 4; i += 2, j++)
            {
                string text = deck.substr(i, 2);
                players[j % 5].push_back((card) {
                    text, (int)faces.find(text[0]), (int)suits.find(text[1])
                });
            }

            string last1 = deck.substr(102, 2);
            string last2 = deck.substr(100, 2);

            int face1 = faces.find(last1[0]);
            int face2 = faces.find(last2[0]);
            int suit1 = suits.find(last1[1]);
            int suit2 = suits.find(last2[1]);

            if (face1 == face2)
                trump = suit1 > suit2 ? suit1 : suit2;
            else
                trump = face1 > face2 ? suit1 : suit2;

            fill(scores.begin(), scores.end(), 0);

            leader = 0;
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
