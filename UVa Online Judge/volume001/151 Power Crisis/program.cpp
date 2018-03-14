// Power Crisis
// UVa ID: 151
// Verdict: Accepted
// Submission Date: 2016-02-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, region[101];

int findCW(int index, int count)
{
    for (int i = index; i < n; i++)
        if (region[i] > 0 && ((--count) == 0))
            return i;

    while (true)
    {
        for (int i = 0; i < n; i++)
            if (region[i] > 0 && ((--count) == 0))
                return i;
    }
}

int findRegion()
{
    for (int i = 0; i < n; i++)
        if (region[i] > 0)
            return region[i];
}

int main(int argc, char* argv[])
{
    while (cin >> n, n)
    {
        int m = 0;
        while (true)
        {
            for (int i = 1; i <= n; i++)
                region[i - 1] = i;
            
            int total = n, blacked = 0;
            bool found = true;
            
            m++;
            while (total > 1)
            {
                if (region[blacked] == 13)
                {
                    found = false;
                    break;
                }

                region[blacked] = 0;
                total--;

                blacked = (blacked + 1) % n;
                blacked = findCW(blacked, m);
            }
            
            if (found)
                break;
        }
        
        cout << m << endl;
    }
    
    return 0;
}
