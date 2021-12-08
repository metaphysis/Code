// A Digital Satire of Digital Age
// UVa ID: 12280
// Verdict: Accepted
// Submission Date: 2021-12-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string g1[28] = {
    "........||.../\\...",
    "........||../..\\..",
    ".../\\...||./....\\.",
    "../..\\..||/......\\",
    "./....\\.||\\______/",
    "/......\\||........",
    "\\______/||........",
    "........||........",
    ".../\\...||.../\\...",
    "../..\\..||../..\\..",
    "./....\\.||./....\\.",
    "/......\\||/......\\",
    "\\______/||\\______/",
    "........||........",
    ".../\\...||........",
    "../..\\..||........",
    "./....\\.||.../\\...",
    "/......\\||../..\\..",
    "\\______/||./....\\.",
    "........||/......\\",
    "........||\\______/",
    "..................",
    "..................",
    "..................",
    "..................",
    "..................",
    "..................",
    ".................."
    };

    string g2[7] = {
    "..................",
    "..................",
    "..................",
    "..................",
    "..................",
    "..................",
    ".................."
    };

    map<char, int> weights;
    for (int i = 'A'; i <= 'Z'; i++)
    {
        int gm = 0;
        for (int j = 7; j >= 0; j--)
            if (i & (1 << j))
            {
                for (int k = j; k >= 0; k--)
                {
                    if (i & (1 << k)) gm += 500;
                    else gm += 250;
                }
                break;
            }
        weights[char(i)] = gm;
    }

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ":\n";
        int gm1 = 0, gm2 = 0;
        string s1, s2, line;
        for (int i = 0; i < 7; i++)
        {
            cin >> g2[i];
            for (int j = 0; j < g2[i].size(); j++)
            {
                if (g2[i][j] >= 'A' && g2[i][j] <= 'Z')
                {
                    if (j < 9) { s1 += g2[i][j]; gm1 += weights[g2[i][j]]; }
                    else { s2 += g2[i][j]; gm2 += weights[g2[i][j]]; }
                }
            }
        }
        cin >> line;
        if (gm1 > gm2)
        {
            for (int i = 0; i < 7; i++) g1[i + 21] = g1[i];
            for (int i = 0; i < s1.size(); i++) g1[26][i + 1] = s1[i];
            for (int i = 0; i < s2.size(); i++) g1[24][i + 11] = s2[i];
        }
        else if (gm1 == gm2)
        {
            for (int i = 7; i < 14; i++) g1[i + 14] = g1[i];
            for (int i = 0; i < s1.size(); i++) g1[25][i + 1] = s1[i];
            for (int i = 0; i < s2.size(); i++) g1[25][i + 11] = s2[i];
        }
        else
        {
            for (int i = 14; i < 21; i++) g1[i + 7] = g1[i];
            for (int i = 0; i < s1.size(); i++) g1[24][i + 1] = s1[i];
            for (int i = 0; i < s2.size(); i++) g1[26][i + 11] = s2[i];
        }
        bool same = true;
        for (int i = 0; i < 7 && same; i++)
            if (g1[i + 21] != g2[i])
                same = false;
        if (same) cout << "The figure is correct.\n";
        else
        {
            for (int i = 0; i < 7; i++)
                cout << g1[i + 21] << '\n';
        }
    }
    return 0;
}
