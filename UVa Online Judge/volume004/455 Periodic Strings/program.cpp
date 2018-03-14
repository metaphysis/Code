// Periodic Strings
// UVa ID: 455
// Verdict: Accepted
// Submission Date: 2016-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    cin >> n;
    
    string line;
    for (int i = 1; i <= n; i++)
    {
        if (i > 1) cout << endl;
        
        cin >> line;

        bool period_exist = false;
        size_t next = line.find(line.front(), 1);
        while (next != line.npos)
        {
            if (line.length() % next == 0)
            {
                bool is_same = true;
                size_t begin = next;
                while (begin < line.length())
                {
                    for (size_t i = 0; i < next; i++)
                        if (line[i] != line[i + begin])
                        {
                            is_same = false;
                            break;
                        }
                    begin += next;
                }
                
                if (is_same)
                {
                    cout << next << endl;
                    period_exist = true;
                    break;
                }
            }
            next = line.find(line.front(), next + 1);
        }
        if (!period_exist) cout << line.length() << endl;
    }
    
	return 0;
}
