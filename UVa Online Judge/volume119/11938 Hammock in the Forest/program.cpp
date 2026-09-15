#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Hammock {
    int a, b;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inBox(const Point &a, const Point &b, const Point &p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    return cross(a, b, p) == 0 && inBox(a, b, p);
}

bool isIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    long long c1 = cross(a, b, c), c2 = cross(a, b, d), c3 = cross(c, d, a), c4 = cross(c, d, b);
    if ((c1 > 0 && c2 < 0 || c1 < 0 && c2 > 0) && (c3 > 0 && c4 < 0 || c3 < 0 && c4 > 0))
        return true;
    if (c1 == 0 && onSegment(a, b, c))
        return true;
    if (c2 == 0 && onSegment(a, b, d))
        return true;
    if (c3 == 0 && onSegment(c, d, a))
        return true;
    if (c4 == 0 && onSegment(c, d, b))
        return true;
    return false;
}

vector<long long> parseNumbers(const string &text) {
    string data = text;
    for (char &ch : data)
        if (ch == '(' || ch == ')' || ch == ',')
            ch = ' ';
    stringstream input(data);
    vector<long long> numbers;
    long long value;
    while (input >> value)
        numbers.push_back(value);
    return numbers;
}

void splitConfig(const string &line, string &treePart, string &hammockPart) {
    size_t pos = line.find(';');
    treePart = line.substr(0, pos);
    hammockPart = line.substr(pos + 1);
}

int solve() {
    int testCount;
    cin >> testCount;
    string line;
    getline(cin, line);
    for (int test = 0; test < testCount; ++test) {
        getline(cin, line);
        while (line.empty())
            getline(cin, line);
        string treePart, hammockPart;
        splitConfig(line, treePart, hammockPart);
        vector<long long> treeNumbers = parseNumbers(treePart);
        vector<long long> hammockNumbers = parseNumbers(hammockPart);
        vector<Point> points;
        vector<Hammock> hammocks;
        for (int i = 0; i < static_cast<int>(treeNumbers.size()); i += 2)
            points.push_back({treeNumbers[i], treeNumbers[i + 1]});
        for (int i = 0; i < static_cast<int>(hammockNumbers.size()); i += 2)
            hammocks.push_back({static_cast<int>(hammockNumbers[i]) - 1, static_cast<int>(hammockNumbers[i + 1]) - 1});
        vector<pair<int, int>> crossings;
        for (int i = 0; i < static_cast<int>(hammocks.size()); ++i) {
            for (int j = i + 1; j < static_cast<int>(hammocks.size()); ++j) {
                if (hammocks[i].a == hammocks[j].a || hammocks[i].a == hammocks[j].b || hammocks[i].b == hammocks[j].a || hammocks[i].b == hammocks[j].b)
                    continue;
                const Point &a = points[hammocks[i].a];
                const Point &b = points[hammocks[i].b];
                const Point &c = points[hammocks[j].a];
                const Point &d = points[hammocks[j].b];
                if (isIntersect(a, b, c, d))
                    crossings.push_back({i, j});
            }
        }
        if (crossings.empty()) {
            cout << "Ok\n";
            continue;
        }
        cout << "Crossings found:";
        for (int i = 0; i < static_cast<int>(crossings.size()); ++i) {
            int a = crossings[i].first, b = crossings[i].second;
            cout << " (" << hammocks[a].a + 1 << "," << hammocks[a].b + 1 << ") (" << hammocks[b].a + 1 << "," << hammocks[b].b + 1 << ")";
            if (i + 1 < static_cast<int>(crossings.size()))
                cout << ";";
        }
        cout << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
