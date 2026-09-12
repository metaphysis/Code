#include <bits/stdc++.h>
using namespace std;

const int maxN = 3005;
const double pi = acos(-1.0);

struct Arc {
    double angle;
    int to;
};

int n, m, compNum;
int xPos[maxN], yPos[maxN], height[maxN];
int belong[maxN], compHeight[maxN], compLevel[maxN];
bool vertexSea[maxN], compSea[maxN], vis[maxN];
string pointName[maxN];
map<string, int> pointId;
map<pair<int, int>, bool> edgeSet;
vector<Arc> edgeList[maxN];
vector<int> compEdge[maxN], heightList, lakeList;

void addEdge(int a, int b) {
    edgeSet[make_pair(a, b)] = true;
    double angle = atan2((double)(yPos[b] - yPos[a]), (double)(xPos[b] - xPos[a]));
    edgeList[a].push_back({angle, b});
}

void fillComp(int x, int id) {
    if (vis[x]) return;
    vis[x] = true;
    belong[x] = id;
    for (Arc item : edgeList[x])
        if (height[item.to] == height[x]) fillComp(item.to, id);
}

void findOuter() {
    for (int i = 1; i <= n; i++) {
        sort(edgeList[i].begin(), edgeList[i].end(), [](const Arc &a, const Arc &b) {
            return a.angle < b.angle;
        });
        vertexSea[i] = false;
        int size = edgeList[i].size();
        for (int j = 0; j < size; j++) {
            int next = (j + 1) % size;
            double gap = edgeList[i][next].angle - edgeList[i][j].angle;
            if (next == 0) gap += 2 * pi;
            if (gap >= pi) vertexSea[i] = true;
            int a = edgeList[i][j].to, b = edgeList[i][next].to;
            if (!edgeSet.count(make_pair(a, b))) vertexSea[i] = true;
        }
    }
}

void buildComp() {
    memset(vis, false, sizeof(vis));
    compNum = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            ++compNum;
            compHeight[compNum] = height[i];
            fillComp(i, compNum);
        }
    for (int i = 1; i <= compNum; i++) compSea[i] = false;
    for (int i = 1; i <= n; i++)
        if (vertexSea[i]) compSea[belong[i]] = true;
    for (int i = 1; i <= compNum; i++) compEdge[i].clear();
    for (int i = 1; i <= n; i++)
        for (Arc item : edgeList[i])
            if (belong[i] != belong[item.to]) compEdge[belong[i]].push_back(belong[item.to]);
}

void drain(int x, int waterHeight) {
    if (vis[x]) return;
    vis[x] = true;
    for (int to : compEdge[x])
        if (compHeight[to] < waterHeight) drain(to, waterHeight);
}

void calcLevel() {
    for (int i = 1; i <= compNum; i++) compLevel[i] = 0;
    for (int waterHeight : heightList) {
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= compNum; i++)
            if (compSea[i] && compHeight[i] < waterHeight) drain(i, waterHeight);
        for (int i = 1; i <= compNum; i++)
            if (!vis[i]) compLevel[i] = waterHeight;
    }
}

void findLake(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (Arc item : edgeList[x])
        if (height[item.to] < compLevel[belong[item.to]] && compLevel[belong[x]] == compLevel[belong[item.to]]) findLake(item.to);
}

void output() {
    lakeList.clear();
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (!vis[i] && height[i] < compLevel[belong[i]]) {
            lakeList.push_back(compLevel[belong[i]]);
            findLake(i);
        }
    sort(lakeList.begin(), lakeList.end());
    if (lakeList.empty()) {
        cout << "  0\n";
        return;
    }
    for (int lakeHeight : lakeList) cout << "  " << lakeHeight << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    while (cin >> n >> m && (n || m)) {
        heightList.clear();
        pointId.clear();
        edgeSet.clear();
        for (int i = 1; i <= n; i++) {
            cin >> pointName[i] >> xPos[i] >> yPos[i] >> height[i];
            pointId[pointName[i]] = i;
            heightList.push_back(height[i]);
            edgeList[i].clear();
        }
        sort(heightList.begin(), heightList.end());
        heightList.erase(unique(heightList.begin(), heightList.end()), heightList.end());
        for (int i = 1; i <= m; i++) {
            string a, b;
            cin >> a >> b;
            addEdge(pointId[a], pointId[b]);
            addEdge(pointId[b], pointId[a]);
        }
        findOuter();
        buildComp();
        calcLevel();
        cout << "Case " << ++caseId << ":\n";
        output();
    }
    return 0;
}
