#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct InputData {
    ll x, y, wideA, wideB, narrowA, narrowB;
    char type;
};

struct CoverTree {
    int n;
    vector<ll> maxVal;

    void init(int size) {
        n = size;
        maxVal.assign(n * 4 + 5, LLONG_MIN);
    }

    void update(int node, int left, int right, int pos, ll value) {
        if (left == right) {
            maxVal[node] = max(maxVal[node], value);
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid) update(node * 2, left, mid, pos, value);
        else update(node * 2 + 1, mid + 1, right, pos, value);
        maxVal[node] = max(maxVal[node * 2], maxVal[node * 2 + 1]);
    }

    void update(int pos, ll value) {
        update(1, 0, n - 1, pos, value);
    }

    ll query(int node, int left, int right, int queryLeft) {
        if (right < queryLeft) return LLONG_MIN;
        if (queryLeft <= left) return maxVal[node];
        int mid = (left + right) / 2;
        return max(query(node * 2, left, mid, queryLeft), query(node * 2 + 1, mid + 1, right, queryLeft));
    }

    ll query(int queryLeft) {
        if (queryLeft >= n) return LLONG_MIN;
        return query(1, 0, n - 1, queryLeft);
    }
};

struct VisibleTree {
    int n;
    vector<ll> minVal, coords;
    vector<set<pair<ll, int>>> bucket;

    void init(vector<ll> values) {
        coords = values;
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        n = coords.size();
        minVal.assign(n * 4 + 5, LLONG_MAX);
        bucket.assign(n, set<pair<ll, int>>());
    }

    void maintain(int node, int left, int right) {
        if (left == right) {
            if (bucket[left].empty()) minVal[node] = LLONG_MAX;
            else minVal[node] = bucket[left].begin()->first;
            return;
        }
        minVal[node] = min(minVal[node * 2], minVal[node * 2 + 1]);
    }

    void update(int node, int left, int right, int pos) {
        if (left == right) {
            maintain(node, left, right);
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid) update(node * 2, left, mid, pos);
        else update(node * 2 + 1, mid + 1, right, pos);
        maintain(node, left, right);
    }

    void add(ll first, ll second, int id) {
        int pos = lower_bound(coords.begin(), coords.end(), first) - coords.begin();
        bucket[pos].insert({second, id});
        update(1, 0, n - 1, pos);
    }

    void erase(ll first, ll second, int id) {
        int pos = lower_bound(coords.begin(), coords.end(), first) - coords.begin();
        bucket[pos].erase({second, id});
        update(1, 0, n - 1, pos);
    }

    void collect(int node, int left, int right, int queryRight, ll limit, vector<int>& result) {
        if (left > queryRight || minVal[node] > limit) return;
        if (left == right) {
            while (!bucket[left].empty() && bucket[left].begin()->first <= limit) {
                result.push_back(bucket[left].begin()->second);
                bucket[left].erase(bucket[left].begin());
            }
            maintain(node, left, right);
            return;
        }
        int mid = (left + right) / 2;
        collect(node * 2, left, mid, queryRight, limit, result);
        collect(node * 2 + 1, mid + 1, right, queryRight, limit, result);
        maintain(node, left, right);
    }

    void collect(ll limitFirst, ll limitSecond, vector<int>& result) {
        int queryRight = upper_bound(coords.begin(), coords.end(), limitFirst) - coords.begin() - 1;
        if (queryRight < 0) return;
        collect(1, 0, n - 1, queryRight, limitSecond, result);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n;
        cin >> n;
        vector<InputData> data(n);
        vector<ll> wideCoords, narrowCoords;
        wideCoords.reserve(n);
        narrowCoords.reserve(n);
        for (int i = 0; i < n; i++) {
            cin >> data[i].x >> data[i].y >> data[i].type;
            data[i].wideA = data[i].x + data[i].y;
            data[i].wideB = data[i].y - data[i].x;
            data[i].narrowA = 2 * data[i].x + data[i].y;
            data[i].narrowB = data[i].y - 2 * data[i].x;
            wideCoords.push_back(data[i].wideA);
            narrowCoords.push_back(data[i].narrowA);
        }
        sort(wideCoords.begin(), wideCoords.end());
        wideCoords.erase(unique(wideCoords.begin(), wideCoords.end()), wideCoords.end());
        sort(narrowCoords.begin(), narrowCoords.end());
        narrowCoords.erase(unique(narrowCoords.begin(), narrowCoords.end()), narrowCoords.end());
        CoverTree wideCover, narrowCover;
        wideCover.init(wideCoords.size());
        narrowCover.init(narrowCoords.size());
        VisibleTree wideVisible, narrowVisible;
        wideVisible.init(wideCoords);
        narrowVisible.init(narrowCoords);
        int visibleCount = 0;
        for (int i = 0; i < n; i++) {
            bool failed = false;
            int widePos = lower_bound(wideCoords.begin(), wideCoords.end(), data[i].wideA) - wideCoords.begin();
            int narrowPos = lower_bound(narrowCoords.begin(), narrowCoords.end(), data[i].narrowA) - narrowCoords.begin();
            if (wideCover.query(widePos) >= data[i].wideB) failed = true;
            if (narrowCover.query(narrowPos) >= data[i].narrowB) failed = true;
            if (failed) {
                cout << "FAIL\n";
                continue;
            }
            vector<int> removed;
            if (data[i].type == 'W') {
                wideVisible.collect(data[i].wideA, data[i].wideB, removed);
                for (int id : removed) {
                    narrowVisible.erase(data[id].narrowA, data[id].narrowB, id);
                }
            } else {
                narrowVisible.collect(data[i].narrowA, data[i].narrowB, removed);
                for (int id : removed) {
                    wideVisible.erase(data[id].wideA, data[id].wideB, id);
                }
            }
            visibleCount -= removed.size();
            wideVisible.add(data[i].wideA, data[i].wideB, i);
            narrowVisible.add(data[i].narrowA, data[i].narrowB, i);
            if (data[i].type == 'W') wideCover.update(widePos, data[i].wideB);
            else narrowCover.update(narrowPos, data[i].narrowB);
            visibleCount++;
            cout << visibleCount << '\n';
        }
    }
    return 0;
}
