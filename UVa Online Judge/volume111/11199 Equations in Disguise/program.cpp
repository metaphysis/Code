// Equations in Disguise
// UVa ID: 11199
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 18.390s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void solveCase(int n, int caseNo) {
    vector<string> eqs(n);
    bool appear[13] = {false};
    for (int i = 0; i < n; ++i) {
        cin >> eqs[i];
        for (char c : eqs[i]) appear[c - 'a'] = true;
    }
    string used, unapp;
    for (int i = 0; i < 13; ++i) {
        if (appear[i]) used += char('a' + i);
        else unapp += char('a' + i);
    }
    int unappCnt = unapp.size();
    // 筛选等号候选
    vector<char> candEq;
    for (char c : used) {
        bool ok = true;
        for (const string& s : eqs) {
            int cnt = 0, pos = -1;
            for (int i = 0; i < (int)s.size(); ++i) if (s[i] == c) { ++cnt; pos = i; }
            if (cnt != 1 || pos == 0 || pos == (int)s.size() - 1) { ok = false; break; }
        }
        if (ok) candEq.push_back(c);
    }
    bool possible[13][13], firstSol = true, hasSol = false;
    for (int i = 0; i < 13; ++i) fill(possible[i], possible[i] + 13, true);
    set<int> interUnapp;
    if (unappCnt == 1) for (int s = 0; s < 13; ++s) interUnapp.insert(s);

    int opMap[13], charToDigit[13], nonZero[13];
    for (char eqChar : candEq) {
        int eqIdx = eqChar - 'a';
        vector<string> lefts(n), rights(n);
        bool validEq = true;
        for (int i = 0; i < n; ++i) {
            size_t pos = eqs[i].find(eqChar);
            lefts[i] = eqs[i].substr(0, pos);
            rights[i] = eqs[i].substr(pos + 1);
            if (lefts[i].empty() || rights[i].empty()) { validEq = false; break; }
        }
        if (!validEq) continue;
        string rest;
        for (char c : used) if (c != eqChar) rest += c;
        int K = rest.size();

        for (int addIdx = -1; addIdx < K; ++addIdx)
            for (int mulIdx = -1; mulIdx < K; ++mulIdx) {
                if (addIdx == mulIdx && addIdx >= 0) continue;
                if ((addIdx == -1) + (mulIdx == -1) > unappCnt) continue;
                int digitCnt = K - (addIdx >= 0) - (mulIdx >= 0);
                if (digitCnt > 10) continue;
                fill(opMap, opMap + 13, 0);
                if (addIdx >= 0) opMap[rest[addIdx] - 'a'] = 1;
                if (mulIdx >= 0) opMap[rest[mulIdx] - 'a'] = 2;

                bool addApp = false, mulApp = false;
                for (int i = 0; i < n; ++i) {
                    for (char c : lefts[i]) {
                        if (opMap[c - 'a'] == 1) addApp = true;
                        if (opMap[c - 'a'] == 2) mulApp = true;
                    }
                    for (char c : rights[i]) {
                        if (opMap[c - 'a'] == 1) addApp = true;
                        if (opMap[c - 'a'] == 2) mulApp = true;
                    }
                }
                if ((addIdx >= 0 && !addApp) || (mulIdx >= 0 && !mulApp)) continue;

                vector<string> tokens;
                vector<vector<int>> leftToks(n), rightToks(n);
                vector<vector<char>> leftOps(n), rightOps(n);
                auto getTok = [&](const string& s) {
                    for (int i = 0; i < (int)tokens.size(); ++i) if (tokens[i] == s) return i;
                    tokens.push_back(s);
                    return (int)tokens.size() - 1;
                };
                bool valid = true;
                auto parse = [&](const string& s, vector<int>& toks, vector<char>& ops) {
                    string cur;
                    for (char c : s) {
                        int sym = opMap[c - 'a'];
                        if (sym) {
                            if (cur.empty()) return false;
                            toks.push_back(getTok(cur));
                            ops.push_back(sym == 1 ? '+' : '*');
                            cur.clear();
                        } else cur += c;
                    }
                    if (cur.empty()) return false;
                    toks.push_back(getTok(cur));
                    return true;
                };
                for (int i = 0; i < n; ++i) {
                    if (!parse(lefts[i], leftToks[i], leftOps[i]) || !parse(rights[i], rightToks[i], rightOps[i])) { valid = false; break; }
                }
                if (!valid) continue;

                int T = tokens.size();
                vector<long long> minBase(T), maxBase(T);
                for (int i = 0; i < T; ++i) {
                    int len = tokens[i].size();
                    minBase[i] = (len == 1) ? 0 : pow(10, len - 1);
                    maxBase[i] = (len == 1) ? 9 : minBase[i] * 10 - 1;
                }

                string digitLetters;
                fill(nonZero, nonZero + 13, 0);
                for (const string& t : tokens) if (t.size() > 1) nonZero[t[0] - 'a'] = 1;
                for (char c : rest) if (opMap[c - 'a'] == 0) {
                    if (nonZero[c - 'a']) digitLetters = c + digitLetters;
                    else digitLetters += c;
                }
                vector<int> letter2Tok[13];
                for (int i = 0; i < T; ++i) for (char c : tokens[i]) letter2Tok[c - 'a'].push_back(i);

                auto buildPost = [](const vector<int>& toks, const vector<char>& ops) {
                    vector<int> res; res.reserve(toks.size() + ops.size());
                    int stk[20], sp = 0;
                    res.push_back(toks[0]);
                    for (size_t i = 0; i < ops.size(); ++i) {
                        int p = ops[i] == '+' ? 1 : 2;
                        while (sp && stk[sp - 1] >= p) res.push_back(stk[--sp] == 1 ? -1 : -2);
                        stk[sp++] = p;
                        res.push_back(toks[i + 1]);
                    }
                    while (sp) res.push_back(stk[--sp] == 1 ? -1 : -2);
                    return res;
                };
                vector<vector<int>> leftPost(n), rightPost(n);
                for (int i = 0; i < n; ++i) leftPost[i] = buildPost(leftToks[i], leftOps[i]);
                for (int i = 0; i < n; ++i) rightPost[i] = buildPost(rightToks[i], rightOps[i]);

                vector<long long> tokVal(T, -1);
                int usedMask = 0;
                auto eval = [](const vector<int>& pf, const vector<long long>& vals) {
                    long long stk[20]; int sp = 0;
                    for (int x : pf) {
                        if (x >= 0) stk[sp++] = vals[x];
                        else { long long b = stk[--sp], a = stk[--sp]; stk[sp++] = x == -1 ? a + b : a * b; }
                    }
                    return stk[0];
                };
                auto range = [&](const vector<int>& pf, const vector<long long>& vals) {
                    pair<long long, long long> stk[20]; int sp = 0;
                    for (int x : pf) {
                        if (x >= 0) stk[sp++] = vals[x] == -1 ? make_pair(minBase[x], maxBase[x]) : make_pair(vals[x], vals[x]);
                        else {
                            auto b = stk[--sp], a = stk[--sp];
                            if (x == -1) stk[sp++] = {a.first + b.first, a.second + b.second};
                            else {
                                long long v1 = a.first * b.first, v2 = a.first * b.second, v3 = a.second * b.first, v4 = a.second * b.second;
                                stk[sp++] = {min({v1, v2, v3, v4}), max({v1, v2, v3, v4})};
                            }
                        }
                    }
                    return stk[0];
                };
                auto okEqs = [&]() {
                    for (int i = 0; i < n; ++i) {
                        bool lFull = all_of(leftToks[i].begin(), leftToks[i].end(), [&](int t){ return tokVal[t] != -1; });
                        bool rFull = all_of(rightToks[i].begin(), rightToks[i].end(), [&](int t){ return tokVal[t] != -1; });
                        if (lFull && rFull) { if (eval(leftPost[i], tokVal) != eval(rightPost[i], tokVal)) return false; }
                        else {
                            auto lr = range(leftPost[i], tokVal), rr = range(rightPost[i], tokVal);
                            if (lr.second < rr.first || lr.first > rr.second) return false;
                        }
                    }
                    return true;
                };
                auto record = [&]() {
                    hasSol = true;
                    int sym[13]; fill(sym, sym + 13, -1);
                    for (char c : used) {
                        int ci = c - 'a';
                        if (ci == eqIdx) sym[ci] = 12;
                        else if (opMap[ci] == 1) sym[ci] = 10;
                        else if (opMap[ci] == 2) sym[ci] = 11;
                        else sym[ci] = charToDigit[ci];
                    }
                    bool usedSym[13] = {false};
                    for (char c : used) usedSym[sym[c - 'a']] = true;
                    set<int> remain;
                    for (int s = 0; s < 13; ++s) if (!usedSym[s]) remain.insert(s);
                    for (char c : used) {
                        int ci = c - 'a', s = sym[ci];
                        if (firstSol) { fill(possible[ci], possible[ci] + 13, false); possible[ci][s] = true; }
                        else for (int j = 0; j < 13; ++j) if (j != s) possible[ci][j] = false;
                    }
                    if (unappCnt == 1) {
                        set<int> inter;
                        for (int s : interUnapp) if (remain.count(s)) inter.insert(s);
                        interUnapp = inter;
                    }
                    firstSol = false;
                };
                function<void(int)> dfs = [&](int idx) {
                    if (idx == (int)digitLetters.size()) { record(); return; }
                    char c = digitLetters[idx];
                    int ci = c - 'a', start = nonZero[ci] ? 1 : 0;
                    for (int d = start; d <= 9; ++d) {
                        if (usedMask & (1 << d)) continue;
                        charToDigit[ci] = d; usedMask |= 1 << d;
                        vector<pair<int, long long>> old;
                        bool ok = true;
                        for (int t : letter2Tok[ci]) {
                            const string& tok = tokens[t];
                            long long v = 0; bool full = true;
                            for (char ch : tok) {
                                int dig = charToDigit[ch - 'a'];
                                if (dig == -1) { full = false; break; }
                                v = v * 10 + dig;
                            }
                            if (full) {
                                if (tok.size() > 1 && charToDigit[tok[0] - 'a'] == 0) { ok = false; break; }
                                old.emplace_back(t, tokVal[t]);
                                tokVal[t] = v;
                            }
                        }
                        if (ok && okEqs()) dfs(idx + 1);
                        for (auto& p : old) tokVal[p.first] = p.second;
                        usedMask &= ~(1 << d);
                        charToDigit[ci] = -1;
                    }
                };
                fill(charToDigit, charToDigit + 13, -1);
                dfs(0);
            }
    }

    if (!hasSol) cout << "Case " << caseNo << ": No\n";
    else {
        vector<pair<char, string>> det;
        for (char c = 'a'; c <= 'm'; ++c) {
            int ci = c - 'a';
            if (appear[ci]) {
                int cnt = 0, sym = -1;
                for (int s = 0; s < 13; ++s) if (possible[ci][s]) { ++cnt; sym = s; }
                if (cnt == 1) {
                    string str = sym <= 9 ? to_string(sym) : (sym == 10 ? "+" : sym == 11 ? "*" : "=");
                    det.emplace_back(c, str);
                }
            } else if (unappCnt == 1 && interUnapp.size() == 1) {
                int sym = *interUnapp.begin();
                string str = sym <= 9 ? to_string(sym) : (sym == 10 ? "+" : sym == 11 ? "*" : "=");
                det.emplace_back(c, str);
            }
        }
        if (det.empty()) cout << "Case " << caseNo << ": Oops\n";
        else {
            cout << "Case " << caseNo << ":";
            for (auto& p : det) cout << ' ' << p.first << p.second;
            cout << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int caseNo = 1, n; cin >> n && n; ++caseNo) solveCase(n, caseNo);
    return 0;
}
