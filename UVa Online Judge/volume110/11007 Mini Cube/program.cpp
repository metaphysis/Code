#include <bits/stdc++.h>
using namespace std;

struct Face {
    using Type = uint16_t;
    Type data = 0;
    Face() {}
    Face(const string &s) {
        for (int i = 0; i < 4; ++i) data |= string("WRBYOG").find(s[i]) << (i * 4);
    }
    unsigned get(int i) const { return data >> (i * 4) & 15; }
    void set(int i, Type c) { data = data & ~(15 << (i * 4)) | c << (i * 4); }
    void rot(int d) {
        unsigned a = get(0), b = get(1);
        if (!d) {
            set(0, get(3));
            set(1, get(2));
            set(2, b);
            set(3, a);
        } else if (d == 1) {
            set(0, get(2));
            set(2, get(3));
            set(3, get(1));
            set(1, a);
        } else {
            set(0, get(1));
            set(1, get(3));
            set(3, get(2));
            set(2, a);
        }
    }
    bool operator ==(const Face &x) const { return data == x.data; }
};

class Cube {
    enum { T, F, R, D, B, L };
    enum { A, C, E, G };
    array<Face, 6> a;
    unsigned char rep = 0, last = 0, dep = 0;
    void pos() {
        static int fc[8][3] = {{T,L,B},{T,R,B},{T,L,F},{T,R,F},{D,L,F},{D,R,F},{D,L,B},{D,R,B}};
        static int id[8][3] = {{A,A,C},{C,C,A},{E,C,A},{G,A,C},{A,G,E},{C,E,G},{E,E,G},{G,G,E}};
        Cube c;
        unsigned v[3] = {c.a[F].get(G), c.a[R].get(E), c.a[D].get(C)};
        int p = -1;
        for (int i = 0; i < 8; ++i) {
            bool ok[3] = {};
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    if (a[fc[i][j]].get(id[i][j]) == v[k]) ok[k] = 1;
            if (ok[0] && ok[1] && ok[2]) {
                p = i;
                break;
            }
        }
        turn(p);
        corner(fc[5], id[5], c.a[D].get(C));
    }
    void turn(int p) {
        int x[8] = {0,-1,1,99,1,99,0,-1}, y[8] = {-1,-1,-1,-1,99,99,99,99};
        if (x[p] != 99) X(x[p]);
        if (y[p] != 99) Y(y[p]);
    }
    void corner(int *fc, int *id, unsigned c) {
        int p = -1;
        for (int i = 0; i < 3; ++i)
            if (a[fc[i]].get(id[i]) == c) {
                p = i;
                break;
            }
        if (p == 1) {
            Z(1);
            X(1);
        } else if (p == 2) {
            Y(-1);
            X(-1);
        }
    }
    void Lm() {
        unsigned x = a[T].get(A), y = a[T].get(E);
        a[L].rot(1);
        a[T].set(A, a[B].get(G));
        a[T].set(E, a[B].get(C));
        a[B].set(G, a[D].get(A));
        a[B].set(C, a[D].get(E));
        a[D].set(A, a[F].get(A));
        a[D].set(E, a[F].get(E));
        a[F].set(A, x);
        a[F].set(E, y);
    }
    void Lp() {
        unsigned x = a[T].get(A), y = a[T].get(E);
        a[L].rot(-1);
        a[T].set(A, a[F].get(A));
        a[T].set(E, a[F].get(E));
        a[F].set(A, a[D].get(A));
        a[F].set(E, a[D].get(E));
        a[D].set(A, a[B].get(G));
        a[D].set(E, a[B].get(C));
        a[B].set(G, x);
        a[B].set(C, y);
    }
    void Um() {
        unsigned x = a[F].get(A), y = a[F].get(C);
        a[T].rot(1);
        a[F].set(A, a[R].get(A));
        a[F].set(C, a[R].get(C));
        a[R].set(A, a[B].get(A));
        a[R].set(C, a[B].get(C));
        a[B].set(A, a[L].get(A));
        a[B].set(C, a[L].get(C));
        a[L].set(A, x);
        a[L].set(C, y);
    }
    void Up() {
        unsigned x = a[F].get(A), y = a[F].get(C);
        a[T].rot(-1);
        a[F].set(A, a[L].get(A));
        a[F].set(C, a[L].get(C));
        a[L].set(A, a[B].get(A));
        a[L].set(C, a[B].get(C));
        a[B].set(A, a[R].get(A));
        a[B].set(C, a[R].get(C));
        a[R].set(A, x);
        a[R].set(C, y);
    }
    void Bm() {
        unsigned x = a[T].get(A), y = a[T].get(C);
        a[B].rot(1);
        a[T].set(A, a[R].get(C));
        a[T].set(C, a[R].get(G));
        a[R].set(C, a[D].get(G));
        a[R].set(G, a[D].get(E));
        a[D].set(E, a[L].get(A));
        a[D].set(G, a[L].get(E));
        a[L].set(A, y);
        a[L].set(E, x);
    }
    void Bp() {
        unsigned x = a[T].get(A), y = a[T].get(C);
        a[B].rot(-1);
        a[T].set(A, a[L].get(E));
        a[T].set(C, a[L].get(A));
        a[L].set(A, a[D].get(E));
        a[L].set(E, a[D].get(G));
        a[D].set(E, a[R].get(G));
        a[D].set(G, a[R].get(C));
        a[R].set(C, x);
        a[R].set(G, y);
    }
    void X(int n) {
        if (!n) {
            swap(a[F], a[B]);
            swap(a[R], a[L]);
            a[T].rot(0);
            a[D].rot(0);
            return;
        }
        int q[4] = {F, n == 1 ? L : R, B, n == 1 ? R : L}, d = n == 1 ? 1 : -1;
        Face x = a[q[0]];
        for (int i = 0; i < 3; ++i) a[q[i]] = a[q[i + 1]];
        a[q[3]] = x;
        a[T].rot(-d);
        a[D].rot(d);
    }
    void Y(int n) {
        if (!n) {
            swap(a[F], a[B]);
            swap(a[T], a[D]);
            a[F].rot(0);
            a[B].rot(0);
            a[R].rot(0);
            a[L].rot(0);
            return;
        }
        int q[4] = {T, n == 1 ? F : B, D, n == 1 ? B : F}, d = n == 1 ? -1 : 1;
        if (n == 1) {
            a[T].rot(0);
            a[B].rot(0);
        } else {
            a[B].rot(0);
            a[D].rot(0);
        }
        Face x = a[q[0]];
        for (int i = 0; i < 3; ++i) a[q[i]] = a[q[i + 1]];
        a[q[3]] = x;
        a[R].rot(-d);
        a[L].rot(d);
    }
    void Z(int n) {
        if (!n) {
            swap(a[T], a[D]);
            swap(a[R], a[L]);
            for (Face &x : a) x.rot(0);
            return;
        }
        int q[4] = {T, n == 1 ? L : R, D, n == 1 ? R : L}, d = n == 1 ? -1 : 1;
        for (int x : q) a[x].rot(n);
        Face x = a[q[0]];
        for (int i = 0; i < 3; ++i) a[q[i]] = a[q[i + 1]];
        a[q[3]] = x;
        a[F].rot(-d);
        a[B].rot(d);
    }
public:
    Cube() : a{Face("WWWW"),Face("RRRR"),Face("YYYY"),Face("BBBB"),Face("OOOO"),Face("GGGG")} {}
    Cube(const vector<string> &s) {
        for (int i = 0; i < 6; ++i) a[i] = Face(s[i]);
        pos();
    }
    bool operator ==(const Cube &x) const { return a == x.a; }
    unsigned hash() const { return (a[0].data << 8 | a[1].data | a[2].data << 4) ^ (a[5].data << 8 | a[4].data | a[3].data << 4); }
    void flip(int x) {
        if (x == 1) Lm();
        else if (x == 2) Lp();
        else if (x == 3) Um();
        else if (x == 4) Up();
        else if (x == 5) Bm();
        else Bp();
        rep = last == x ? rep + 1 : 1;
        last = x;
        ++dep;
    }
    Cube next(int x) const {
        Cube c = *this;
        c.flip(x);
        return c;
    }
    int getLast() const { return last; }
    int getRep() const { return rep; }
    int getDep() const { return dep; }
};

class Solver {
    enum { L = 1, Lp, U, Up, B, Bp };
    vector<vector<Cube>> cur, ans;
    unordered_multimap<unsigned, Cube> mp;
    bool bad(const vector<vector<Cube>> &v, int d, int i, int x) const {
        int p = v[d][i].getLast(), l = min(p, x), r = max(p, x);
        if (p == x && (p == Lp || p == Up || p == Bp)) return true;
        if (p == x && v[d][i].getRep() == 2) return true;
        return r - l == 1 && (l & 1);
    }
    int find(const Cube &c) const {
        auto r = mp.equal_range(c.hash());
        for (auto i = r.first; i != r.second; ++i)
            if (i->second == c) return i->second.getDep();
        return -1;
    }
    void add(int d, Cube c) {
        if (find(c) == -1) {
            ans[d].push_back(c);
            mp.emplace(c.hash(), c);
        }
    }
    void build() {
        ans[0].push_back(Cube());
        mp.emplace(ans[0][0].hash(), ans[0][0]);
        for (int d = 1; d < 8; ++d)
            for (int i = 0; i < (int)ans[d - 1].size(); ++i)
                for (int x = 1; x < 7; ++x)
                    if (!bad(ans, d - 1, i, x)) add(d, ans[d - 1][i].next(x));
    }
public:
    Solver() : cur(8), ans(8) { build(); }
    int run(const vector<string> &s) {
        for (auto &x : cur) x.clear();
        cur[0].push_back(Cube(s));
        int t = find(cur[0][0]);
        if (t != -1) return t;
        for (int d = 1; d < 8; ++d)
            for (int i = 0; i < (int)cur[d - 1].size(); ++i)
                for (int x = 1; x < 7; ++x)
                    if (!bad(cur, d - 1, i, x)) {
                        cur[d].push_back(cur[d - 1][i].next(x));
                        t = find(cur[d].back());
                        if (t != -1) return d + t;
                    }
        return 99;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cin.ignore(2);
    Solver s;
    vector<string> in(6);
    while (n--) {
        for (string &x : in) getline(cin, x);
        cout << s.run(in) << '\n';
        getline(cin, in[0]);
    }
    return 0;
}
