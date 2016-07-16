// PGA Tour Prize Money
// UVa ID: 207
// Verdict: Accepted
// Submission Date: 2016-04-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const int DQ = -1;

struct player
{
    string name;
    int rd1, rd2, rd3, rd4, total, place, round;
    bool amateur, tie, prized;
    double prize;
};

bool printBlankLine = false;
vector < player > players;
vector < double > percents;
double money;

bool cmp(player a, player b)
{
    if (a.total == b.total)
        return a.name < b.name;
    else
        return a.total < b.total;
}

bool cmp2(player a, player b)
{
    if (a.round == b.round)
        return cmp(a, b);
    else
        return a.round > b.round;
}

void allocate()
{
    if (printBlankLine)
        cout << "\n";
    else
        printBlankLine = true;
        
    // print header
    cout << setw(21) << left << "Player Name";
    cout << setw(10) << left << "Place";
    cout << setw(5) << left << "RD1";
    cout << setw(5) << left << "RD2";
    cout << setw(5) << left << "RD3";
    cout << setw(5) << left << "RD4";
    cout << setw(10) << left << "TOTAL";
    cout << "Money Won\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // first cut
    vector < player > dq;
    vector < player > firstcut;
    for (int i = 0; i < players.size(); i++)
        if (players[i].round >= 2)
        {
            players[i].total = players[i].rd1 + players[i].rd2;
            firstcut.push_back(players[i]);
        }
       
    sort(firstcut.begin(), firstcut.end(), cmp);
    if (firstcut.size() > 70)
    {
        int last;
        for (last = 70; last < firstcut.size(); last++)
            if (firstcut[last].total == firstcut[69].total)
                continue;
            else
                break;
        firstcut.erase(firstcut.begin() + last, firstcut.end());
    }
    
    // second cut
    vector < player > secondcut;
    for (int i = 0; i < firstcut.size(); i++)
    {
        if (firstcut[i].round >= 4)
        {
            firstcut[i].total += (firstcut[i].rd3 + firstcut[i].rd4);
            firstcut[i].prized = false;
            firstcut[i].tie = false;
            secondcut.push_back(firstcut[i]);
        }
        else
            dq.push_back(firstcut[i]);
    }
    sort(secondcut.begin(), secondcut.end(), cmp);
    
    // rank and allocate money
    for (int i = 0, index = 0; i < secondcut.size() && index < 70; i++)
        if (!secondcut[i].amateur)
        {
            secondcut[i].prize = percents[index++];
            secondcut[i].prized = true;
        }
    
    for (int i = 0, place = 1; i < secondcut.size();)
    {
        int counter = 0, prizedPlayers = 0, noAmateurs = 0;
        double prizeAllocate = 0.0;
        while ((i + counter) < secondcut.size() &&
            secondcut[i + counter].total == secondcut[i].total)
        {
            if (!secondcut[i + counter].amateur && secondcut[i + counter].prized)
                prizedPlayers++;
            if (!secondcut[i + counter].amateur)
                noAmateurs++;
            if (secondcut[i + counter].prized)
                prizeAllocate += secondcut[i + counter].prize;
            counter++;
        }

        if (counter > 1)
        {
            if (prizedPlayers > 0)
                prizeAllocate /= noAmateurs;
            prizeAllocate *= money;
            for (int j = 0; j < counter; j++)
            {
                secondcut[i + j].place = place;
                if (!secondcut[i + j].amateur && prizedPlayers > 0)
                {
                    secondcut[i + j].tie = noAmateurs > 1;
                    secondcut[i + j].prized = true;
                    secondcut[i + j].prize = prizeAllocate;
                }
            }
            place += counter;
            i += counter;
        }
        else
        {
            secondcut[i].place = place;
            secondcut[i].tie = false;
            secondcut[i].prize *= money;
            place++;
            i++;
        }
    }
    
    // output the money winner
    for (int i = 0; i < secondcut.size(); i++)
    {
        cout << setw(21) << left << secondcut[i].name;
        string standing = to_string(secondcut[i].place) + (secondcut[i].tie ? "T" : "");
        cout << setw(10) << left << standing;
        cout << setw(5) << left << secondcut[i].rd1;
        cout << setw(5) << left << secondcut[i].rd2;
        cout << setw(5) << left << secondcut[i].rd3;
        cout << setw(5) << left << secondcut[i].rd4;

        if (secondcut[i].prized)
        {
            cout << setw(10) << left << secondcut[i].total;
            cout << "$";
            cout << setw(9) << right << fixed << setprecision(2) << secondcut[i].prize;
        }
        else
            cout << secondcut[i].total;

        cout << "\n";
    }
    
    // In case of tie order the players by rounds completed and by total shots. 
    // If there’s still a tie, order them in alphabetical order.
    for (int i = 0; i < dq.size(); i++)
        dq[i].total += dq[i].rd3 != DQ ? dq[i].rd3 : 0;
    
    sort(dq.begin(), dq.end(), cmp2);
    
    for (int i = 0; i < dq.size(); i++)
    {
        cout << setw(21) << left << dq[i].name;
        cout << setw(10) << left << "";
        cout << setw(5) << left << (dq[i].rd1 != DQ ? to_string(dq[i].rd1) : "");
        cout << setw(5) << left << (dq[i].rd2 != DQ ? to_string(dq[i].rd2) : "");
        cout << setw(5) << left << (dq[i].rd3 != DQ ? to_string(dq[i].rd3) : "");
        cout << setw(5) << left << (dq[i].rd4 != DQ ? to_string(dq[i].rd4) : "");
        cout << "DQ\n";
    }
}

string trim(string line)
{
    while (line.length() && isblank(line.back()))
        line.erase(line.end() - 1);
    while (line.length() && isblank(line.front()))
        line.erase(line.begin());
    return line;
}

player parseToPlayer(string line)
{
    while (line.length() < 32)
        line += ' ';
        
    player x;
    x.name = line.substr(0, 20);
    x.amateur = trim(x.name).back() == '*';
    
    x.rd1 = DQ;
    x.rd2 = DQ;
    x.rd3 = DQ;
    x.rd4 = DQ;
    x.round = 0;
    
    string rd1 = trim(line.substr(20, 3));
    string rd2 = trim(line.substr(23, 3));
    string rd3 = trim(line.substr(26, 3));
    string rd4 = trim(line.substr(29, 3));
    
    if (rd1 != "DQ")
    {
        x.rd1 = stoi(rd1);
        x.round++;
    }
    else
        return x;
        
    if (rd2 != "DQ")
    {
        x.rd2 = stoi(rd2);
        x.round++;
    }
    else
        return x;
           
    if (rd3 != "DQ")
    {
        x.rd3 = stoi(rd3);
        x.round++;
    }
    else
        return x;
    
    if (rd4 != "DQ")
    {
        x.rd4 = stoi(rd4);
        x.round++;
    }
            
    return x;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        players.clear();
        percents.clear();
        
        cin >> money;
        double percent;
        for (int i = 1; i <= 70; i++)
        {
            cin >> percent;
            percents.push_back(percent / 100.0);
        }
        
        int totalPlayers;
        cin >> totalPlayers;
        cin.ignore();
        
        string line;
        for (int i = 1; i <= totalPlayers; i++)
        {
            getline(cin, line);
            players.push_back(parseToPlayer(line));
        }
        
        allocate();
    }
    
	return 0;
}
