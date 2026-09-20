#include <bits/stdc++.h>
using namespace std;

const int maxN = 6066010;
int parent[maxN];

int findRoot(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findRoot(parent[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        stringstream input(line);
        vector<int> args;
        int value;
        char cmd;
        if (!(input >> cmd)) continue;
        cmd = static_cast<char>(tolower(static_cast<unsigned char>(cmd)));
        while (input >> value) args.push_back(value);
        if (cmd == 'd') {
            int planetCnt = args[0];
            for (int i = 0; i <= planetCnt; ++i) parent[i] = i;
            continue;
        }
        int src = args[0], dst = args[1], pairCnt = 1;
        int srcStep = 0, dstStep = 0;
        if (args.size() == 3) {
            pairCnt = args[2];
            dstStep = 1;
        } else if (args.size() == 4) {
            pairCnt = args[2];
            dstStep = args[3];
        } else if (args.size() == 5) {
            pairCnt = args[2];
            dstStep = args[3];
            srcStep = args[4];
        }
        if (cmd == 'c') {
            if (srcStep == 0 && dstStep == 0) pairCnt = 1;
            for (int i = src, j = dst, k = 0; k < pairCnt; i += srcStep, j += dstStep, ++k) {
                int srcRoot = findRoot(i), dstRoot = findRoot(j);
                parent[dstRoot] = srcRoot;
            }
        } else {
            int connected = 0, disconnected = 0;
            for (int i = src, j = dst, k = 0; k < pairCnt; i += srcStep, j += dstStep, ++k) {
                int srcRoot = findRoot(i), dstRoot = findRoot(j);
                if (srcRoot == dstRoot) ++connected;
                else ++disconnected;
            }
            cout << connected << " - " << disconnected << '\n';
        }
    }
    return 0;
}
