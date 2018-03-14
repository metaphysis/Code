// Self Numbers
// UVa ID: 640
// Verdict: Accepted
// Submission Date: 2016-08-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int number[1000001] = { 0 };

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    number[1] = 0;
    for (int i = 1; i <= 1000000; i++)
    {
        if (number[i] == 0)
        {
            cout << i << '\n';

            int start = i;
            while (start < 1000000)
            {
                int next = start;
                while (start > 0)
                {
                    next += start % 10;
                    start /= 10;
                }
                
                if (next <= 1000000)
                {
                    if (number[next] == 1)
                        break;

                    number[next] = 1;
                    start = next;
                }
                else
                    break;
            }
        }
    }
    
	return 0;
}
