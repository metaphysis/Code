// Shopping Trip
// UVa ID: 11284
// Verdict: Accepted
// Submission Date: 2018-01-21
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int PINF = 0x3fffffff, NINF = -0x3fffffff;

struct store
{
    int number, profit;
    store (int number = 0, int profit = 0): number(number), profit(profit) {}
    bool operator<(const store &s) const { return number < s.number; }
};

struct state
{
    int ones, bits;
    state (int ones = 0, int bits = 0): ones(ones), bits(bits) {}
    bool operator<(const state &s) const { return ones < s.ones; }
};

void shopping()
{
    int N, M, P, cost[64][64];
    char dot;
    int u, v, price, priceI, priceF;

    cin >> N >> M;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
            cost[i][j] = cost[j][i] = PINF;
        cost[i][i] = 0;
    }
    for (int i = 1; i <= M; i++)
    {
        cin >> u >> v >> priceI >> dot >> priceF;
        price = priceI * 100 + priceF;
        cost[u][v] = min(cost[u][v], price);
        cost[v][u] = min(cost[v][u], price);
    }

    // Floyd-Warshall algorithm.
    for (int k = 0; k <= N; k++)
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    vector<store> stores;
    cin >> P;
    for (int i = 0, number = 0; i < P; i++)
    {
        cin >> number >> priceI >> dot >> priceF;
        stores.push_back(store(number, priceI * 100 + priceF));
    }
    sort(stores.begin(), stores.end());

    vector<state> states;
    int T = (1 << P);
    for (int i = 0; i < T; i++)
        // __builtin_popcount(i) counts the one's in binary bits of a number.
        states.push_back(state(__builtin_popcount(i), i));
    sort(states.begin(), states.end());

    // Initialize.
    int dp[1 << 16][16];
    for (int i = 0; i < T; i++)
        for (int j = 0; j < P; j++)
            dp[i][j] = NINF;

    // DP.
    int maxProfit = NINF;
    for (int i = 0; i < P; i++)
        dp[1 << i][i] = stores[i].profit - cost[0][stores[i].number];

    for (int i = 0; i < T; i++)
    {
        int bits = states[i].bits;
        for (int j = 0; j < P; j++)
        {
            if (dp[bits][j] == NINF) continue;
            u = stores[j].number;
            maxProfit = max(maxProfit, dp[bits][j] - cost[u][0]);
            for (int k = 0; k < P; k++)
            {
                if ((bits >> k) & 1) continue;
                int nextBits = bits | (1 << k);
                v = stores[k].number;
                dp[nextBits][k] = max(dp[nextBits][k], dp[bits][j] - cost[u][v] + stores[k].profit);
            }
        }
    }

    if (maxProfit > 0)
    {
        cout << "Daniel can save $" << (maxProfit / 100);
        cout << '.';
        cout << setw(2) << right << setfill('0') << (maxProfit % 100) << '\n';
    }
    else
    {
        cout << "Don't leave the house\n";
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
        shopping();

    return 0;
}
