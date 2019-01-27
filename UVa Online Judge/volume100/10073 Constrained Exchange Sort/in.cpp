#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    vector<int> offset[13];
    int di[4] = {1, 3, 6, 12};
    for (int i = 1; i <= 12; i++)
        for (int j = 0; j <= 2; j++)
        {
            int nextd = i + di[j];
            if (nextd >= 1 && nextd <= 12)
                if ((i - 1) / di[j + 1] == (nextd - 1) / di[j + 1])
                    offset[i].push_back(nextd);
            nextd = i - di[j];
            if (nextd >= 1 && nextd <= 12)
                if ((i - 1) / di[j + 1] == (nextd - 1) / di[j + 1])
                    offset[i].push_back(nextd);
        }

    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        string s = "ABCDEFGHIJKL";
        int idx = 12, lastIdx = 12;
        for (int i = 1; i <= 30; i++)
        {
            int nextd = offset[idx][rand() % offset[idx].size()];
            while (nextd == lastIdx)
                nextd = offset[idx][rand() % offset[idx].size()];
            swap(s[idx - 1], s[nextd - 1]);
            lastIdx = idx;
            idx = nextd;
        }
        cout << s << '\n';
    }
    
    return 0;
}
