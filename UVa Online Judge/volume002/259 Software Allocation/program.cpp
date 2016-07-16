// Software Allocation
// UVa ID: 259
// Verdict: Accepted
// Submission Date: 2016-05-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

vector < vector < int > > computer(10);
vector < int > applications(26);
vector < int > candidates(26);
vector < int > solution(10);

bool found = false;

void backtrack(int index)
{
    if (found)
        return;
        
    if (index == 10)
    {
        for (int i = 0; i < 26; i++)
            if (applications[i] > 0)
                return;
                
        found = true;
        for (int i = 0; i < 10; i++)
        {
            if (solution[i] == -1)
                cout << "_";
            else
                cout << (char)('A' + solution[i]);
        }
        cout << endl;
        
        return;
    }
    
    for (int i = 0; i < computer[index].size(); i++)
    {
        if (applications[computer[index][i]] > 0)
        {
            applications[computer[index][i]]--;
            solution[index] = computer[index][i];
            backtrack(index + 1);
            solution[index] = -1;
            applications[computer[index][i]]++;
            
            if (found)
                return;
        }
    }
    
    backtrack(index + 1);
}

void allocate()
{
    //for (int i = 0; i < applications.size(); i++)
        //cout << applications[i] << " ";
    //cout << endl;
    
    //for (int i = 0; i < computer.size(); i++)
    //{
        //for (int j = 0; j < computer[i].size(); j++)
            //cout << computer[i][j] << " ";
        //cout << endl;
    //}
    
    // check if the count of applications is bigger than count of computers or not
    int counter = 0;
    for (int i = 0; i < applications.size(); i++)
        counter += applications[i];
    if (counter > 10)
    {
        cout << "!\n";
        return;
    }
    
    // check if count of applications is less than or equal to available computers
    for (int i = 0; i < applications.size(); i++)
        if (applications[i] > candidates[i])
        {
            cout << "!\n";
            return;
        }
        
    found = false;
    fill(solution.begin(), solution.end(), -1);
    backtrack(0);
    
    if (found == false)
        cout << "!\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    fill(candidates.begin(), candidates.end(), 0);
    
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
        {
            allocate();
            
            for (int i = 0; i < computer.size(); i++)
                computer[i].clear();
                
            fill(applications.begin(), applications.end(), 0);
            fill(candidates.begin(), candidates.end(), 0);
        }
        else
        {
            applications[line[0] - 'A'] += (line[1] - '0');
            for (int i = 3; i < line.length() - 1; i++)
            {
                computer[line[i] - '0'].push_back(line[0] - 'A');
                candidates[line[0] - 'A']++;
            }
        }
    }
    
    allocate();
    
	return 0;
}
