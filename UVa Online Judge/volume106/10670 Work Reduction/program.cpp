// Work Reduction
// UVa ID: 10670
// Verdict: Accepted
// Submission Date: 2017-10-14
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct agent
{
    string name;
    long long cost;

    bool operator<(const agent &a) const
    {
        if (cost == a.cost) return name < a.name;
        else return cost < a.cost;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, L;
    long long N, M;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        vector<agent> agencies;

        cin >> N >> M >> L;
        cin.ignore(1024, '\n');
        for (int i = 1; i <= L; i++)
        {
            string line;
            getline(cin, line);
            
            string next;
            for (int i = 0; i < line.length(); i++)
            {
                if (isblank(line[i])) continue;
                if (line[i] == ':')
                    next += ',';
                else
                    next += line[i];
            }
            
            istringstream iss(next);

            string name, A, B;
            getline(iss, name, ',');
            getline(iss, A, ',');
            getline(iss, B, ',');
            
            long long feeA = stoi(A), feeB = stoi(B);
            long long cost = 0;

            // greed algorithm.
            long long backupN = N;
            while (N > M)
            {
                long long nextN = N / 2;
                if (nextN < M)
                {
                    N--;
                    cost += feeA;
                }
                else
                {
                    if ((N - nextN) * feeA > feeB)
                        cost += feeB;
                    else
                        cost += (N - nextN) * feeA;
                    N = nextN;
                }
            }
            N = backupN;
            agencies.push_back(agent{name, cost});
        }

        sort(agencies.begin(), agencies.end());

        cout << "Case " << c << '\n';
        for (auto a : agencies)
            cout << a.name << ' ' << a.cost << '\n';
    }

    return 0;
}
