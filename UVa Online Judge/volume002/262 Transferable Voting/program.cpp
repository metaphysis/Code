// Transferable Voting 
// UVa IDs: 262
// Verdict: Accepted
// Submission Date: 2016-06-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

map<int, string> names;
vector< vector<int> > ballots;
set<int> candidates;
int spoiled;

void voting()
{
    bool tie = false;
    while (true)
    {
        map<int, int> counter;
        for (auto i = candidates.begin(); i != candidates.end(); i++)
            counter[(*i)] = 0;
            
        for (auto i = ballots.begin(); i != ballots.end(); i++)
            if (!(*i).empty())
                counter[(*i).front()]++;
                
        int minCounter = ballots.size(), maxCounter = 0;
        for (auto i = counter.begin(); i != counter.end(); i++)
        {
            minCounter = min(minCounter, (*i).second);
            maxCounter = max(maxCounter, (*i).second);
        }

        if (maxCounter > ballots.size() / 2)
        {
            for (auto i = counter.begin(); i != counter.end(); i++)
                if ((*i).second == maxCounter)
                {
                    cout << "The winner of the election is ";
                    cout << names[(*i).first] << "." << endl;
                    break;
                }
                
            break;
        }
        
        vector <int> eliminated;
        for (auto i = counter.begin(); i != counter.end(); i++)
            if ((*i).second == minCounter)
            {
                eliminated.push_back((*i).first);
                candidates.erase((*i).first);
                
                for (auto j = ballots.begin(); j != ballots.end(); j++)
                    for (int k = (*j).size() - 1; k >= 0; k--)
                        if ((*j)[k] == (*i).first)
                            (*j).erase((*j).begin() + k);
                            
            }
        
        sort(eliminated.begin(), eliminated.end());
        for (int i = 0; i < eliminated.size(); i++)
        {
            cout << names[eliminated[i]] << " with ";
            cout << counter[eliminated[i]] << " votes is eliminated." << endl;
        }
        
        // If there only is one candidate left, he automatically wins,
        // no matter how many votes he has. 
        if (candidates.size() == 1)
        {
            cout << "The winner of the election is ";
            cout << names[*(candidates.begin())] << "." << endl;
            break;
        }
        
        if (candidates.empty())
        {
            tie = true;
            break;
        }
    }
    
    if (tie)
        cout << "The election was indecisive." << endl;
    cout << "There were " << ballots.size() << " valid ballots and ";
    cout << spoiled << " spoiled ballots." << endl;
    
}

int main(int argc, char *argv[])
{
    string line;
    int cases = (getline(cin, line), stoi(line));
    
    // empty line
    getline(cin, line);

    while (cases--)
    {
        // read candidates
        names.clear();
        candidates.clear();
        ballots.clear();
        while (getline(cin, line), line.length() > 0)
        {
            int index = line.find('.');
            int number = stoi(line.substr(0, index));
            string name = line.substr(index + 2);
            names.insert(make_pair(number, name));
            //cout << "number = " << number << " name = " << name << endl;
            candidates.insert(number);
        }
        
        // read ballots
        spoiled = 0;
        while (getline(cin, line))
        {
            if (line.length() > 0)
            {
                istringstream iss(line);
                vector<int> aBallot;
                set<int> existed;
                int number;
                bool is_spoiled = false;
                while (iss >> number)
                {
                    if (candidates.count(number) > 0 && existed.count(number) == 0)
                    {
                        aBallot.push_back(number);
                        existed.insert(number);
                    }
                    else
                    {
                        is_spoiled = true;
                        break;
                    }
                }
                
                if (is_spoiled == false)
                    ballots.push_back(aBallot);
                else
                    spoiled++;
            }
            else
                break;
        }
        
        if (ballots.size() == 0 && names.size() == 1)
        {
            cout << "The winner of the election is ";
            cout << (*(names.begin())).second << "." << endl;
            cout << "There were 0 valid ballots and " << spoiled;
            cout << " spoiled ballots." << endl;
        }
        else
            voting();
        
        
        if (cases)
            cout << endl;
    }
    
	return 0;
}
