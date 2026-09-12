#include <bits/stdc++.h>
using namespace std;

int getDir(char ch) {
    if (ch == 'N') return 0;
    if (ch == 'E') return 1;
    if (ch == 'S') return 2;
    return 3;
}

bool cmpFinish(int st, int nst, int limitLen, const vector<int> &arr) {
    for (int k = 0; k < limitLen; k++)
        if (arr[st + k] != (arr[nst + limitLen - 1 - k] + 2) % 4)
            return false;
    return true;
}

bool cmpOne(int st, int nst, int limitLen, int flag, const vector<int> &arr) {
    int num0[4] = {0, 0, 0, 0}, num1[4] = {0, 0, 0, 0};
    for (int i = st, j = nst; i < st + limitLen; i++, j++) {
        num0[arr[i]]++;
        num1[(arr[j] + 2) % 4]++;
        bool sameNum = true;
        for (int k = 0; k < 4; k++)
            if (num0[k] != num1[k])
                sameNum = false;
        if (!sameNum)
            continue;
        bool samePart = true;
        for (int k = 0; k <= i - st; k++)
            if (arr[st + k] != (arr[j - k] + 2) % 4)
                samePart = false;
        if (!samePart)
            continue;
        int restLen = st + limitLen - i - 1;
        if (flag == 0 && cmpOne(i + 1, j + 1, restLen, 1, arr))
            return true;
        if (cmpFinish(i + 1, j + 1, restLen, arr))
            return true;
    }
    return false;
}

int solve() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, caseId = 1;
    while (cin >> n && n) {
        vector<char> dirs(n);
        vector<int> lens(n);
        int unit = 0;
        for (int i = 0; i < n; i++) {
            cin >> dirs[i] >> lens[i];
            unit = __gcd(unit, lens[i]);
        }
        vector<int> arr;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < lens[i] / unit; j++)
                arr.push_back(getDir(dirs[i]));
        int total = arr.size();
        cout << "Polygon " << caseId++ << ": ";
        if (total % 2 != 0) {
            cout << "Impossible\n";
            continue;
        }
        vector<int> all = arr;
        all.insert(all.end(), arr.begin(), arr.end());
        int half = total / 2;
        bool possible = false;
        for (int st = 0; st < half && !possible; st++) {
            int nst = st + half;
            int num0[4] = {0, 0, 0, 0}, num1[4] = {0, 0, 0, 0};
            for (int i = st; i < st + half; i++)
                num0[all[i]]++;
            for (int i = nst; i < nst + half; i++)
                num1[(all[i] + 2) % 4]++;
            bool sameNum = true;
            for (int i = 0; i < 4; i++)
                if (num0[i] != num1[i])
                    sameNum = false;
            if (!sameNum)
                continue;
            possible = cmpOne(st, nst, half, 0, all);
        }
        cout << (possible ? "Possible\n" : "Impossible\n");
    }
    return 0;
}

int main() {
    return solve();
}
