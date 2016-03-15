// Spreadsheet
// UVa IDs: 196
// Verdict: Accepted
// Submission Date: 
// UVa Run Time: 0.093s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <map>

using namespace std;

map < string, int > cells;
map < string, vector < string > > formula;
string columns = "ZABCDEFGHIJKLMNOPQRSTUVWXY";

string getCellId(int i, int j)
{
    string id;
    while (j > 0)
    {
        id.insert(id.begin(), columns[j % 26]);
        if (j % 26 == 0)
            j -= 26;
        j /= 26;
    }
    return id + to_string(i);
}

int getValue(string x)
{
    if (cells.count(x))
        return cells[x];
        
    int sum = 0;    
    for (int i = 0; i < formula[x].size(); i++)
        sum += getValue(formula[x][i]);
    cells[x] = sum;
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    while (n--)
    {
        int row, column;
        cin >> column >> row;
        
        cells.clear();
        formula.clear();
        
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= column; j++)
            {
                string block;
                cin >> block;
                
                string id = getCellId(i, j);
                if (block.front() == '=')
                {
                    block += '+';
                    int start = 1, next = start;
                    while (start < block.length())
                    {
                        next = block.find('+', start);
                        formula[id].push_back(block.substr(start, next - start));
                        start = next + 1;
                    }
                }
                else
                    cells[id] = stoi(block);
            }
        
        for (int i = 1; i <= row; i++)
        {
            for (int j = 1; j <= column; j++)
                cout << (j > 1 ? " ": "") << getValue(getCellId(i, j));
            cout << "\n";
        }
            
    }
    
	return 0;
}
