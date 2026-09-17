#include <bits/stdc++.h>
using namespace std;

const int MAXL = 200, INF = 0x3f3f3f3f;

vector<pair<int, int>> seg[MAXL];
int pos[101];

void mergeInterval(vector<pair<int, int>> &vec) {
    vector<pair<int, int>> res;
    sort(vec.begin(), vec.end());
    for (int i = 0; i < (int)vec.size(); i++) {
        int l = vec[i].first, r = vec[i].second;
        if (l > r)
            continue;
        if (res.empty() || l > res.back().second + 1)
            res.push_back(make_pair(l, r));
        else
            res.back().second = max(res.back().second, r);
    }
    vec.swap(res);
}

void initialize() {
    string str;
    for (int i = 1; i <= 100; i++) {
        str += to_string(i);
        pos[i] = str.size() - 1;
    }
    int len = str.size();
    for (int i = 0; i < len; i++) {
        vector<pair<int, int>> vec;
        if (i < 5) {
            int x = 0;
            for (int j = 0; j <= i; j++)
                x = x * 10 + str[j] - '0';
            vec.push_back(make_pair(x, x));
            vec.push_back(make_pair(-x, -x));
        }
        int x = 0, p = 1;
        for (int j = i - 1; j >= 0 && i - j <= 5; j--) {
            x = (str[j + 1] - '0') * p + x;
            p *= 10;
            for (int k = 0; k < seg[j].size(); k++) {
                int l = seg[j][k].first, r = seg[j][k].second;
                vec.push_back(make_pair(l + x, r + x));
                vec.push_back(make_pair(l - x, r - x));
                vec.push_back(make_pair(x - r, x - l));
                vec.push_back(make_pair(-r - x, -l - x));
            }
        }
        mergeInterval(vec);
        seg[i].swap(vec);
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < (int)seg[i].size(); j++)
            swap(seg[i][j].first, seg[i][j].second);
    }
}

bool validate(int n, int m) {
    vector<pair<int, int>> &vec = seg[pos[n]];
    pair<int, int> key = make_pair(m, -INF);
    int id = (lower_bound(vec.begin(), vec.end(), key) - vec.begin());
    if (id == vec.size()) return false;
    return vec[id].second <= m && m <= vec[id].first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initialize();
    int n, m;
    while (cin >> n >> m) {
        if (validate(n, m)) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}
