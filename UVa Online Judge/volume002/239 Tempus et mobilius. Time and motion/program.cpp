// Tempus et mobilius. Time and motion
// UVa ID: 239
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long gcd(long long x, long long y)
{
    long long t;
    while (x % y)
    {
        t = x;
        x = y;
        y = t % y;
    }
    return y;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        queue<int> balls;
        stack<int> minute, five, hour;
        
        for (int i = 0; i < n; i++)
            balls.push(i);
            
        for (int i = 0; i < 24 * 60; i++)
        {
            int ball = balls.front();
            balls.pop();
            
            if(minute.size() < 4)
                minute.push(ball);
            else
            {
                while (minute.empty() == false)
                {
                    balls.push(minute.top());
                    minute.pop();
                }
                    
                if (five.size() < 11)
                    five.push(ball);
                else
                {
                    while (five.empty() == false)
                    {
                        balls.push(five.top());
                        five.pop();
                    }
                        
                    if (hour.size() < 11)
                        hour.push(ball);
                    else
                    {
                        while (hour.empty() == false)
                        {
                            balls.push(hour.top());
                            hour.pop();
                        }
                        
                        balls.push(ball);
                    }
                }
            }
        }

        int permutation[7010], visited[7010] = {};

        for (int i = 0; i < n; i++)
        {
            permutation[i] = balls.front();
            balls.pop();
        }
            
        long long days = 1;
        for (int i = 0; i < n; i++)
            if (visited[i] == 0)
            {
                int length = 1;
                visited[i] = 1;
                
                for (int j = permutation[i]; j != i; j = permutation[j])
                {
                    visited[j] = 1;
                    length++;
                }
                
                days = days / gcd(days, length) * length;
            }

        cout << n << " balls cycle after " << days << " days.\n";
    }

    return 0;
}
