const int MAXV = 210;

int main(int argc, char *argv[])
{
    int n;
    int x1[MAXV], y1[MAXV], x2[MAXV], y2[MAXV];

    while (cin >> n)
    {
        vector<int> xs, ys;
        for (int i = 0; i < n; i++)
        {
            cin >> x1[i] >> y1[i];
            cin >> x2[i] >> y2[i];
            xs.push_back(x1[i]); xs.push_back(x2[i]);
            ys.push_back(y1[i]); ys.push_back(y2[i]);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (int i = 0; i < n; i++)
        {
            x1[i] = lower_bound(xs.begin(), xs.end(), x1[i]) - xs.begin();
            x2[i] = lower_bound(xs.begin(), xs.end(), x2[i]) - xs.begin();
            y1[i] = lower_bound(ys.begin(), ys.end(), y1[i]) - ys.begin();
            y2[i] = lower_bound(ys.begin(), ys.end(), y2[i]) - ys.begin();
        }

        int g[2 * n][2 * n] = {};
        for (int c = 0; c < n; c++)
            for (int i = x1[c]; i < x2[c]; i++)
                for (int j = y1[c]; j < y2[c]; j++)
                        g[i][j]++;

        int area = 0;
        for (int i = 0; i < 2 * n - 1; i++)
            for (int j = 0; j < 2 * n - 1; j++)
                if (g[i][j] >= 2)
                    area += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
        cout << area << '\n';
    }

    return 0;
}
