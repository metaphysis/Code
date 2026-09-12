// Naming Babies
// UVa ID: 12594
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.500s

#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 62);

struct Line {
    long long m, b;
    long long getValue(long long x) const {
        return m * x + b;
    }
};

class ConvexHull {
private:
    deque<Line> hull;
    bool isBad(const Line &first, const Line &second, const Line &third) {
        __int128 left = (__int128)(second.b - first.b) * (second.m - third.m);
        __int128 right = (__int128)(third.b - second.b) * (first.m - second.m);
        return left >= right;
    }
public:
    void clear() {
        hull.clear();
    }
    void addLine(long long m, long long b) {
        Line line = {m, b};
        while (hull.size() >= 2 && isBad(hull[hull.size() - 2], hull.back(), line))
            hull.pop_back();
        hull.push_back(line);
    }
    long long query(long long x) {
        while (hull.size() >= 2 && hull[0].getValue(x) >= hull[1].getValue(x))
            hull.pop_front();
        return hull.front().getValue(x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseId = 1; caseId <= testCases; caseId++) {
        string perfectName, name;
        int partCount;
        cin >> perfectName >> partCount;
        cin >> name;
        int length = name.size();
        int pos[26];
        for (int i = 0; i < 26; i++)
            pos[perfectName[i] - 'a'] = i;
        vector<long long> sumPos(length + 1, 0), sumIndexPos(length + 1, 0), sumPosSquare(length + 1, 0);
        for (int i = 0; i < length; i++) {
            long long value = pos[name[i] - 'a'];
            sumPos[i + 1] = sumPos[i] + value;
            sumIndexPos[i + 1] = sumIndexPos[i] + 1LL * i * value;
            sumPosSquare[i + 1] = sumPosSquare[i] + value * value;
        }
        vector<long long> prevDp(length + 1, inf), curDp(length + 1, inf);
        prevDp[0] = 0;
        for (int part = 1; part <= partCount; part++) {
            fill(curDp.begin(), curDp.end(), inf);
            ConvexHull hull;
            for (int right = part; right <= length; right++) {
                int left = right - 1;
                if (prevDp[left] < inf / 2) {
                    long long intercept = prevDp[left] - sumIndexPos[left] + sumPosSquare[left] + 1LL * left * sumPos[left];
                    hull.addLine(-left, intercept);
                }
                long long best = hull.query(sumPos[right]);
                curDp[right] = sumIndexPos[right] - sumPosSquare[right] + best;
            }
            prevDp.swap(curDp);
        }
        cout << "Case " << caseId << ": " << prevDp[length] << '\n';
    }
    return 0;
}
