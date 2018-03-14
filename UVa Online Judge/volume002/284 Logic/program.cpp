// Logic
// UVa ID: 284
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cell
{
    int index;
    int leftvalue, rightvalue;
    bool updated;
    char operators;
    vector <int> to;
};

cell grid[100];
vector <int> inputcell, outputcell;

int main(int argc, char *argv[])
{
    string line;
    int cases = 0;
    getline(cin, line);
    cases = stoi(line);

    while (cases--)
    {
        inputcell.clear(), outputcell.clear();
        
        for (int i = 0; i < 100; i++)
        {
            grid[i].index = i;
            grid[i].to.clear();
        }
        
        while (getline(cin, line), line[0] != 'e')
        {
            vector <string> input;
            string word;
            istringstream iss(line);
            while (iss >> word)
                input.push_back(word);
            
            int index = (input[0][0] - '0') * 10 + (input[0][1] - '0');
            grid[index].operators = input[0][2];
            
            if (input[0][2] == 'i')
                inputcell.push_back(index);
            if (input[0][2] == 'o')
                outputcell.push_back(index);
                
            for (int i = 1; i < input.size() - 1; i++)
                grid[index].to.push_back((input[i][0] - '0') * 10 + (input[i][1] - '0'));
        }
        
        int t;
        getline(cin, line);
        t = stoi(line);

        for (int k = 1; k <= t; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                grid[i].leftvalue = -1;
                grid[i].rightvalue = -1;
                grid[i].updated = false;
            }
        
            getline(cin, line);
            
            for (int j = line.length() - 1; j >= 0; j--)
                if (isblank(line[j]))
                    line.erase(line.begin() + j);
                else
                    break;
            
            for (int j = 0; j < line.length(); j++)
                grid[inputcell[j]].leftvalue = (line[j] == '1');
            
            bool updated;
            do
            {
                updated = false;
                for (int i = 0; i < 100; i++)
                {
                    if (grid[i].updated)
                        continue;
                    
                    if (grid[i].operators == 'i')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = grid[i].leftvalue;
                                else
                                    grid[grid[i].to[j]].rightvalue = grid[i].leftvalue;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    else if (grid[i].operators == '!')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = !grid[i].leftvalue;
                                else
                                    grid[grid[i].to[j]].rightvalue = !grid[i].leftvalue;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    else if (grid[i].operators == 'o')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                                grid[grid[i].to[j]].leftvalue = grid[i].leftvalue;
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    else if (grid[i].operators == '&')
                    {
                        if (grid[i].leftvalue >= 0 && grid[i].rightvalue >= 0)
                        {
                            int value = grid[i].leftvalue && grid[i].rightvalue;
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = value;
                                else
                                    grid[grid[i].to[j]].rightvalue = value;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    else if (grid[i].operators == '|')
                    {
                        if (grid[i].leftvalue >= 0 && grid[i].rightvalue >= 0)
                        {
                            int value = grid[i].leftvalue || grid[i].rightvalue;
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = value;
                                else
                                    grid[grid[i].to[j]].rightvalue = value;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                }
            } while (updated);
            
            for (int i = 0; i < outputcell.size(); i++)
                cout << (grid[outputcell[i]].leftvalue ? '1' : '0');
            cout << endl;
        }
        
        cout << endl;
    }
    
	return 0;
}
