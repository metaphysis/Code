// Sum-up the Primes (II)
// UVa ID: 10447
// Verdict:
// Submission Date:
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[301] = {}, cnt = 0;
int Q, N, T, B;
int marked[256][801][13], cache[256], nexti[256];
vector<int> backup, available;

bool dfs(int idx, int sum, int used)
{
    if (sum > N || idx == available.size()) return false;

    if (used == T)
    {
        if (sum == N) return true;
        return false;
    }

    if (marked[idx][sum][used]) return false;
    cache[used] = available[idx];

    if (sum + available[idx] > N) idx = nexti[idx];
    if (idx == -1) return false;
    if (dfs(idx + 1, sum + available[idx], used + 1)) return true;
    if (dfs(idx + 1, sum, used)) return true;

    marked[idx][sum][used] = 1;
    return false;
}

bool cmp(int a, int b)
{
    return to_string(a) < to_string(b);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i <= 300; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }

    int blocks;
    cin >> blocks;
    for (int bs = 1; bs <= blocks; bs++)
    {
        backup.clear();
        int f;
        cout << "Block " << bs << ":\n";
        for (int i = 1; i <= 61; i++)
        {
            cin >> f;
            for (int j = 1; j <= f; j++)
                backup.push_back(primes[i]);
        }

        cin >> Q;
        for (int q = 1; q <= Q; q++)
        {
            available.assign(backup.begin(), backup.end());
            cin >> N >> T >> B;
            if (B) available.push_back(2);

            cout << "Query " << q << ":\n";
            if (N == 0 || T == 0)
            {
                cout << "No Solution.\n";
                continue;
            }

            for (int i = 0; i <= available.size(); i++)
                for (int j = 0; j <= N; j++)
                    for (int k = 0; k <= T; k++)
                        marked[i][j][k] = 0;

            sort(available.begin(), available.end(), cmp);

            memset(nexti, -1, sizeof(nexti));
            for (int i = 0; i < available.size(); i++)
            {
                for (int j = i; j < available.size(); j++)
                    if (available[j] < available[i])
                    {
                        nexti[i] = j;
                        break;
                    }
            }

            if (dfs(0, 0, 0))
            {
                for (int i = 0; i < T; i++)
                {
                    if (i) cout << '+';
                    cout << cache[i];
                }
                cout << '\n';
            }
            else cout << "No Solution.\n";
        }
        cout << '\n';
    }

    return 0;
}
