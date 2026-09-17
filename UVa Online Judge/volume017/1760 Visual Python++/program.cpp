#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Corner {
    ll row, col;
};

struct Rect {
    ll top, left, bottom, right;
};

struct MatchEvent {
    ll row, col;
    int type, index;
};

struct Segment {
    ll pos, left, right;
    int owner;
};

struct SweepEvent {
    ll row, left, right;
    int type, owner;
};

struct Fenwick {
    int size;
    vector<int> tree;
    Fenwick(int n) : size(n), tree(n + 1, 0) {}

    void add(int index, int value) {
        for (; index <= size; index += index & -index) tree[index] += value;
    }

    int query(int index) {
        int result = 0;
        for (; index > 0; index -= index & -index) result += tree[index];
        return result;
    }

    int rangeQuery(int left, int right) {
        if (left > right) return 0;
        return query(right) - query(left - 1);
    }
};

bool matchCorners(const vector<Corner>& topLeft, const vector<Corner>& bottomRight, vector<int>& answer, vector<Rect>& rects) {
    int n = topLeft.size();
    vector<MatchEvent> events;
    events.reserve(2 * n);
    answer.assign(n, -1);
    rects.resize(n);
    for (int i = 0; i < n; ++i) {
        events.push_back({topLeft[i].row, topLeft[i].col, 0, i});
        events.push_back({bottomRight[i].row, bottomRight[i].col, 1, i});
    }
    sort(events.begin(), events.end(), [](const MatchEvent& a, const MatchEvent& b) {
        if (a.row != b.row) return a.row < b.row;
        if (a.type != b.type) return a.type < b.type;
        if (a.col != b.col) return a.col < b.col;
        return a.index < b.index;
    });
    set<pair<ll, int>> active;
    for (const MatchEvent& event : events) {
        if (event.type == 0) {
            active.insert({event.col, event.index});
            continue;
        }
        auto iterator = active.upper_bound({event.col, numeric_limits<int>::max()});
        if (iterator == active.begin()) return false;
        --iterator;
        int topIndex = iterator->second, bottomIndex = event.index;
        active.erase(iterator);
        answer[topIndex] = bottomIndex;
        rects[topIndex] = {topLeft[topIndex].row, topLeft[topIndex].col, bottomRight[bottomIndex].row, bottomRight[bottomIndex].col};
    }
    return active.empty();
}

bool checkCollinear(vector<Segment>& segments) {
    sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) {
        if (a.pos != b.pos) return a.pos < b.pos;
        if (a.left != b.left) return a.left < b.left;
        if (a.right != b.right) return a.right < b.right;
        return a.owner < b.owner;
    });
    int n = segments.size(), index = 0;
    while (index < n) {
        int next = index + 1;
        ll maxRight = segments[index].right;
        while (next < n && segments[next].pos == segments[index].pos) {
            if (segments[next].left <= maxRight) return false;
            maxRight = max(maxRight, segments[next].right);
            ++next;
        }
        index = next;
    }
    return true;
}

bool checkCrossing(const vector<Segment>& horizontal, const vector<Segment>& vertical, const vector<Rect>& rects) {
    vector<ll> columns;
    vector<SweepEvent> events;
    columns.reserve(vertical.size());
    events.reserve(horizontal.size() + 2 * vertical.size());
    for (const Segment& segment : vertical) {
        columns.push_back(segment.pos);
        events.push_back({segment.left, segment.pos, segment.pos, 0, segment.owner});
        events.push_back({segment.right, segment.pos, segment.pos, 2, segment.owner});
    }
    for (const Segment& segment : horizontal) events.push_back({segment.pos, segment.left, segment.right, 1, segment.owner});
    sort(columns.begin(), columns.end());
    columns.erase(unique(columns.begin(), columns.end()), columns.end());
    sort(events.begin(), events.end(), [](const SweepEvent& a, const SweepEvent& b) {
        if (a.row != b.row) return a.row < b.row;
        if (a.type != b.type) return a.type < b.type;
        if (a.left != b.left) return a.left < b.left;
        return a.right < b.right;
    });
    Fenwick bit(columns.size());
    for (const SweepEvent& event : events) {
        if (event.type == 0) {
            int position = lower_bound(columns.begin(), columns.end(), event.left) - columns.begin() + 1;
            bit.add(position, 1);
            continue;
        }
        if (event.type == 2) {
            int position = lower_bound(columns.begin(), columns.end(), event.left) - columns.begin() + 1;
            bit.add(position, -1);
            continue;
        }
        int leftIndex = lower_bound(columns.begin(), columns.end(), event.left) - columns.begin() + 1, rightIndex = upper_bound(columns.begin(), columns.end(), event.right) - columns.begin(), count = bit.rangeQuery(leftIndex, rightIndex), expected = rects[event.owner].left == rects[event.owner].right ? 1 : 2;
        if (count > expected) return false;
    }
    return true;
}

bool checkRectangles(const vector<Rect>& rects) {
    int n = rects.size();
    vector<Segment> horizontal, vertical;
    horizontal.reserve(2 * n);
    vertical.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        const Rect& rect = rects[i];
        if (rect.top > rect.bottom || rect.left > rect.right) return false;
        horizontal.push_back({rect.top, rect.left, rect.right, i});
        if (rect.top != rect.bottom) horizontal.push_back({rect.bottom, rect.left, rect.right, i});
        vertical.push_back({rect.left, rect.top, rect.bottom, i});
        if (rect.left != rect.right) vertical.push_back({rect.right, rect.top, rect.bottom, i});
    }
    if (!checkCollinear(horizontal)) return false;
    if (!checkCollinear(vertical)) return false;
    return checkCrossing(horizontal, vertical, rects);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Corner> topLeft(n), bottomRight(n);
        vector<int> answer;
        vector<Rect> rects;
        for (int i = 0; i < n; ++i) cin >> topLeft[i].row >> topLeft[i].col;
        for (int i = 0; i < n; ++i) cin >> bottomRight[i].row >> bottomRight[i].col;
        bool valid = matchCorners(topLeft, bottomRight, answer, rects);
        if (valid) valid = checkRectangles(rects);
        if (!valid) {
            cout << "syntax error\n";
            continue;
        }
        for (int index : answer) cout << index + 1 << '\n';
    }
    return 0;
}
