#include <bits/stdc++.h>
using namespace std;

class FastInput {
private:
    static const int bufferSize = 1 << 20;
    int index, size;
    char buffer[bufferSize];
public:
    FastInput() : index(0), size(0) {}
    char getChar() {
        if (index >= size) {
            size = fread(buffer, 1, bufferSize, stdin);
            index = 0;
            if (size == 0) return 0;
        }
        return buffer[index++];
    }
    template <typename T>
    bool read(T &value) {
        char ch = getChar();
        if (!ch) return false;
        while (ch != '-' && (ch < '0' || ch > '9')) {
            ch = getChar();
            if (!ch) return false;
        }
        int sign = 1;
        if (ch == '-') {
            sign = -1;
            ch = getChar();
        }
        value = 0;
        while (ch >= '0' && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = getChar();
        }
        value *= sign;
        return true;
    }
};

class Fenwick {
private:
    int size;
    vector<int> tree;
public:
    Fenwick(int n) : size(n), tree(n + 1, 0) {}
    void add(int index, int value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }
    int sum(int index) {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }
};

struct Point {
    long long d1, d2;
};

struct Query {
    long long r1, r2;
    int id;
};

int main() {
    FastInput input;
    int n;
    input.read(n);
    long long x0, y0, z0, x1, y1, z1;
    input.read(x0);
    input.read(y0);
    input.read(z0);
    input.read(x1);
    input.read(y1);
    input.read(z1);
    int pointCount = n - 2;
    vector<Point> points(pointCount);
    vector<long long> values;
    values.reserve(pointCount);
    for (int i = 0; i < pointCount; i++) {
        long long x, y, z;
        input.read(x);
        input.read(y);
        input.read(z);
        long long dx0 = x - x0, dy0 = y - y0, dz0 = z - z0;
        long long dx1 = x - x1, dy1 = y - y1, dz1 = z - z1;
        points[i].d1 = dx0 * dx0 + dy0 * dy0 + dz0 * dz0;
        points[i].d2 = dx1 * dx1 + dy1 * dy1 + dz1 * dz1;
        values.push_back(points[i].d2);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return a.d1 > b.d1;
    });
    int q;
    input.read(q);
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        long long r1, r2;
        input.read(r1);
        input.read(r2);
        queries[i].r1 = r1 * r1;
        queries[i].r2 = r2 * r2;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
        return a.r1 > b.r1;
    });
    Fenwick fenwick(values.size());
    vector<int> answers(q);
    int pointIndex = 0, addedCount = 0;
    for (const Query &query : queries) {
        while (pointIndex < pointCount && points[pointIndex].d1 > query.r1) {
            int rank = lower_bound(values.begin(), values.end(), points[pointIndex].d2) - values.begin() + 1;
            fenwick.add(rank, 1);
            pointIndex++;
            addedCount++;
        }
        int limit = upper_bound(values.begin(), values.end(), query.r2) - values.begin();
        int notReceived = addedCount - fenwick.sum(limit);
        answers[query.id] = pointCount - notReceived;
    }
    string output;
    output.reserve(q * 4);
    for (int answer : answers) output += to_string(answer) + '\n';
    fwrite(output.c_str(), 1, output.size(), stdout);
    return 0;
}
