#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8;

int column[MAXN] = {0}, used[MAXN] = {0};

bool safe()
{
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

void render()
{
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
            cout << (column[i] == j ? " Q" : " *");
        cout << '\n';
    }
    cout << '\n';
}

int dfs(int depth)
{
    if (depth == MAXN && safe()) { render(); return 1; }

    int cnt = 0;
    for (int i = 0; i < MAXN; i++)
        if (!used[i]) {
            used[i] = 1, column[depth] = i;
            cnt += dfs(depth + 1);
            used[i] = 0, column[depth] = -1;
        }
    return cnt;
}


int main(int argc, char *argv[])
{
    cout << dfs(0) << '\n';
    return 0;
}
