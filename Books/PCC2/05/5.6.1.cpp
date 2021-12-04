#include <bits/stdc++.h>

using namespace std;

vector<int> multiply(vector<int> &a, vector<int> &b)
{
    vector<int> c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    return c;
}

int main(int argc, char *argv[])
{
    return 0;
}
