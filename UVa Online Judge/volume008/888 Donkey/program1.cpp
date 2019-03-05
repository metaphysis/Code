// Donkey
// UVa ID: 888
// Verdict: Wrong Answer
// Submission Date: 2019-03-05
// UVa Run Time: 0.180s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int M, N;
double dp2[2][26][26][26];
double dp3[3][17][17][17][17];
double dp4[4][13][13][13][13][13];

double dfs2(int who, int p1, int p2)
{
    if (p1 > M) return 1.0;
    if (p2 > M) return 0.0;
    if (dp2[who][M][p1][p2] >= 0) return dp2[who][M][p1][p2];
    double r = 0;
    for (int die = 1; die <= 6; die++)
    {
        int np1 = p1, np2 = p2;
        if (who == 0)
        {
            np1 += die;
            if (np1 == np2) np1++;
        }
        else
        {
            np2 += die;
            if (np2 == np1) np2++;
        }
        r += dfs2((who + 1) % N, np1, np2) / 6.0;
    }
    return dp2[who][M][p1][p2] = r;
}

double dfs3(int who, int p1, int p2, int p3)
{
    if (p1 > M) return 1.0;
    if (p2 > M || p3 > M) return 0.0;
    if (dp3[who][M][p1][p2][p3] >= 0) return dp3[who][M][p1][p2][p3];
    double r = 0;
    for (int die = 1; die <= 6; die++)
    {
        int np1 = p1, np2 = p2, np3 = p3;
        if (who == 0)
        {
            np1 += die;
            while (np1 == np2 || np1 == np3) np1++;
        }
        else if (who == 1)
        {
            np2 += die;
            while (np2 == np1 || np2 == np3) np2++;
        }
        else
        {
            np3 += die;
            while (np3 == np1 || np3 == np2) np3++;
        }
        r += dfs3((who + 1) % N, np1, np2, np3) / 6.0;
    }
    return dp3[who][M][p1][p2][p3] = r;
}

double dfs4(int who, int p1, int p2, int p3, int p4)
{
    if (p1 > M) return 1.0;
    if (p2 > M || p3 > M || p4 > M) return 0.0;
    if (dp4[who][M][p1][p2][p3][p4] >= 0) return dp4[who][M][p1][p2][p3][p4];
    double r = 0;
    for (int die = 1; die <= 6; die++)
    {
        int np1 = p1, np2 = p2, np3 = p3, np4 = p4;
        if (who == 0)
        {
            np1 += die;
            while (np1 == np2 || np1 == np3 || np1 == np4) np1++;
        }
        else if (who == 1)
        {
            np2 += die;
            while (np2 == np1 || np2 == np3 || np2 == np4) np2++;
        }
        else if (who == 2)
        {
            np3 += die;
            while (np3 == np1 || np3 == np2 || np3 == np4) np3++;
        }
        else
        {
            np4 += die;
            while (np4 == np1 || np4 == np2 || np4 == np3) np4++;
        }
        r += dfs4((who + 1) % N, np1, np2, np3, np4) / 6.0;
    }
    return dp4[who][M][p1][p2][p3][p4] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 26; j++)
            for (int d1 = 0; d1 < 26; d1++)
                for (int d2 = 0; d2 < 26; d2++)
                    dp2[i][j][d1][d2] = -1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 17; j++)
            for (int d1 = 0; d1 < 17; d1++)
                for (int d2 = 0; d2 < 17; d2++)
                    for (int d3 = 0; d3 < 17; d3++)
                        dp3[i][j][d1][d2][d3] = -1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 13; j++)
            for (int d1 = 0; d1 < 13; d1++)
                for (int d2 = 0; d2 < 13; d2++)
                    for (int d3 = 0; d3 < 13; d3++)
                        for (int d4 = 0; d4 < 13; d4++)
                            dp4[i][j][d1][d2][d3][d4] = -1;                    
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Game " << cs << ":the probability that player 1 wins = ";
        cin >> M >> N;
        int river[4], who;
        for (int i = 0; i < N; i++) cin >> river[i];
        cin >> who;
        
        if (N == 1) cout << "1.000\n";
        else
        {
            double r;
            if (N == 2) r = dfs2(who - 1, river[0], river[1]);
            else if (N == 3) r = dfs3(who - 1, river[0], river[1], river[2]);
            else r = dfs4(who - 1, river[0], river[1], river[2], river[3]);
            cout << fixed << setprecision(3) << r << '\n';
        }
    }

    return 0;
}
