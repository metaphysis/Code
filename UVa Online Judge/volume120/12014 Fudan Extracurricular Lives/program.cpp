#include <bits/stdc++.h>
using namespace std;

int allCnt[27];
int hiddenCnt[27];
int needSentence;
int bestScore;
vector<vector<int> > declaredComps;
vector<int> declaredChunk;
vector<vector<int> > currentComps;
vector<int> currentChunk;

int tileId(string s) {
    int suit = 0;
    if (s[1] == 'B')
        suit = 1;
    else if (s[1] == 'M')
        suit = 2;
    return suit * 9 + s[0] - '1';
}

char tileSuit(int id) {
    if (id / 9 == 0)
        return 'D';
    if (id / 9 == 1)
        return 'B';
    return 'M';
}

int calcScore(bool sevenPairs, vector<vector<int> > &comps, vector<int> &isChunk) {
    int score = 1, i, j;
    bool pure = true;
    int firstSuit = -1;
    for (i = 0; i < 27; i++)
        if (allCnt[i] > 0) {
            if (firstSuit == -1)
                firstSuit = i / 9;
            else if (firstSuit != i / 9)
                pure = false;
            if (allCnt[i] == 4)
                score++;
        }
    bool sky = true, chunkious = true, royal = true;
    for (i = 0; i < (int)comps.size(); i++) {
        bool hasEdge = false;
        for (j = 0; j < (int)comps[i].size(); j++) {
            int num = comps[i][j] % 9 + 1;
            if (num == 1 || num == 9)
                hasEdge = true;
            if (num != 2 && num != 5 && num != 8)
                royal = false;
        }
        if (!hasEdge)
            sky = false;
        if (comps[i].size() == 3 && !isChunk[i])
            chunkious = false;
    }
    if (sevenPairs)
        score += 2;
    if (pure)
        score += 2;
    if (sky)
        score += 2;
    if (!sevenPairs && chunkious) {
        score++;
        if (royal)
            score += 2;
    }
    return score;
}

void dfsRegular(int rest[], int sentenceCnt, bool pairUsed) {
    int first = -1, i;
    for (i = 0; i < 27; i++)
        if (rest[i] > 0) {
            first = i;
            break;
        }
    if (first == -1) {
        if (sentenceCnt == needSentence && pairUsed)
            bestScore = max(bestScore, calcScore(false, currentComps, currentChunk));
        return;
    }
    if (!pairUsed && rest[first] >= 2) {
        rest[first] -= 2;
        vector<int> comp(2, first);
        currentComps.push_back(comp);
        currentChunk.push_back(0);
        dfsRegular(rest, sentenceCnt, true);
        currentChunk.pop_back();
        currentComps.pop_back();
        rest[first] += 2;
    }
    if (sentenceCnt < needSentence && rest[first] >= 3) {
        rest[first] -= 3;
        vector<int> comp(3, first);
        currentComps.push_back(comp);
        currentChunk.push_back(1);
        dfsRegular(rest, sentenceCnt + 1, pairUsed);
        currentChunk.pop_back();
        currentComps.pop_back();
        rest[first] += 3;
    }
    int num = first % 9;
    if (sentenceCnt < needSentence && num <= 6 && rest[first + 1] > 0 && rest[first + 2] > 0) {
        rest[first]--;
        rest[first + 1]--;
        rest[first + 2]--;
        vector<int> comp;
        comp.push_back(first);
        comp.push_back(first + 1);
        comp.push_back(first + 2);
        currentComps.push_back(comp);
        currentChunk.push_back(0);
        dfsRegular(rest, sentenceCnt + 1, pairUsed);
        currentChunk.pop_back();
        currentComps.pop_back();
        rest[first]++;
        rest[first + 1]++;
        rest[first + 2]++;
    }
}

void solveSevenPairs() {
    int cnt[27], pairCnt = 0, i;
    vector<vector<int> > comps;
    vector<int> isChunk;
    for (i = 0; i < 27; i++) {
        cnt[i] = allCnt[i];
        if (cnt[i] % 2 != 0)
            return;
        pairCnt += cnt[i] / 2;
        while (cnt[i] >= 2) {
            vector<int> comp(2, i);
            comps.push_back(comp);
            isChunk.push_back(0);
            cnt[i] -= 2;
        }
    }
    if (pairCnt == 7)
        bestScore = max(bestScore, calcScore(true, comps, isChunk));
}

void readDeclared(string s) {
    declaredComps.clear();
    declaredChunk.clear();
    if (s == "NONE")
        return;
    for (int i = 0; i < (int)s.size();) {
        int id = tileId(s.substr(i, 2)), j = i;
        vector<int> comp;
        while (j < (int)s.size() && tileId(s.substr(j, 2)) == id) {
            comp.push_back(id);
            j += 2;
        }
        declaredComps.push_back(comp);
        declaredChunk.push_back(1);
        i = j;
    }
}

int getScore(string hidden, string declared, int add) {
    int i, rest[27];
    memset(allCnt, 0, sizeof(allCnt));
    memset(hiddenCnt, 0, sizeof(hiddenCnt));
    for (i = 0; i < (int)hidden.size(); i += 2) {
        int id = tileId(hidden.substr(i, 2));
        allCnt[id]++;
        hiddenCnt[id]++;
    }
    if (declared != "NONE")
        for (i = 0; i < (int)declared.size(); i += 2)
            allCnt[tileId(declared.substr(i, 2))]++;
    readDeclared(declared);
    allCnt[add]++;
    hiddenCnt[add]++;
    bestScore = -1;
    currentComps = declaredComps;
    currentChunk = declaredChunk;
    needSentence = 4 - (int)declaredComps.size();
    for (i = 0; i < 27; i++)
        rest[i] = hiddenCnt[i];
    dfsRegular(rest, 0, false);
    if (declaredComps.empty())
        solveSevenPairs();
    return bestScore;
}

bool canUseSuit(string hidden, string declared, int add) {
    int used[3] = {0, 0, 0}, i;
    for (i = 0; i < (int)hidden.size(); i += 2)
        used[tileId(hidden.substr(i, 2)) / 9] = 1;
    if (declared != "NONE")
        for (i = 0; i < (int)declared.size(); i += 2)
            used[tileId(declared.substr(i, 2)) / 9] = 1;
    used[add / 9] = 1;
    return used[0] + used[1] + used[2] <= 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t, i;
    cin >> t;
    for (i = 1; i <= t; i++) {
        string hidden, declared;
        cin >> hidden >> declared;
        memset(allCnt, 0, sizeof(allCnt));
        for (int j = 0; j < (int)hidden.size(); j += 2)
            allCnt[tileId(hidden.substr(j, 2))]++;
        if (declared != "NONE")
            for (int j = 0; j < (int)declared.size(); j += 2)
                allCnt[tileId(declared.substr(j, 2))]++;
        vector<int> scores(27, -1);
        for (int add = 0; add < 27; add++) {
            if (allCnt[add] == 4 || !canUseSuit(hidden, declared, add))
                continue;
            scores[add] = getScore(hidden, declared, add);
        }
        cout << "Case #" << i << ":\n";
        bool found = false;
        for (int add = 0; add < 27; add++)
            if (scores[add] >= 0) {
                found = true;
                cout << char('1' + add % 9) << tileSuit(add) << ": " << scores[add] << "\n";
            }
        if (!found)
            cout << "NONE\n";
    }
    return 0;
}
