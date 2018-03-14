// Puzzle (II)
// UVa ID: 519
// Verdict: Accepted
// Submission Date: 2017-05-01
// UVa Run Time: 0.160s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct piece
{
    int top, right, bottom, left, hash;

    void getSide(string &description)
    {
        top = description[0] == 'O' ? 1 : (description[0] == 'I' ? 2 : 0);
        right = description[1] == 'O' ? 1 : (description[1] == 'I' ? 2 : 0);
        bottom = description[2] == 'O' ? 1 : (description[2] == 'I' ? 2 : 0);
        left = description[3] == 'O' ? 1 : (description[3] == 'I' ? 2 : 0);
        hash = top * 1000 + right * 100 + bottom * 10 + left;
    }
    
    // more similar, more closer.
    bool operator < (const piece &x) const
    {
        return hash < x.hash;
    }
};

piece pieces[40];
int grid[10][10], used[40], n, m, t;
string description;
bool successful = false;

bool check()
{
    int topLeftFlat = 0, topRightFlat = 0, bottomLeftFlat = 0, bottomRightFlat = 0;
    int topFlat = 0, rightFlat = 0, bottomFlat = 0, leftFlat = 0, noneFlat = 0;

    for (int i = 0; i < t; i++)
    {
        if (pieces[i].top == 0 && pieces[i].left == 0) topLeftFlat++;
        if (pieces[i].top == 0 && pieces[i].right == 0) topRightFlat++;
        if (pieces[i].bottom == 0 && pieces[i].left == 0) bottomLeftFlat++;
        if (pieces[i].bottom == 0 && pieces[i].right == 0) bottomRightFlat++;
        if (pieces[i].top == 0) topFlat++;
        if (pieces[i].right == 0) rightFlat++;
        if (pieces[i].bottom == 0) bottomFlat++;
        if (pieces[i].left == 0) leftFlat++;
        if (pieces[i].top != 0 && pieces[i].right != 0 && pieces[i].bottom != 0 && pieces[i].left != 0) noneFlat++;
    }
    
    if (topLeftFlat != 1 || topRightFlat != 1 || bottomLeftFlat != 1 || bottomRightFlat != 1) return false;
    if (topFlat != m || bottomFlat != m) return false;
    if (leftFlat != n || rightFlat != n) return false;
    if (n >= 2 && m >= 2 && noneFlat != (n - 2) * (m - 2)) return false;

    return true;
}

bool validate(int i, int j, int k)
{
    if (i == 0 && pieces[k].top != 0) return false;
    if (i == (n - 1) && pieces[k].bottom != 0) return false;
    if (j == 0 && pieces[k].left != 0) return false;
    if (j == (m - 1) && pieces[k].right != 0) return false;
    if (i > 0 && (pieces[k].top + pieces[grid[i - 1][j]].bottom) != 3) return false;
    if (j > 0 && (pieces[k].left + pieces[grid[i][j - 1]].right) != 3) return false;

    return true;
}

void backtrack(int i, int j)
{
    if (i == n) successful = true;
    else
    {
        for (int k = 0; k < t; k++)
            if (!used[k] && (k == 0 || used[k - 1] || pieces[k].hash != pieces[k - 1].hash) && validate(i, j, k))
            {
                used[k] = 1;
                grid[i][j] = k;

                if (j + 1 == m) backtrack(i + 1, 0);
                else backtrack(i, j + 1);

                if (successful) return;

                used[k] = 0;
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m, n > 0)
    {
        t = n * m;
        for (int i = 0; i < t; i++)
        {
            cin >> description;
            pieces[i].getSide(description);
        }
        
        successful = false;
        if (check())
        {
            sort(pieces, pieces + t);
            memset(used, 0, sizeof(used));   
            backtrack(0, 0);
        }

        cout << (successful ? "YES" : "NO") << '\n';
    }

    return 0;
}
