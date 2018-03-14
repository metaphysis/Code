// Slurpys
// UVa ID: 384
// Verdict: Accepted
// Submission Date: 2016-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isC();
bool isSlump();
bool isSlimp();
bool isSlurpy();

string line;
int position;

bool isC()
{
    if (position < line.length() && line[position] == 'C')
    {
        position++;
        return true;
    }
    else
        return false;
}

bool isSlump()
{
    if (position < line.length() && (line[position] == 'D' || line[position] == 'E'))
        position++;
    else
        return false;
    
    bool atLeastOneF = false;
    while (position < line.length() && line[position] == 'F')
    {
        atLeastOneF = true;
        position++;
    }
    
    if (atLeastOneF == false)
        return false;
        
    if (position < line.length() && line[position] == 'G')
    {
        position++;
        return true;
    }
    else
        return isSlump();
}

bool isSlimp()
{
    if (position < line.length() && line[position] == 'A')
        position++;
    else
        return false;
        
    if (position < line.length() && line[position] == 'H')
    {
        position++;
        return true;
    } 
    else if (position < line.length() && line[position] == 'B')
    {
        position++;
        return isSlimp() && isC();
    }
    else
        return isSlump() && isC();
}

bool isSlurpy()
{
    //return isSlimp() && position == line.length();
    //return isSlump() && position == line.length();
    return isSlimp() && isSlump() && position == line.length();
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    getline(cin, line);
    int n = stoi(line);
    
    cout << "SLURPYS OUTPUT" << endl;
    
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        position = 0;
        cout << (isSlurpy() ? "YES" : "NO") << endl;
    }   
    
    cout << "END OF OUTPUT" << endl;
    
	return 0;
}
