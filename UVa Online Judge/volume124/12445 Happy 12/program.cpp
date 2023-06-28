// Happy 12
// UVa ID: 12445
// Verdict: Accepted
// Submission Date: 2023-06-28
// UVa Run Time: 7.560s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;

static long long mask;

inline void _set(int p, long long v) { mask |= v << (4 * p); }
inline int _get(const long long &u, int p) { return (u >> (4 * p)) & 15LL; }

void lc(const long long &u) {
	mask = u & 0x0fffff000000LL | 0x0000000fffffLL & (u >> 4);
	_set(5, _get(u, 11));
	_set(11, _get(u, 0));
}
void lcc(const long long &u) {
	mask = u & 0x0fffff000000LL | 0x000000fffff0LL & (u << 4);
	_set(0, _get(u, 11));
	_set(11, _get(u, 5));
}
void rc(const long long &u) {
	mask = u & 0x0000000fffffLL | 0x0ffffff00000LL & (u >> 4);
	_set(11, _get(u, 5));
}
void rcc(const long long &u) {
	mask = u & 0x0000000fffffLL | 0xffffff000000LL & (u << 4);
	_set(5, _get(u, 11));
}
void wc(const long long &u) {
	mask = 0x0fffffffffffLL & (u >> 4);
	_set(11, _get(u, 0));
}
void wcc(const long long &u) {
	mask = 0xfffffffffff0LL & (u << 4);
	_set(0, _get(u, 11));
}

static void (*F[])(const long long&) = {lc, lcc, rc, rcc, wc, wcc};

unordered_map<long long, int> forwarded;

void trick() {
    int cnt = 0;
	long long u = 0;
	for (int i = 0; i < 12; i++) u |= (long long)i << (4 * i);
	forwarded[u] = 0;
    queue<long long> q1; q1.push(u);
    queue<int> q2; q2.push(0);
    while (!q1.empty()) {
		u = q1.front(); q1.pop();
        cnt = q2.front(); q2.pop();
		for (int i = 0; i < 6; i++) {
			F[i](u);
			if (forwarded.find(mask) != forwarded.end()) continue;
			if (cnt + 1 < 10) {
                forwarded[mask] = cnt + 1;
				q1.push(mask);
                q2.push(cnt + 1);
            }
		}
    }
}

void bfs(long long u) {
	if (forwarded.find(u) != forwarded.end()) {
        cout << forwarded[u] << '\n';
        return;
    }
    int cnt = 0;
	unordered_map<long long, int> backwarded;
	backwarded[u] = 0;
    queue<long long> q1; q1.push(u);
    queue<int> q2; q2.push(0);
    while (!q1.empty()) {
		u = q1.front(); q1.pop();
        cnt = q2.front(); q2.pop();
		for (int i = 0; i < 6; i++) {
			F[i](u);
			if (forwarded.find(mask) != forwarded.end()) {
                cout << forwarded[mask] + cnt + 1 << '\n';
                return;
            }
            if (backwarded.find(mask) != backwarded.end()) continue;
			if (cnt + 1 < 10) {
                backwarded[mask] = cnt + 1;
				q1.push(mask);
                q2.push(cnt + 1);
            }
		}
	}
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	trick();
	int T; cin >> T;
	while (T--) {
        long long u = 0, v;
		for (int i = 0; i < 12; i++) {
            cin >> v; v--;
            u |= v << (4 * i);
		}
		bfs(u);
	}
	return 0;
}
