// Ants Aphids and a Ladybug
// UVa ID: 10939
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

#define INF 0x3fffffff
#define N 8192
#define K 1024

int nextEdge[2 * N], adjEdge[2 * N], vertexAnt[N], antPos[K], chaseCount[K];
int distGot[N], distToAnt[N], antOwner[N], movedFlag[N];
int nodeCount, antCount, edgeId;

void chaseAnt(int parent, int node, int timeLeft) {
    if (distToAnt[node] == INF || timeLeft == 0) return;
    if (node == antPos[antOwner[node]]) return;
    if (!movedFlag[antOwner[node]] && distToAnt[node] <= timeLeft) {
        vertexAnt[antPos[antOwner[node]]] = 0;
        distToAnt[antPos[antOwner[node]]] = INF;
        vertexAnt[node] = antOwner[node];
        antPos[antOwner[node]] = node;
        movedFlag[antOwner[node]] = 1;
        timeLeft = distToAnt[node];
    } else if (movedFlag[antOwner[node]] && distToAnt[node] < timeLeft) {
        timeLeft = distToAnt[node];
    }
    for (int i = nextEdge[node]; i != 0; i = nextEdge[i]) {
        if (adjEdge[i] != parent)
            chaseAnt(node, adjEdge[i], timeLeft);
    }
}

void computeDistances(int parent, int node) {
    if (vertexAnt[node] > 0) {
        distToAnt[node] = 0;
        antOwner[node] = vertexAnt[node];
        return;
    }
    distToAnt[node] = INF;
    antOwner[node] = 0;
    for (int i = nextEdge[node]; i != 0; i = nextEdge[i]) {
        int child = adjEdge[i];
        if (child == parent) continue;
        computeDistances(node, child);
        if ((distToAnt[child] + 1) < distToAnt[node] ||
            ((distToAnt[child] + 1) == distToAnt[node] && antOwner[child] < antOwner[node])) {
            distToAnt[node] = distToAnt[child] + 1;
            antOwner[node] = antOwner[child];
        }
    }
}

int main() {
    int i, x, y, z;
    while (scanf("%d", &nodeCount) == 1 && nodeCount > 0) {
        for (i = 0; i <= nodeCount; i++) nextEdge[i] = 0;
        for (z = nodeCount + 1, i = 1; i < nodeCount && scanf("%d %d", &x, &y) == 2; i++) {
            adjEdge[z] = y;
            nextEdge[z] = nextEdge[x];
            nextEdge[x] = z++;
            adjEdge[z] = x;
            nextEdge[z] = nextEdge[y];
            nextEdge[y] = z++;
        }
        for (i = 0; i <= nodeCount; i++) vertexAnt[i] = 0;
        scanf("%d", &antCount);
        for (i = 1; i <= antCount; i++) {
            chaseCount[i] = 0;
            scanf("%d", &antPos[i]);
            vertexAnt[antPos[i]] = i;
        }
        for (scanf("%d", &y); y-- > 0 && scanf("%d", &x) == 1; ) {
            for (i = 0; i <= nodeCount; i++) distToAnt[i] = INF;
            for (i = 0; i <= nodeCount; i++) movedFlag[i] = 0;
            computeDistances(0, x);
            chaseAnt(0, x, INF - 1);
            chaseCount[vertexAnt[x]]++;
        }
        for (i = 1; i <= antCount; i++)
            printf("%d %d\n", antPos[i], chaseCount[i]);
    }
    return 0;
}
