// Creating Palindrome
// UVa ID: 11753
// Verdict: Accepted
// Submission Date: 2017-04-08
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int T, N, K, minK;
vector<int> numbers(10000, 0);
map<pair<int, int>, int> cache;

void findK(int i, int j, int maxK)
{
    if (i >= j || maxK > K)
    {
        minK = min(minK, maxK);
        return;
    }

    int &k = cache[make_pair(i, j)];
    if (k == 0 || maxK < k)
    {
        k = maxK;
        if (numbers[i] == numbers[j])
            findK(i + 1, j - 1, maxK);
        else
        {
            findK(i + 1, j, maxK + 1);
            findK(i, j - 1, maxK + 1);
        }
    }
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
        
        cache.clear();
        minK = 20000;
        findK(0, N - 1, 0);
        
        if (minK > K)
            cout << "Too difficult\n";
        else
            cout << minK << '\n';
    }
    
    return 0;
}
