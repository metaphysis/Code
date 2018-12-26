#include <bits/stdc++.h>

using namespace std;

int compress(int *x1, int *x2, int w, int n)
{
    vector<int> xs;
    for (int i = 0; i < n; i++)
        for (int d = -1; d <= 1; d++)
        {
            int tx1 = x1[i] + d, tx2 = x2[i] + d;
            if (0 <= tx1 && tx1 < w) xs.push_back(tx1);
            if (0 <= tx2 && tx2 < w) xs.push_back(tx2);
        }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    for (int i = 0; i < n; i++)
    {
        x1[i] = lower_bound(xs.begin(), xs.end(), x1[i]) - xs.begin();
        x2[i] = lower_bound(xs.begin(), xs.end(), x2[i]) - xs.begin();
    }

    return xs.size();
}

int main(int argc, char *argv[])
{
    return 0;
}
