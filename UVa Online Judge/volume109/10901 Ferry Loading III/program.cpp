// Ferry Loading III
// UVa ID: 10901
// Verdict: Accepted
// Submission Date: 2017-02-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010;

struct car
{
    int idx, arrived_time;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int c, n, t, m, arrived_time, unloaded_time[MAXN];
    queue<car> left_bank, right_bank;
    string bank;

    cin >> c;
    for (int i = 0; i < c; i++)
    {
        cin >> n >> t >> m;

        for (int j = 0; j < m; j++)
        {
            cin >> arrived_time >> bank;
            if (bank == "left") left_bank.push((car){j, arrived_time});
            else right_bank.push((car){j, arrived_time});
        }
        
        int current_time = 0, at_left = 1;
        while (true)
        {
            if (left_bank.empty() && right_bank.empty()) break;

            if (at_left)
            {
                int loaded = 0;
                while (!left_bank.empty() && left_bank.front().arrived_time <= current_time && loaded < n)
                {
                    unloaded_time[left_bank.front().idx] = current_time + t;
                    left_bank.pop();
                    loaded += 1;
                }
                
                if (loaded == 0)
                {
                    if (right_bank.empty() || (!left_bank.empty() && left_bank.front().arrived_time <= right_bank.front().arrived_time))
                    {
                        if (current_time < left_bank.front().arrived_time)
                            current_time = left_bank.front().arrived_time;
                    }
                    else
                    {
                        if (right_bank.front().arrived_time > current_time)
                            current_time = right_bank.front().arrived_time + t;
                        else
                            current_time += t;
                        at_left = 0;
                    }
                }
                else
                {
                    current_time += t;
                    at_left = 0;
                }
            }
            else
            {
                int loaded = 0;
                while (!right_bank.empty() && right_bank.front().arrived_time <= current_time && loaded < n)
                {
                    unloaded_time[right_bank.front().idx] = current_time + t;
                    right_bank.pop();
                    loaded += 1;
                }
                
                if (loaded == 0)
                {
                    if (left_bank.empty() || (!right_bank.empty() && right_bank.front().arrived_time <= left_bank.front().arrived_time))
                    {
                        if (current_time < right_bank.front().arrived_time)
                            current_time = right_bank.front().arrived_time;
                    }
                    else
                    {
                        if (left_bank.front().arrived_time > current_time)
                            current_time = left_bank.front().arrived_time + t;
                        else
                            current_time += t;
                        at_left = 1;
                    }
                }
                else
                {
                    current_time += t;
                    at_left = 1;
                }
            }
        }
        
        if (i > 0) cout << '\n';
        for (int j = 0; j < m; j++) cout << unloaded_time[j] << '\n';
    }

    return 0;
}
