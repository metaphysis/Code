// Keywords
// UVa ID: 175 
// Verdict: Accepted
// Submission Date: 2016-02-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

vector<vector<string>> profiles, titles;
vector<int> gaps;

void processProfile(string line)
{
    line = line.substr(line.find("P:") + 2);
    
    //cout << line << endl;
    
    string word;
    int distance;
    
    istringstream iss(line);
    iss >> distance;
    
    gaps.push_back(distance);
    
    vector < string > keywords;
    while (iss >> word)
        keywords.push_back(word);
    
    //for (int i = 0; i < keywords.size(); i++)
        //cout << keywords[i] << " ";
    //cout << endl;
        
    profiles.push_back(keywords);
}

void processTitle(string line)
{
    line = line.substr(line.find("T:") + 2);
    for (int i = line.length() - 1; i >= 0; i--)
        if (isalpha(line[i]))
        {
            if (isupper(line[i]))
                line[i] = tolower(line[i]);
        }
        else if (line[i] != ' ' && line[i] != '\t')
        {
            line.erase(line.begin() + i);
        }
        
    istringstream iss(line);
    vector<string> singleTitle;
    string word;
    while (iss >> word)
        singleTitle.push_back(word);
        
    //for (int i = 0; i < singleTitle.size(); i++)
        //cout << singleTitle[i] << " ";
    //cout << endl;
    
    titles.push_back(singleTitle);
}

bool findKeywords(int i, int m, int gap)
{
    for (int j = 0; j < profiles[i].size() - 1; j++)
        for (int n = 0; n < titles[m].size(); n++)
        {
            if (titles[m][n] == profiles[i][j])
            {
                for (int k  = j + 1; k < profiles[i].size(); k++)
                {
                    int up = n + gap + 1, down = n - gap - 1;
                    for (int x = max(down, 0); x <= min(up, (int)(titles[m].size()) - 1); x++)
                    {
                        if (x == n)
                            continue;
                            
                        //cout << titles[m][x] << " " << profiles[i][k] << "\n";
                        if (titles[m][x] == profiles[i][k])
                            return true;
                    }
                }
            }
        }
    
    return false;        
}

void searchTitle()
{
    for (int i = 0; i < profiles.size(); i++)
    {
        cout << (i + 1) << ": ";
        bool firstPrinted = false;
        
        for (int j = 0; j < titles.size(); j++)
            if (findKeywords(i, j, gaps[i]))
            {
                if (firstPrinted == false)
                    firstPrinted = true;
                else
                    cout << ",";
                    
                cout << (j + 1);
            }
            
        cout << "\n";    
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line, title;
    bool profileEnded = false;
    while (getline(cin, line), line != "#")
    {
        if (profileEnded == false && line.find("T:") == line.npos)
        {
            processProfile(line);
            continue;
        }
        else
            profileEnded = true;
            
        title += line;
        if (line.find('|') != line.npos)
        {
            processTitle(title);
            title.clear();
        }
    }
    
    searchTitle();
    
	return 0;
}
