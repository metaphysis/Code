// In Case of Failure
// UVa ID: 1683
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.760s
// https://blog.csdn.net/metaphysis/article/details/163218448

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Node {
    int idx;
    int left, right;
    long long minX, maxX, minY, maxY;
};

class KDTree {
public:
    KDTree(const vector<Point>& points) : pts(points) {
        nodes.resize(pts.size());
        vector<int> indices(pts.size());
        iota(indices.begin(), indices.end(), 0);
        nodeCnt = 0;
        root = build(indices, 0, (int)pts.size() - 1, 0);
    }

    long long query(int targetIdx) {
        return query(root, pts[targetIdx].x, pts[targetIdx].y, targetIdx, LLONG_MAX);
    }

private:
    vector<Point> pts;
    vector<Node> nodes;
    int root, nodeCnt;

    int build(vector<int>& idxs, int l, int r, int depth) {
        if (l > r) return -1;
        int mid = (l + r) >> 1;
        int dim = depth & 1;
        nth_element(idxs.begin() + l, idxs.begin() + mid, idxs.begin() + r + 1,
            [&](int a, int b) {
                if (dim == 0) return pts[a].x < pts[b].x;
                return pts[a].y < pts[b].y;
            });
        int cur = nodeCnt++;
        int pointIdx = idxs[mid];
        nodes[cur].idx = pointIdx;
        nodes[cur].left = build(idxs, l, mid - 1, depth + 1);
        nodes[cur].right = build(idxs, mid + 1, r, depth + 1);
        nodes[cur].minX = nodes[cur].maxX = pts[pointIdx].x;
        nodes[cur].minY = nodes[cur].maxY = pts[pointIdx].y;
        if (nodes[cur].left != -1) {
            int lc = nodes[cur].left;
            nodes[cur].minX = min(nodes[cur].minX, nodes[lc].minX);
            nodes[cur].maxX = max(nodes[cur].maxX, nodes[lc].maxX);
            nodes[cur].minY = min(nodes[cur].minY, nodes[lc].minY);
            nodes[cur].maxY = max(nodes[cur].maxY, nodes[lc].maxY);
        }
        if (nodes[cur].right != -1) {
            int rc = nodes[cur].right;
            nodes[cur].minX = min(nodes[cur].minX, nodes[rc].minX);
            nodes[cur].maxX = max(nodes[cur].maxX, nodes[rc].maxX);
            nodes[cur].minY = min(nodes[cur].minY, nodes[rc].minY);
            nodes[cur].maxY = max(nodes[cur].maxY, nodes[rc].maxY);
        }
        return cur;
    }

    long long minDistToBox(int nodeIdx, long long px, long long py) {
        const Node& nd = nodes[nodeIdx];
        long long dx = 0, dy = 0;
        if (px < nd.minX) dx = nd.minX - px;
        else if (px > nd.maxX) dx = px - nd.maxX;
        if (py < nd.minY) dy = nd.minY - py;
        else if (py > nd.maxY) dy = py - nd.maxY;
        return dx * dx + dy * dy;
    }

    long long query(int nodeIdx, long long px, long long py, int targetIdx, long long best) {
        if (nodeIdx == -1) return best;
        const Node& nd = nodes[nodeIdx];
        long long dx = pts[nd.idx].x - px;
        long long dy = pts[nd.idx].y - py;
        long long dist = dx * dx + dy * dy;
        if (nd.idx != targetIdx && dist < best) best = dist;
        int first = nd.left, second = nd.right;
        long long leftDist = (first == -1) ? LLONG_MAX : minDistToBox(first, px, py);
        long long rightDist = (second == -1) ? LLONG_MAX : minDistToBox(second, px, py);
        if (leftDist > rightDist) {
            swap(first, second);
            swap(leftDist, rightDist);
        }
        if (first != -1 && leftDist < best)
            best = query(first, px, py, targetIdx, best);
        if (second != -1 && rightDist < best)
            best = query(second, px, py, targetIdx, best);
        return best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i)
            cin >> pts[i].x >> pts[i].y;
        KDTree tree(pts);
        for (int i = 0; i < n; ++i)
            cout << tree.query(i) << '\n';
    }
    return 0;
}
