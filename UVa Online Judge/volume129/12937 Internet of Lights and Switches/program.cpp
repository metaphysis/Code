#include <bits/stdc++.h>
using namespace std;

using U64 = unsigned long long;

U64 parseMask(const string &state) {
    U64 mask = 0;
    for (int i = 0; i < (int)state.size(); i++)
        if (state[i] == '1') mask |= 1ULL << i;
    return mask;
}

long long solve(int lightCnt, int switchCnt, int minLen, int maxLen) {
    vector<U64> prefix(switchCnt + 1);
    string state;
    U64 fullMask = (1ULL << lightCnt) - 1;
    for (int i = 1; i <= switchCnt; i++) {
        cin >> state;
        prefix[i] = prefix[i - 1] ^ parseMask(state);
    }
    unordered_map<U64, long long> freq;
    freq.reserve((size_t)(switchCnt + 1) * 2);
    long long answer = 0;
    for (int right = 1; right <= switchCnt; right++) {
        int addPos = right - minLen, removePos = right - maxLen - 1;
        if (addPos >= 0) freq[prefix[addPos]]++;
        if (removePos >= 0) {
            auto it = freq.find(prefix[removePos]);
            --it->second;
            if (it->second == 0) freq.erase(it);
        }
        U64 need = prefix[right] ^ fullMask;
        auto it = freq.find(need);
        if (it != freq.end()) answer += it->second;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int lightCnt, switchCnt, minLen, maxLen, caseNo = 1;
    while (cin >> lightCnt >> switchCnt >> minLen >> maxLen) {
        cout << "Case " << caseNo++ << ": ";
        cout << solve(lightCnt, switchCnt, minLen, maxLen) << '\n';
    }
    return 0;
}
