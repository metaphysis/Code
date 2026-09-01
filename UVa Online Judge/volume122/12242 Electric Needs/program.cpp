#include <bits/stdc++.h>
using namespace std;

using Long = long long;

struct Point {
    Long row, col;
};

struct Rect {
    Long left, right, down, up;
};

class Solver {
private:
    Long n, m;
    int p;
    vector<Point> plants;
    Long unionY(const vector<Rect>& rects, Long leftX, Long rightX) {
        vector<pair<Long, Long> > lines;
        for (const Rect& rect : rects)
            if (rect.left <= leftX && rect.right >= rightX)
                lines.push_back(make_pair(rect.down, rect.up));
        if (lines.empty())
            return 0;
        sort(lines.begin(), lines.end());
        Long result = 0, left = lines[0].first, right = lines[0].second;
        for (int i = 1; i < (int)lines.size(); i++) {
            if (lines[i].first > right + 1) {
                result += right - left + 1;
                left = lines[i].first;
                right = lines[i].second;
            } else
                right = max(right, lines[i].second);
        }
        result += right - left + 1;
        return result;
    }
    Long countNear(Long dis, Long xLimit, Long yLimit) {
        if (dis < 0)
            return 0;
        vector<Rect> rects;
        vector<Long> xs;
        for (const Point& plant : plants) {
            Long left = max(1LL, plant.row - dis), right = min(xLimit, plant.row + dis);
            Long down = max(1LL, plant.col - dis), up = min(yLimit, plant.col + dis);
            if (left <= right && down <= up) {
                rects.push_back({left, right, down, up});
                xs.push_back(left);
                xs.push_back(right + 1);
            }
        }
        if (rects.empty())
            return 0;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        Long area = 0;
        for (int i = 0; i + 1 < (int)xs.size(); i++)
            area += (xs[i + 1] - xs[i]) * unionY(rects, xs[i], xs[i + 1] - 1);
        Long plantCount = 0;
        for (const Point& plant : plants)
            if (plant.row <= xLimit && plant.col <= yLimit)
                plantCount++;
        return area - plantCount;
    }
    Long countLevel(Long dis, Long xLimit, Long yLimit) {
        return countNear(dis, xLimit, yLimit) - countNear(dis - 1, xLimit, yLimit);
    }
    pair<Long, Long> locate(Long pos) {
        Long low = 0, high = max(n, m);
        while (low < high) {
            Long mid = low + (high - low) / 2;
            if (countNear(mid, n, m) >= pos)
                high = mid;
            else
                low = mid + 1;
        }
        Long dis = low;
        Long before = countNear(dis - 1, n, m);
        Long target = pos - before;
        Long top = 1, bottom = n;
        while (top < bottom) {
            Long mid = top + (bottom - top) / 2;
            if (countLevel(dis, mid, m) >= target)
                bottom = mid;
            else
                top = mid + 1;
        }
        Long row = top;
        target -= countLevel(dis, row - 1, m);
        Long left = 1, right = m;
        while (left < right) {
            Long mid = left + (right - left) / 2;
            Long current = countLevel(dis, row, mid) - countLevel(dis, row - 1, mid);
            if (current >= target)
                right = mid;
            else
                left = mid + 1;
        }
        return make_pair(row, left);
    }
public:
    void run() {
        while (cin >> n >> m >> p && (n || m || p)) {
            plants.resize(p);
            for (Point& plant : plants)
                cin >> plant.row >> plant.col;
            int q;
            cin >> q;
            while (q--) {
                Long pos;
                cin >> pos;
                pair<Long, Long> answer = locate(pos);
                cout << answer.first << ' ' << answer.second << '\n';
            }
            cout << "-\n";
        }
    }
};

int main() {
    Solver solver;
    solver.run();
    return 0;
}
