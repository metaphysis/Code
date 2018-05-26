#include <bits/stdc++.h>

using namespace std;

const int MAXV = 8;

int column[MAXV] = {0}, used[MAXV] = {0}, solutions = 0;

bool safe()
{
    for (int i = 0; i < MAXV; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

void display()
{
    for (int i = 0; i < MAXV; i++)
    {
        for (int j = 0; j < MAXV; j++)
            cout << (column[i] == j ? " Q" : " *");
        cout << '\n';
    }
    cout << '\n';
}

void backtrack(int depth)
{
    if (depth == MAXV && safe()) {
        display();
        solutions++;
        return;
    }

    for (int i = 0; i < MAXV; i++) if (!used[i]) {
        used[i] = 1, column[depth] = i;
        backtrack(depth + 1);
        used[i] = 0;
    }
}


int main(int argc, char *argv[])
{
    solutions = 0;
    backtrack(0);
    cout << solutions << '\n';

    return 0;
}
