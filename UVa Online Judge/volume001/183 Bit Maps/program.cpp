// Bit Maps
// UVa IDs: 183
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>

using namespace std;

string category, code, buffer;
int row, column;
char matrix[210][210];

string trim(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);
        else
            break;
            
    while (line.length() > 0 && isblank(line.front()))
        line.erase(line.begin());
        
    return line;
}

void bitToCode()
{
    cout << category << " " << row << " " << column << endl;
    cout << buffer << endl;
}

void codeToBit()
{
    cout << category << " " << row << " " << column << endl;
    cout << buffer << endl;
}

void process()
{
    if (category == "B")
        bitToCode();
    else
        codeToBit();    
}

void read(string line)
{
    istringstream iss(line);
    iss >> category >> row >> column;    
}

int main(int argc, char *argv[])
{
    string line;
    bool categorySetted = false;
    
    while (getline(cin, line))
    {
        line = trim(line);
        
        if (line.find(' ') != line.npos)
        {
            if (categorySetted == false)
            {
                categorySetted = true;
                read(line);
            }
            else
            {
                process();
                buffer.clear();
                read(line);
            }
        }
        else if(line != "#")
        {
            buffer += trim(line);
        }
        else if (line == "#")
        {
            process();
            break;
        }
    }
    
	return 0;
}
