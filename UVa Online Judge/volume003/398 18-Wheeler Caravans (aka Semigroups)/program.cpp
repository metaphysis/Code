// 18-Wheeler Caravans (aka Semigroups)
// UVa IDs: 398
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.000s
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
        
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        vector<char> elements(n);
        vector<string> table(n);
        char multiplication[30][30];
        map<char, int> location;
        
        for (int i = 0; i < n; i++)
        {
            cin >> elements[i];
            location[elements[i]] = i;
        }

        for (int i = 0; i < n; i++)
        {
            cin >> table[i];
            for (int j = 0; j < n; j++)
                multiplication[i][j] = table[i][j];
        }

        if (cases++) cout << endl;
  
        cout << "S = {";
        for (int i = 0; i < n; i++)
        {
            if (i > 0) cout << ",";
            cout << elements[i];
        }
        cout << "}" << endl;

        cout << " #|";
        for (int i = 0; i < n; i++)
            cout << elements[i];
        cout << endl;

        cout << " -+" << string(n, '-') << endl;

        for (int i = 0; i < n; i++)
            cout << " " << elements[i] << "|" << table[i] << endl;
        cout << endl;
        
        bool semigroup = false, commutative = false;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                {
                    char a = elements[i], b = elements[j], c = elements[k];
                    
                    char left1 = multiplication[i][j];
                    if (location.find(left1) == location.end())
                    {
                        cout << "NOT A SEMIGROUP: " << a << "#" << b << " = " << left1;
                        cout << " WHICH IS NOT AN ELEMENT OF THE SET" << endl;
                        goto exit_processing;
                    }
                    
                    char left2 = multiplication[location[left1]][k];
                    if (location.find(left2) == location.end())
                    {
                        cout << "NOT A SEMIGROUP: " << left1 << "#" << c << " = " << left2;
                        cout << " WHICH IS NOT AN ELEMENT OF THE SET" << endl;
                        goto exit_processing;
                    }
                    
                    char right1 = multiplication[j][k];
                    if (location.find(right1) == location.end())
                    {
                        cout << "NOT A SEMIGROUP: " << b << "#" << c << " = " << right1;
                        cout << " WHICH IS NOT AN ELEMENT OF THE SET" << endl;
                        goto exit_processing;
                    }
                    
                    char right2 = multiplication[i][location[right1]];
                    if (location.find(right2) == location.end())
                    {
                        cout << "NOT A SEMIGROUP: " << a << "#" << right1 << " = " << right2;
                        cout << " WHICH IS NOT AN ELEMENT OF THE SET" << endl;
                        goto exit_processing;
                    }
                    
                    if (left2 != right2)
                    {
                        cout << "NOT A SEMIGROUP: (";
                        cout << a << "#" << b << ")#" << c << " IS NOT EQUAL TO ";
                        cout << a << "#(" << b << "#" << c << ")" << endl;
                        goto exit_processing;
                    }
                    
                }
                
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                char a = elements[i], b = elements[j];
                char left = multiplication[i][j], right = multiplication[j][i];
                
                if (left != right)
                {
                    cout << "SEMIGROUP BUT NOT COMMUTATIVE (";
                    cout << a << "#" << b << " IS NOT EQUAL TO ";
                    cout << b << "#" << a << ")" << endl;
                    goto exit_processing;
                }
            }
            
        cout << "COMMUTATIVE SEMIGROUP" << endl;
            
exit_processing:
        cout << string(30, '-') << endl;
    }
    
	return 0;
}
