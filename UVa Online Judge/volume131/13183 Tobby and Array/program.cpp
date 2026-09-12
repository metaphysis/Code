// Tobby and Array 
// UVa ID: 13183
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 2.550s

#include <bits/stdc++.h>
using namespace std;

class FastInput {
private:
    static const int bufSize = 1 << 20;
    int idx, size;
    char buf[bufSize];

    char getChar() {
        if (idx >= size) {
            size = fread(buf, 1, bufSize, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }

public:
    FastInput() : idx(0), size(0) {}

    bool readInt(int &x) {
        char c = getChar();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (!c) return false;
        }
        int sign = 1;
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = getChar();
        }
        x *= sign;
        return true;
    }
};

class WaveletMatrix {
private:
    int n, bits;
    vector<int> values, mid;
    vector<vector<int>> pref;

public:
    WaveletMatrix(const vector<int> &arr) {
        n = static_cast<int>(arr.size());
        values = arr;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        int m = static_cast<int>(values.size());
        bits = 1;
        while ((1 << bits) < m) bits++;
        vector<int> cur(n), nxt(n);
        for (int i = 0; i < n; i++)
            cur[i] = lower_bound(values.begin(), values.end(), arr[i]) - values.begin();
        pref.assign(bits, vector<int>(n + 1));
        mid.assign(bits, 0);
        for (int lev = 0; lev < bits; lev++) {
            int bit = bits - lev - 1;
            for (int i = 0; i < n; i++)
                pref[lev][i + 1] = pref[lev][i] + (((cur[i] >> bit) & 1) == 0);
            int zeroCnt = pref[lev][n];
            mid[lev] = zeroCnt;
            int p0 = 0, p1 = zeroCnt;
            for (int i = 0; i < n; i++) {
                if (((cur[i] >> bit) & 1) == 0)
                    nxt[p0++] = cur[i];
                else
                    nxt[p1++] = cur[i];
            }
            cur.swap(nxt);
        }
    }

    int kth(int l, int r, int k) {
        int rank = 0;
        for (int lev = 0; lev < bits; lev++) {
            int leftZero = pref[lev][l];
            int rightZero = pref[lev][r];
            int zeroCnt = rightZero - leftZero;
            int bit = bits - lev - 1;
            if (k <= zeroCnt) {
                l = leftZero;
                r = rightZero;
            } else {
                k -= zeroCnt;
                l = mid[lev] + l - leftZero;
                r = mid[lev] + r - rightZero;
                rank |= 1 << bit;
            }
        }
        return values[rank];
    }
};

int main() {
    FastInput input;
    int n, q;
    while (input.readInt(n) && input.readInt(q)) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            input.readInt(arr[i]);
        WaveletMatrix wm(arr);
        string output;
        output.reserve(static_cast<size_t>(q) * 12);
        for (int i = 0; i < q; i++) {
            int l, r, k;
            input.readInt(l);
            input.readInt(r);
            input.readInt(k);
            int ans = wm.kth(l - 1, r, k);
            output += to_string(ans);
            output.push_back('\n');
        }
        fwrite(output.data(), 1, output.size(), stdout);
    }
    return 0;
}
