#include <bits/stdc++.h>
using namespace std;

int getDist(int a, int b, int size) {
    int ax, ay, bx, by;
    ax = (a - 1) / size;
    ay = (a - 1) % size;
    bx = (b - 1) / size;
    by = (b - 1) % size;
    return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}

int getGuess(const vector<int> &can, int n, bool high) {
    int i;
    if (high) {
        for (i = n; i >= 1; i--)
            if (can[i]) return i;
    } else {
        for (i = 1; i <= n; i++)
            if (can[i]) return i;
    }
    return 0;
}

void printLine(int guess, const string &ans) {
    cout << setw(3) << guess << "? - " << ans << '\\n';
}

int main() {
    int n, m, size, guess, preGuess, curDist, preDist, rel, xRel, i;
    bool firstCase, high;
    string ans;
    firstCase = true;
    while (cin >> n >> m) {
        if (!firstCase) cout << '\\n';
        firstCase = false;
        size = sqrt(n);
        vector<int> can(n + 1, 1);
        guess = 1;
        if (m == guess) {
            printLine(guess, "YES!!");
            continue;
        }
        printLine(guess, "CLOSER");
        can[guess] = 0;
        preGuess = guess;
        high = true;
        while (true) {
            guess = getGuess(can, n, high);
            if (m == guess) {
                printLine(guess, "YES!!");
                break;
            }
            curDist = getDist(m, guess, size);
            preDist = getDist(m, preGuess, size);
            rel = (curDist > preDist) - (curDist < preDist);
            if (rel < 0) ans = "CLOSER";
            else if (rel > 0) ans = "FARTHER";
            else ans = "SAME";
            printLine(guess, ans);
            for (i = 1; i <= n; i++) {
                if (!can[i]) continue;
                xRel = (getDist(i, guess, size) > getDist(i, preGuess, size)) - (getDist(i, guess, size) < getDist(i, preGuess, size));
                if (xRel != rel) can[i] = 0;
            }
            can[guess] = 0;
            preGuess = guess;
            high = !high;
        }
    }
    return 0;
}
