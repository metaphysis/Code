// Creating Palindrome
// UVa ID: 11753
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

int T, N, K;
bool finished = false;
vector<int> numbers(10000, 0);
map<long long, int> cache;

int findK(int i, int j, int maxK)
{
    if (finished)
        return 0;
        
    if (maxK > K)
    {
        finished = true;
        return 0;
    }
    
    if (i >= j) return 0;
    
    long long interval = i * 100000 + j;
    if (cache.find(interval) != cache.end())
    {
        return cache[interval];
    }
    
    int k = 20000;
    if (numbers[i] == numbers[j])
        k = findK(i + 1, j - 1, maxK);
    else
        k = min(2 + findK(i + 1, j - 1, maxK + 1), 1 + min(findK(i + 1, j, maxK + 1), findK(i, j - 1, maxK + 1)));
    
    cache[interval] = k;
    return k;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> T;
    
    for (int c = 1; c <= T; c++)
    {
        cout << "Case " << c << ": ";

        cin >> N >> K;
        
        for (int i = 0; i < N; i++)
            cin >> numbers[i];
            
        bool isPalindrome = true;
        for (int x = 0, y = N - 1; x <= y; x++, y--)
            if (numbers[x] != numbers[y])
            {
                isPalindrome = false;
                break;
            }
        if (isPalindrome)
        {
            cout << "Too easy\n";
            continue;
        }
        
        finished = false;
        cache.clear();
        int k = findK(0, N - 1, 0);
        
        if (finished)
            cout << "Too difficult\n";
        else
            cout << k << '\n';
    }
    
    return 0;
}
