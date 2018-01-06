// The Lonesome Cargo Distributor
// UVa ID: 10172
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 110;

int size(int head, int rear)
{
    if (rear >= head) return rear - head;
    return rear + MAXN - head;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, S, Q, Qi, ID;
    int carrier[MAXN], top, platform[MAXN][MAXN], head[MAXN], rear[MAXN];
    int undelivered = 0, minutes, firstRun;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        memset(head, 0, sizeof(head));
        memset(rear, 0, sizeof(rear));

        cin >> N >> S >> Q;
        for (int i = 0; i < N; i++)
        {
            cin >> Qi;
            undelivered += Qi;
            for (int j = 0; j < Qi; j++)
            {
                cin >> ID;
                platform[i][rear[i]++] = ID - 1;
            }
        }

        top = 0, minutes = 0, firstRun = 1;

        while (undelivered > 0)
        {
            for (int i = 0; i < N; i++)
            {
                // Is it the first operation?
                if (firstRun) firstRun = 0; else minutes += 2;
            
                // Unloading.
                while (top > 0)
                {
                    if (carrier[top - 1] != i)
                    {
                        // Is Platform B full?
                        if (size(head[i], rear[i]) == Q) break;
                        platform[i][rear[i]] = carrier[top - 1];
                        rear[i] = (rear[i] + 1) % MAXN;
                    }
                    else undelivered--;

                    top--;
                    minutes++;
                }

                // Loading.
                while (top < S)
                {
                    if (size(head[i], rear[i]) > 0)
                    {
                        carrier[top] = platform[i][head[i]];
                        top++;
                        head[i] = (head[i] + 1) % MAXN;
                        minutes++;
                    }
                    else break;
                }
                
                // Is the job finished?
                if (undelivered == 0) break;
            }
        }

        cout << minutes << '\n';
    }

    return 0;
}
