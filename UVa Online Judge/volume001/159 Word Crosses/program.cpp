// Word Crosses
// UVa IDs: 159
// Verdict: Accepted
// Submission Date: 2016-02-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

bool findCrosses(string line)
{
    string a, b, c, d;
    istringstream iss(line);
    iss >> a >> b >> c >> d;
    
    //cout << a << " " << b << " " << c << " " << d << endl;
    
    int aIndex = -1, bIndex = -1;
    for (int i = 0; i < a.length(); i++)
        if ((bIndex = b.find(a[i])) != b.npos)
        {
            aIndex = i;
            break;
        }
        
    int cIndex = -1, dIndex = -1;
    for (int i = 0; i < c.length(); i++)
        if ((dIndex = d.find(c[i])) != d.npos)
        {
            cIndex = i;
            break;
        }
    
    //cout << aIndex << " " << bIndex << " " << cIndex << " " << dIndex << endl;
    
    if (aIndex >= 0 && cIndex >= 0)
    {
        char matrix[30][30] = { 0 };
        memset(matrix, ' ', sizeof(matrix));
        
        for (int i = 0; i < a.length(); i++)
            matrix[max(bIndex, dIndex)][i] = a[i];
        for (int i = 0; i < b.length(); i++)
            matrix[i + (bIndex < dIndex ? dIndex - bIndex : 0)][aIndex] = b[i];
        for (int i = 0; i < c.length(); i++)
            matrix[max(bIndex, dIndex)][a.length() + 3 + i] = c[i];
        for (int i = 0; i < d.length(); i++)
            matrix[i + (dIndex < bIndex ? bIndex - dIndex : 0)][a.length() + 3 + cIndex] = d[i];
        
        
        for (int i = 0; i < 30; i++)
            for (int j = 29; j >= 0; j--)
                if (matrix[i][j] != ' ')
                {
                    matrix[i][j + 1] = '*';
                    break;
                }
        
        int height = max(bIndex, dIndex);
        height += max(b.length() - bIndex - 1, d.length() - dIndex - 1);
        for (int i = 0; i <= height; i++)
        {
            for (int j = 0; j < (a.length() + 3 + c.length()); j++)
                if (matrix[i][j] != '*')
                    cout << matrix[i][j];
                 else
                    break;
            cout << endl;
        }
        
        return true;
    }
    
    return false;
}

int main(int argc, char* argv[])
{
    string line;
    bool printBlankLine = false;
    while (getline(cin, line), line != "#")
    {
        if (printBlankLine == false)
            printBlankLine = true;
        else
            cout << endl;
            
        if (!findCrosses(line))
            cout << "Unable to make two crosses" << endl;
    }
        
	return 0;
}
