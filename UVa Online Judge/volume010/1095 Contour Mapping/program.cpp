// Contour Mapping
// UVa ID: 1095
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

struct EdgeInfo {
    int u;
    int v;
    vector<ll> oppositeHeights;
};

static unsigned long long edgeKey(int u, int v) {
    if (u > v) swap(u, v);
    return (static_cast<unsigned long long>(static_cast<unsigned int>(u)) << 32) | static_cast<unsigned int>(v);
}

static ld arithmeticSum(ll first, ll last) {
    if (first > last) return 0.0L;
    ld count = static_cast<ld>(last - first + 1);
    return (static_cast<ld>(first) + static_cast<ld>(last)) * count / 2.0L;
}

static ld triangleContribution(ll a, ll b, ll c, ll d, ll h) {
    array<ll, 3> value = {a, b, c};
    sort(value.begin(), value.end());
    ll low = value[0];
    ll mid = value[1];
    ll high = value[2];
    if (low == high) return 0.0L;
    ld sectionAtMid;
    if (low == mid || mid == high) {
        sectionAtMid = static_cast<ld>(d);
    } else {
        ld t = static_cast<ld>(mid - low) / static_cast<ld>(high - low);
        sectionAtMid = static_cast<ld>(d) * sqrtl(1.0L - t * (1.0L - t));
    }
    ld result = 0.0L;
    if (low < mid) {
        ll first = low / h + 1;
        ll last = (mid - 1) / h;
        if (first <= last) {
            ld count = static_cast<ld>(last - first + 1);
            ld levelSum = static_cast<ld>(h) * arithmeticSum(first, last);
            result += sectionAtMid * (levelSum - static_cast<ld>(low) * count) / static_cast<ld>(mid - low);
        }
    }
    if (mid < high) {
        ll first = mid / h + 1;
        ll last = (high - 1) / h;
        if (first <= last) {
            ld count = static_cast<ld>(last - first + 1);
            ld levelSum = static_cast<ld>(h) * arithmeticSum(first, last);
            result += sectionAtMid * (static_cast<ld>(high) * count - levelSum) / static_cast<ld>(high - mid);
        }
    }
    if (low < mid && mid < high && mid % h == 0) result += sectionAtMid;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int s;
    int caseNumber = 1;
    while (cin >> s && s != 0) {
        int p;
        ll d;
        ll h;
        cin >> p >> d >> h;
        vector<vector<int>> id(s);
        vector<ll> height;
        int pointCount = 0;
        for (int row = 0; row < s; ++row) {
            int count = p + (row & 1);
            id[row].resize(count);
            for (int col = 0; col < count; ++col) {
                ll value;
                cin >> value;
                id[row][col] = pointCount++;
                height.push_back(value);
            }
        }
        unordered_map<unsigned long long, EdgeInfo> edges;
        ld answer = 0.0L;
        auto addEdge = [&](int u, int v, int opposite) {
            unsigned long long key = edgeKey(u, v);
            auto it = edges.find(key);
            if (it == edges.end()) {
                EdgeInfo info;
                info.u = min(u, v);
                info.v = max(u, v);
                info.oppositeHeights.push_back(height[opposite]);
                edges.emplace(key, move(info));
            } else {
                it->second.oppositeHeights.push_back(height[opposite]);
            }
        };
        auto addTriangle = [&](int a, int b, int c) {
            answer += triangleContribution(height[a], height[b], height[c], d, h);
            addEdge(a, b, c);
            addEdge(b, c, a);
            addEdge(c, a, b);
        };
        for (int row = 0; row + 1 < s; ++row) {
            int upperCount = static_cast<int>(id[row].size());
            int lowerCount = static_cast<int>(id[row + 1].size());
            if (lowerCount == upperCount + 1) {
                for (int i = 0; i < upperCount; ++i) addTriangle(id[row][i], id[row + 1][i], id[row + 1][i + 1]);
                for (int i = 0; i + 1 < upperCount; ++i) addTriangle(id[row][i], id[row][i + 1], id[row + 1][i + 1]);
            } else if (upperCount == lowerCount + 1) {
                for (int i = 0; i < lowerCount; ++i) addTriangle(id[row + 1][i], id[row][i], id[row][i + 1]);
                for (int i = 0; i + 1 < lowerCount; ++i) addTriangle(id[row + 1][i], id[row + 1][i + 1], id[row][i + 1]);
            }
        }
        for (const auto &entry : edges) {
            const EdgeInfo &edge = entry.second;
            ll hu = height[edge.u];
            ll hv = height[edge.v];
            if (hu != hv) continue;
            ll level = hu;
            if (level % h != 0) continue;
            bool isContourBoundary = false;
            if (edge.oppositeHeights.size() == 1) {
                isContourBoundary = true;
            } else {
                for (ll oppositeHeight : edge.oppositeHeights) {
                    if (oppositeHeight != level) {
                        isContourBoundary = true;
                        break;
                    }
                }
            }
            if (isContourBoundary) answer += static_cast<ld>(d);
        }
        cout << "Case " << caseNumber++ << ": " << fixed << setprecision(0) << answer << '\n';
    }
    return 0;
}
