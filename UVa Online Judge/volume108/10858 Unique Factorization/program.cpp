// Unique factorsization
// UVa ID: 10858
// Verdict: Accepted
// Submission Date: 2018-01-14
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

const int MAXN = 2500;
int primes[MAXN], cnt;
    
void sieve(int *primes, int n, int &cnt)
{
    cnt = 0, memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

bool operator < (vector<int> &a, vector<int> &b)
{
    for (int i = 0; i < a.size() && i < b.size(); i++)
        if (a[i] != b[i])
            return a[i] < b[i];
    return a.size() > b.size();
}

bool operator == (vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

vector<vector<int>> generate(vector<int> factors)
{
    vector<vector<int>> all;
    vector<vector<int>> children;
    vector<vector<int>> mother;

    all.push_back(factors);
    mother.push_back(factors);
        
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < mother.size(); i++)
        {
            if (mother[i].size() <= 2) continue;
            for (int j = 0; j < mother[i].size(); j++)
                for (int k = j + 1; k < mother[i].size(); k++)
                {
                    vector<int> v(mother[i]);
                    int nj = mother[i][j], nk = mother[i][k];
                    v.erase(v.begin() + k);
                    v.erase(v.begin() + j);
                    v.push_back(nj * nk);
                    sort(v.begin(), v.end());
                    children.push_back(v);
                }
            updated = true;
        }

        mother.clear();
        sort(children.begin(), children.end());
        children.erase(unique(children.begin(), children.end()), children.end());
        for (auto t : children)
        {
            all.push_back(t);
            mother.push_back(t);
        }
        children.clear();

        if (!updated) break;
    }
    
    return all;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    sieve(primes, MAXN, cnt);

    int n;
    while (cin >> n, n > 0)
    {
        vector<int> factors;
        for (int i = 0; i < cnt; i++)
        {
            while (n % primes[i] == 0)
            {
                factors.push_back(primes[i]);
                n /= primes[i];
            }
        }
        if (n > 1) factors.push_back(n);
        if (factors.size() <= 1) cout << "0\n";
        else if (factors.size() == 2)
        {
            cout << "1\n";
            cout << factors.front() << ' ' << factors.back() << '\n';
        }
        else
        {
            vector<vector<int>> all = generate(factors);
            
            sort(all.begin(), all.end());
            all.erase(unique(all.begin(), all.end()), all.end());
            cout << all.size() << '\n';
            for (auto sequence : all)
            {
                for (int i = 0; i < sequence.size(); i++)
                {
                    if (i) cout << ' ';
                    cout << sequence[i];
                }
                cout << '\n';
            }
        }
    }

    return 0;
}
