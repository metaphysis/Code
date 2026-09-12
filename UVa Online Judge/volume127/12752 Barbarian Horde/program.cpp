#include <bits/stdc++.h>
using namespace std;

const long long maxCount = LLONG_MAX;
long long dp[24][25][2];

long long addCount(long long a, long long b) {
    if (a >= maxCount - b) return maxCount;
    return a + b;
}

void initDp(int maxLen) {
    int m, r, i;
    for (r = 0; r <= maxLen; ++r) {
        dp[0][r][0] = 0;
        dp[0][r][1] = 0;
    }
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    for (m = 1; m <= maxLen; ++m) {
        for (r = 0; r <= m; ++r) {
            dp[m][r][0] = 0;
            for (i = 0; i < r; ++i)
                dp[m][r][0] = addCount(dp[m][r][0], dp[m - 1][i][1]);
            dp[m][r][1] = 0;
            for (i = r; i < m; ++i)
                dp[m][r][1] = addCount(dp[m][r][1], dp[m - 1][i][0]);
        }
    }
}

void removeChar(char chars[], int &len, int pos) {
    int i;
    for (i = pos; i + 1 < len; ++i)
        chars[i] = chars[i + 1];
    --len;
}

string getAnswer(string word, long long rankValue) {
    char chars[24];
    string answer;
    int len, pos, i, nextDir;
    len = static_cast<int>(word.size());
    sort(word.begin(), word.end());
    for (i = 0; i < len; ++i)
        chars[i] = word[i];
    for (pos = 0; pos < static_cast<int>(word.size()); ++pos) {
        for (i = 0; i < len; ++i) {
            if (pos > 0 && pos % 2 == 1 && chars[i] <= answer.back()) continue;
            if (pos > 0 && pos % 2 == 0 && chars[i] >= answer.back()) continue;
            nextDir = pos % 2 == 0 ? 1 : 0;
            if (rankValue > dp[len - 1][i][nextDir]) {
                rankValue -= dp[len - 1][i][nextDir];
                continue;
            }
            answer += chars[i];
            removeChar(chars, len, i);
            break;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases, caseId;
    string word;
    long long rankValue;
    initDp(23);
    cin >> testCases;
    for (caseId = 1; caseId <= testCases; ++caseId) {
        cin >> word >> rankValue;
        cout << "Case " << caseId << ": " << getAnswer(word, rankValue) << '\n';
    }
    return 0;
}
