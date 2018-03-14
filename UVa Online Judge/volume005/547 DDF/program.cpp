// DDF
// UVa ID: 547
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int digit_sum[3100], next_number[3100], length[3100] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    for (int i = 1; i <= 3000; i++)
    {
        int digit = 0, t = i;
        while (t)
        {
            digit += t % 10;
            t /= 10;
        }
        digit_sum[i] = digit;
    }
    
    for (int i = 1; i <= 3000; i++)
    {
        int next = 0;
        for (int j = 1; j <= sqrt(i); j++)
        {
            if ((i % j) == 0)
            {
                int b = i / j;
                next += digit_sum[j];
                if (b != j)
                    next += digit_sum[b];
            }
        }
        next_number[i] = next;
    }
    
    for (int i = 1; i <= 3000; i++)
    {
        if (length[next_number[i]] > 0)
            length[i] = 1 + length[next_number[i]];
        else
        {
            int step = 1, start = i;
            while (next_number[start] != start)
            {
                step++;
                start = next_number[start];
            }
            length[i] = step;
        }
    }

    int m, n, cases = 0;
    while (cin >> m >> n)
    {
        cases++;
        cout << "Input" << cases << ": " << m << ' ' << n << '\n';
        
        int start = min(m, n), end = max(m, n), max_i, max_length = 0;
        for (int i = start; i <= end; i++)
            if (length[i] > max_length)
            {
                max_i = i;
                max_length = length[i];
            }
        
        cout << "Output" << cases << ": " << max_i;
        while (next_number[max_i] != max_i)
        {
            max_i = next_number[max_i];
            cout << ' ' << max_i;
        }

        cout << '\n';
    }
    
	return 0;
}
