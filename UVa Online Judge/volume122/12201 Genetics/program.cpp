#include <bits/stdc++.h>
using namespace std;

int parentArr[110];

int findRoot(int x) {
    if (parentArr[x] == x)
        return x;
    return parentArr[x] = findRoot(parentArr[x]);
}

void mergeSet(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y)
        parentArr[x] = y;
}

int solve(string dna) {
    int n = dna.size(), pairCount = n / 2, vertexCount = 0, sameFaceCount = 0;
    int firstPos[26], secondPos[26];
    bool firstFace[26], secondFace[26], visited[26];
    memset(firstPos, -1, sizeof(firstPos));
    memset(secondPos, -1, sizeof(secondPos));
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++) {
        int id = tolower(dna[i]) - 'a';
        bool face = islower(dna[i]);
        if (firstPos[id] == -1) {
            firstPos[id] = i;
            firstFace[id] = face;
        } else {
            secondPos[id] = i;
            secondFace[id] = face;
        }
    }
    for (int i = 0; i < n; i++)
        parentArr[i] = i;
    for (int id = 0; id < 26; id++) {
        if (firstPos[id] == -1)
            continue;
        int p = firstPos[id], q = secondPos[id];
        if (firstFace[id] == secondFace[id]) {
            sameFaceCount++;
            mergeSet(p, q);
            mergeSet((p + 1) % n, (q + 1) % n);
        } else {
            mergeSet(p, (q + 1) % n);
            mergeSet((p + 1) % n, q);
        }
    }
    for (int i = 0; i < n; i++)
        if (findRoot(i) == i)
            vertexCount++;
    int euler = 1 - pairCount + vertexCount, result;
    if (sameFaceCount > 0) {
        result = 2 - euler;
        if (result == 0)
            cout << "none\n";
        else if (result == 1)
            cout << "1 arm\n";
        else
            cout << result << " arms\n";
    } else {
        result = (2 - euler) / 2;
        if (result == 0)
            cout << "none\n";
        else if (result == 1)
            cout << "1 leg\n";
        else
            cout << result << " legs\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string dna;
    while (cin >> dna && dna != "END")
        solve(dna);
    return 0;
}
