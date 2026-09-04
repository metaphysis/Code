#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long pos, speed;
    Line(long long p = 0, long long v = 0) : pos(p), speed(v) {
    }
};

class LiChao {
private:
    vector<long long> xs;
    vector<Line> tree;
    bool isMax;

    bool better(const Line &a, const Line &b, long long x) {
        if (a.speed == 0) return false;
        if (b.speed == 0) return true;
        __int128 left = (__int128)(x - a.pos) * b.speed;
        __int128 right = (__int128)(x - b.pos) * a.speed;
        if (isMax) return left > right;
        return left < right;
    }

    void addLine(Line line, int node, int left, int right) {
        int mid = (left + right) / 2;
        bool leftBetter = better(line, tree[node], xs[left]);
        bool midBetter = better(line, tree[node], xs[mid]);
        if (midBetter) swap(line, tree[node]);
        if (left == right) return;
        if (leftBetter != midBetter) addLine(line, node * 2, left, mid);
        else addLine(line, node * 2 + 1, mid + 1, right);
    }

    Line queryLine(int index, int node, int left, int right) {
        if (left == right) return tree[node];
        int mid = (left + right) / 2;
        Line result;
        if (index <= mid) result = queryLine(index, node * 2, left, mid);
        else result = queryLine(index, node * 2 + 1, mid + 1, right);
        if (better(tree[node], result, xs[index])) return tree[node];
        return result;
    }

public:
    LiChao(const vector<long long> &coordinates, bool maxMode) {
        xs = coordinates;
        isMax = maxMode;
        tree.assign(xs.size() * 4 + 5, Line());
    }

    void addLine(Line line) {
        addLine(line, 1, 0, (int)xs.size() - 1);
    }

    Line query(long long x) {
        int index = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        return queryLine(index, 1, 0, (int)xs.size() - 1);
    }
};

long long floorDiv(long long numerator, long long denominator) {
    if (numerator >= 0) return numerator / denominator;
    return -((-numerator + denominator - 1) / denominator);
}

long long ceilDiv(long long numerator, long long denominator) {
    if (numerator >= 0) return (numerator + denominator - 1) / denominator;
    return -((-numerator) / denominator);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int frogCount, segmentCount;
        cin >> frogCount >> segmentCount;
        static long long positions[1005], speeds[1005], ends[100005];
        for (int i = 0; i < frogCount; i++) cin >> positions[i];
        for (int i = 0; i < frogCount; i++) cin >> speeds[i];
        for (int i = 0; i < segmentCount; i++) cin >> ends[i];
        vector<long long> starts, rights, coordinates;
        starts.reserve(segmentCount + 1);
        rights.reserve(segmentCount + 1);
        coordinates.reserve((segmentCount + 1) * 2);
        for (int i = 0; i <= segmentCount; i++) {
            long long left = i == 0 ? 0 : ends[i - 1] + 1;
            long long right = i == segmentCount ? 1000000000LL : ends[i];
            starts.push_back(left);
            rights.push_back(right);
            coordinates.push_back(left);
            coordinates.push_back(right);
        }
        sort(coordinates.begin(), coordinates.end());
        coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());
        LiChao maxTree(coordinates, true), minTree(coordinates, false);
        for (int i = 0; i < frogCount; i++) {
            Line line(positions[i], speeds[i]);
            maxTree.addLine(line);
            minTree.addLine(line);
        }
        long long answer = LLONG_MAX;
        for (int i = 0; i <= segmentCount; i++) {
            Line maxLine = maxTree.query(starts[i]);
            Line minLine = minTree.query(rights[i]);
            long long lower = ceilDiv(starts[i] - maxLine.pos, maxLine.speed);
            long long upper = floorDiv(rights[i] - minLine.pos, minLine.speed);
            lower = max(0LL, lower);
            if (lower <= upper) answer = min(answer, lower);
        }
        if (answer == LLONG_MAX) answer = -1;
        cout << "Case " << caseId << ": " << answer << '\n';
    }
    return 0;
}
