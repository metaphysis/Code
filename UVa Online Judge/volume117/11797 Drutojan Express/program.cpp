// Drutojan Express
// UVa ID: 11797
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getIndex(string name)
{
    if (name == "Ja") return 0;
    if (name == "Sam") return 1;
    if (name == "Sha") return 2;
    if (name == "Sid") return 3;
    if (name == "Tan") return 4;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        int time[5] = {0};
        queue<int> list[5];
        int M, N;
        string name;
        cin >> M >> N >> name;
        int idx = getIndex(name);
        for (int i = 0, k; i < 5; i++)
        {
            cin >> k;
            for (int j = 0; j < k; j++)
            {
                cin >> name;
                list[i].push(getIndex(name));
            }
        }
        int m = 0;
        while (m < N)
        {
            if (m + M <= N) time[idx] += M;
            else time[idx] += N - m;
            m += M;
            if (m + 2 >= N) break;
            m += 2;
            list[idx].push(list[idx].front());
            list[idx].pop();
            idx = list[idx].back();
        }
        cout << "Case " << cs << ":\n";
        cout << "Ja " << time[0] << '\n';
        cout << "Sam " << time[1] << '\n';
        cout << "Sha " << time[2] << '\n';
        cout << "Sid " << time[3] << '\n';
        cout << "Tan " << time[4] << '\n';
    }
    return 0;
}
