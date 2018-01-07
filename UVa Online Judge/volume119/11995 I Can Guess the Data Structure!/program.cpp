// I Can Guess the Data Structure!
// UVa ID: 11995
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        int command, x;
        stack<int> s; queue<int> q; priority_queue<int, vector<int>, less<int>> pq;
        bool isStack = true, isQueue = true, isPriorityQueue = true;
        for (int i = 1; i <= n; i++)
        {
            cin >> command >> x;
            if (command == 1)
            {
                s.push(x); q.push(x); pq.push(x);
            }
            else
            {
                if (isStack)
                {
                    if (s.empty() || s.top() != x) isStack = false;
                    else s.pop();
                }
                
                if (isQueue)
                {
                    if (q.empty() || q.front() != x) isQueue = false;
                    else q.pop();
                }
                
                if (isPriorityQueue)
                {
                    if (pq.empty() || pq.top() != x) isPriorityQueue = false;
                    else pq.pop();
                }
            }
        }
        
        if (isStack && !isQueue && !isPriorityQueue) cout << "stack\n";
        else if (!isStack && isQueue && !isPriorityQueue) cout << "queue\n";
        else if (!isStack && !isQueue && isPriorityQueue) cout << "priority queue\n";
        else if (!isStack && !isQueue && !isPriorityQueue) cout << "impossible\n";
        else cout << "not sure\n";
    }

    return 0;
}
