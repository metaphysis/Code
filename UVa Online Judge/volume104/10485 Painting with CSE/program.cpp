#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

using Object = vector<Point>;
using Objects = vector<Object>;

bool samePoint(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

class Parser {
private:
    string str;
    int pos, len;
public:
    Parser(const string &s) : str(s), pos(0), len((int)s.size()) {
    }

    void skipSpace() {
        while (pos < len && isspace((unsigned char)str[pos])) pos++;
    }

    bool take(char c) {
        skipSpace();
        if (pos >= len || str[pos] != c) return false;
        pos++;
        return true;
    }

    bool parseNum(long long &val) {
        skipSpace();
        if (pos >= len) return false;
        int sign = 1;
        if (str[pos] == '+' || str[pos] == '-') {
            if (str[pos] == '-') sign = -1;
            pos++;
        }
        if (pos >= len || !isdigit((unsigned char)str[pos])) return false;
        __int128 cur = 0;
        while (pos < len && isdigit((unsigned char)str[pos])) {
            cur = cur * 10 + str[pos] - '0';
            if (cur > (__int128)LLONG_MAX + (sign == -1)) return false;
            pos++;
        }
        if (sign == 1) val = (long long)cur;
        else if (cur == (__int128)LLONG_MAX + 1) val = LLONG_MIN;
        else val = -(long long)cur;
        return true;
    }

    bool parsePoint(Point &point) {
        long long x, y;
        if (!take('(')) return false;
        if (!parseNum(x)) return false;
        if (!take(',')) return false;
        if (!parseNum(y)) return false;
        if (!take(')')) return false;
        point = {x, y};
        return true;
    }

    bool checkObject(const Object &obj) {
        for (int i = 1; i < (int)obj.size(); i++) {
            bool horizontal = obj[i - 1].y == obj[i].y;
            bool vertical = obj[i - 1].x == obj[i].x;
            if (!horizontal && !vertical) return false;
        }
        return true;
    }

    bool parseObject(Object &obj) {
        skipSpace();
        if (pos >= len) return false;
        if (str[pos] == '[') {
            pos++;
            Point point;
            if (!parsePoint(point)) return false;
            obj.push_back(point);
            while (true) {
                skipSpace();
                if (pos < len && str[pos] == ',') {
                    pos++;
                    if (!parsePoint(point)) return false;
                    obj.push_back(point);
                } else {
                    break;
                }
            }
            if (!take(']')) return false;
            return checkObject(obj);
        }
        if (str[pos] != 'A') return false;
        pos++;
        if (!take('(')) return false;
        Object first, second;
        if (!parseObject(first)) return false;
        if (!take(',')) return false;
        if (!parseObject(second)) return false;
        if (!take(')')) return false;
        if (!samePoint(first.back(), second.front())) return false;
        obj = first;
        for (int i = 1; i < (int)second.size(); i++) obj.push_back(second[i]);
        return true;
    }

    void translate(Objects &objects, long long dx, long long dy) {
        for (Object &obj : objects)
            for (Point &point : obj) {
                point.x += dx;
                point.y += dy;
            }
    }

    void scale(Objects &objects, long long fx, long long fy) {
        for (Object &obj : objects)
            for (Point &point : obj) {
                point.x *= fx;
                point.y *= fy;
            }
    }

    void rotate(Objects &objects, long long theta) {
        long long cnt = ((theta / 90) % 4 + 4) % 4;
        while (cnt--) {
            for (Object &obj : objects)
                for (Point &point : obj) {
                    long long x = point.x;
                    point.x = -point.y;
                    point.y = x;
                }
        }
    }

    bool parseListItem(Objects &objects) {
        skipSpace();
        if (pos >= len) return false;
        if (str[pos] == '[' || str[pos] == 'A') {
            Object obj;
            if (!parseObject(obj)) return false;
            objects.push_back(obj);
            return true;
        }
        char op = str[pos];
        if (op != 'T' && op != 'S' && op != 'R') return false;
        pos++;
        if (!take('(')) return false;
        long long a, b;
        Objects temp;
        if (!parseNum(a)) return false;
        if (!take(',')) return false;
        if (op == 'T' || op == 'S') {
            if (!parseNum(b)) return false;
            if (!take(',')) return false;
        }
        if (!parseList(temp)) return false;
        if (!take(')')) return false;
        if (op == 'T') translate(temp, a, b);
        else if (op == 'S') scale(temp, a, b);
        else rotate(temp, a);
        objects = temp;
        return true;
    }

    bool parseList(Objects &objects) {
        if (!parseListItem(objects)) return false;
        while (true) {
            skipSpace();
            if (pos >= len || str[pos] != 'u') break;
            pos++;
            Objects temp;
            if (!parseListItem(temp)) return false;
            for (Object &obj : temp) objects.push_back(obj);
        }
        return true;
    }

    bool parse(Objects &objects) {
        if (!parseList(objects)) return false;
        skipSpace();
        return pos == len;
    }
};

void drawPoint(vector<string> &bitmap, const Point &point) {
    if (point.x >= 0 && point.x <= 9 && point.y >= 0 && point.y <= 9)
        bitmap[point.y][point.x] = '#';
}

void drawLine(vector<string> &bitmap, const Point &a, const Point &b, bool &valid) {
    if (a.x != b.x && a.y != b.y) {
        valid = false;
        return;
    }
    if (a.x == b.x && a.y == b.y) {
        drawPoint(bitmap, a);
        return;
    }
    if (a.y == b.y) {
        long long left = max(0LL, min(a.x, b.x));
        long long right = min(9LL, max(a.x, b.x));
        if (a.y < 0 || a.y > 9 || left > right) return;
        for (long long x = left; x <= right; x++) bitmap[a.y][x] = '#';
    } else {
        long long bottom = max(0LL, min(a.y, b.y));
        long long top = min(9LL, max(a.y, b.y));
        if (a.x < 0 || a.x > 9 || bottom > top) return;
        for (long long y = bottom; y <= top; y++) bitmap[y][a.x] = '#';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    int caseNo = 1;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line == "#") break;
        vector<string> bitmap(10, string(10, '.'));
        Parser parser(line);
        Objects objects;
        bool valid = parser.parse(objects);
        if (valid) {
            for (const Object &obj : objects) {
                for (const Point &point : obj) drawPoint(bitmap, point);
                for (int i = 1; i < (int)obj.size(); i++) {
                    drawLine(bitmap, obj[i - 1], obj[i], valid);
                    if (!valid) break;
                }
                if (!valid) break;
            }
        }
        if (!valid) bitmap[0][0] = '?';
        cout << "Set #" << caseNo++ << '\n';
        for (int y = 9; y >= 0; y--) cout << bitmap[y] << '\n';
    }
    return 0;
}
