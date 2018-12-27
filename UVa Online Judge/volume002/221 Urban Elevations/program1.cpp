// Urban Elevations
// UVa ID: 221
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct building
{
    int index;
    double left, bottom, width, depth, height;
    bool operator<(const building &b) const
    {
        if (left != b.left) return left < b.left;
        return bottom < b.bottom;
    }
};

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        vector<building> bs(n);
        vector<double> xs;

        for (int i = 0; i < n; i++)
        {
            cin >> bs[i].left >> bs[i].bottom >> bs[i].width >> bs[i].depth >> bs[i].height;
            bs[i].index = i + 1;
            xs.push_back(bs[i].left);
            xs.push_back(bs[i].left + bs[i].width);
        }

        if (cases++) cout << '\n';

        cout << "For map #" << cases;
        cout << ", the visible buildings are numbered as follows:" << '\n';

        sort(bs.begin(), bs.end());
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        for (int i = 0, printed = 0; i < n; i++)
        {
            bool visible = false;
            for (int j = 0; j < xs.size() - 1; j++)
            {
                double middle = (xs[j] + xs[j + 1]) / 2;
                if (bs[i].left <= middle && bs[i].left + bs[i].width >= middle)
                {
                    bool covered = false;
                    for (int k = 0; k < n; k++)
                        if (bs[k].left <= middle && bs[k].left + bs[k].width >= middle)
                            if (bs[k].bottom < bs[i].bottom && bs[k].height >= bs[i].height)
                            {
                                covered = true;
                                break;
                            }
                    if (!covered)
                    {
                        visible = true;
                        break;
                    }
                }
            }
            if (visible)
            {
                if (printed++) cout << ' ';
                cout << bs[i].index;
            }
        }
        cout << '\n';
    }

    return 0;
}
