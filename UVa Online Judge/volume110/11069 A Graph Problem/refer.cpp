#include <bits/stdc++.h>
using namespace std;
const int limN = 65;

int N;
long long NB;
long long adj[limN];
int ansS, ansCnt;

void bruta(int pos=0, long long msk=0LL, int cnt=0) {
    if(msk==NB) {
        ansCnt++;
        ansS = max(ansS, cnt);
        return;
    }
    for(int i=pos; i<N; i++) {
        if(!((1LL<<i) & msk))
            bruta(i+1, msk | adj[i], cnt+1);
    }
}

void testCase() {
    ansCnt = ansS = 0;
    
    int E;
    scanf("%d%d", &N, &E);
    NB = (1LL<<N)-1;
    for(int i=0; i<N; i++)
        adj[i] = (1LL<<i);
    while(E--) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a] |= (1LL<<b);
        adj[b] |= (1LL<<a);
    }
    bruta();

    printf("%d\n%d\n", ansCnt, ansS);
}

int main() {
    int tc;
    for(scanf("%d", &tc); tc; tc--)
        testCase();
}
