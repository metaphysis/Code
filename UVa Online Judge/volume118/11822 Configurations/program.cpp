#include <bits/stdc++.h>
using namespace std;

const int Mod = 12345;
const int MaxLog = 31;

struct Config {
    int c, m, d;
    vector<int> states;
    vector<vector<int> > edges;
    vector<vector<vector<int> > > power;
    bool ready;
    Config() : c(0), m(0), d(0), ready(false) {}
};

map<pair<int, int>, Config> configs;

vector<vector<int> > multiplyMatrix(const vector<vector<int> >& a, const vector<vector<int> >& b) {
    int n = a.size();
    vector<vector<int> > c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (a[i][k])
                for (int j = 0; j < n; j++)
                    if (b[k][j])
                        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % Mod;
    return c;
}

void enumerateMove(Config& config, int source, const vector<int>& columns, int index, int target) {
    if (index == (int)columns.size()) {
        int targetIndex = lower_bound(config.states.begin(), config.states.end(), target) - config.states.begin();
        config.edges[source].push_back(targetIndex);
        return;
    }
    int column = columns[index];
    if (column > 0 && !(target & (1 << (column - 1))))
        enumerateMove(config, source, columns, index + 1, target | (1 << (column - 1)));
    if (column + 1 < config.c && !(target & (1 << (column + 1))))
        enumerateMove(config, source, columns, index + 1, target | (1 << (column + 1)));
}

Config& getConfig(int c, int m) {
    pair<int, int> key = make_pair(c, m);
    if (configs[key].ready)
        return configs[key];
    Config& config = configs[key];
    config.c = c;
    config.m = m;
    for (int mask = 0; mask < (1 << c); mask++)
        if (__builtin_popcount(mask) == m)
            config.states.push_back(mask);
    config.d = config.states.size();
    config.edges.resize(config.d);
    for (int i = 0; i < config.d; i++) {
        vector<int> columns;
        for (int j = 0; j < c; j++)
            if (config.states[i] & (1 << j))
                columns.push_back(j);
        enumerateMove(config, i, columns, 0, 0);
    }
    vector<vector<int> > base(config.d, vector<int>(config.d, 0));
    for (int i = 0; i < config.d; i++)
        for (int j : config.edges[i])
            base[j][i] = (base[j][i] + 1) % Mod;
    config.power.push_back(base);
    for (int i = 1; i < MaxLog; i++)
        config.power.push_back(multiplyMatrix(config.power[i - 1], config.power[i - 1]));
    config.ready = true;
    return config;
}

void applyPower(const Config& config, vector<int>& value, long long step) {
    int bit = 0;
    while (step) {
        if (step & 1) {
            vector<int> nextValue(config.d, 0);
            for (int i = 0; i < config.d; i++)
                for (int j = 0; j < config.d; j++)
                    nextValue[i] = (nextValue[i] + config.power[bit][i][j] * value[j]) % Mod;
            value = nextValue;
        }
        step >>= 1;
        bit++;
    }
}

void applyBlocked(const Config& config, vector<int>& value, int blockedMask) {
    vector<int> nextValue(config.d, 0);
    for (int i = 0; i < config.d; i++) {
        if (value[i] == 0)
            continue;
        for (int j : config.edges[i])
            if (!(config.states[j] & blockedMask))
                nextValue[j] = (nextValue[j] + value[i]) % Mod;
    }
    value = nextValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    for (int caseId = 1; caseId <= testCase; caseId++) {
        long long r;
        int c, m, b;
        cin >> r >> c >> m;
        cin >> b;
        map<long long, int> blockRows;
        for (int i = 0; i < b; i++) {
            long long row;
            int column;
            cin >> row >> column;
            if (row <= r)
                blockRows[row] |= 1 << (column - 1);
        }
        Config& config = getConfig(c, m);
        vector<int> value(config.d, 1);
        if (blockRows.count(1)) {
            int blockedMask = blockRows[1];
            for (int i = 0; i < config.d; i++)
                if (config.states[i] & blockedMask)
                    value[i] = 0;
        }
        long long currentRow = 1;
        for (map<long long, int>::iterator it = blockRows.begin(); it != blockRows.end(); ++it) {
            long long row = it->first;
            if (row <= 1)
                continue;
            applyPower(config, value, row - currentRow - 1);
            applyBlocked(config, value, it->second);
            currentRow = row;
        }
        applyPower(config, value, r - currentRow);
        int answer = 0;
        for (int item : value)
            answer = (answer + item) % Mod;
        cout << "Case " << caseId << ": " << answer << '\n';
    }
    return 0;
}
