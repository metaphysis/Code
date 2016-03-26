// City Navigation
// UVa IDs: 176
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct house
{
    char code;
    int index, number, step;
};

set < string > missing;
set < string > discovered;
house from, to;

void walk()
{
    queue < house > position;
    position.push(from);
    
    while (position.empty() == false)
    {
        house v = position.front();
        position.pop();
        
        if (v.code == 'A')
        {
            if (v.number % 2 == 0)
            {
                int sNumber = number / 100;
                if (v.number == 0)
                {
                    
                }
                else if (v.number == 98)
                {
                }
                else
                {
                }
            }
            else
            {
                
            }
        }
        else
        {
        }
        
        if (v.code == to.code && v.index == to.index && v.number == to.number)
        {
            cout << (v.step - 2) << endl;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    string line;
    int start, end;
    
    while(cin >> line, line != "#")
    {
        cin >> start >> end;
        
        for (int i = start; i <= end + 1; i++)
            missing.insert(line + to_string(i));
    }
    
    while (cin >> line, line != "#")
    {
        cin >> start;
        from = (house){line.front(), stoi(line.substr(1)), start, 1};
        
        cin >> line >> end;
        to = (house){line.front(), stoi(line.substr(1)), end, 0};
        
        walk();
    }
    
	return 0;
}
