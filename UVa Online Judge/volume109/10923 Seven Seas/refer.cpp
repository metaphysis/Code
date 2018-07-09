#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <iostream>
#include <set>
#include <cmath>
#include <cassert>
#include <ctime>
#include <string>

using namespace std;

#define db(x) cout << #x " == " << x << endl
//#define _ << ", " <<
#define iter(a) typeof((a).begin())
#define Tr(a,b) for(iter(b) a = (b).begin(); a != (b).end(); ++a)
#define Fr(a,b,c) for( int a = b ; a < c ; ++a )
#define rF(a,b,c) for( int a = c-1; a>=b ; --a )
#define Rp(a,b) Fr(a,0,b)
#define fr Fr
#define rp Rp
#define cl(a,b) memset(a,b,sizeof(a))
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<double,pair<int,int> > pdi;
typedef vector<pair<int,int> > vpii;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define y1 Y1
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL
#define ULMAX 0xffffffffffffffffULL
#define MAXN 1000
#define MAXM 120000

int k;
char g[11][11];
ull fila[1100000];

int tmp[11][11];
pii p[20];
map<ull,int> M;
//map<ull,ull> back;

int di[] = {-1,-1,0,1,1,1,0,-1};
int dj[] = {0,-1,-1,-1,0,1,1,1};

bool valid(int i, int j) { return i >= 0 && i < 9 && j >= 0 && j < 8; }

pii getCloser(int i, int j, int ii, int jj) {
	int minim = 1000000;
	pii ans;
	rp(d,8) {
		int ni = i+di[d];
		int nj = j+dj[d];
		if (valid(ni,nj) && abs(ni-ii) + abs(nj-jj) < minim) {
			minim = abs(ni-ii) + abs(nj-jj);
			ans = MP(ni,nj);
		}
	}
	return ans;
}

char stor[11][11];

int aff[11][11];
pii ppp[20];
void print(ull h) {
	if (h == -1) return;
	rp(i,9) rp(j,8) stor[i][j] = (g[i][j] == '#') ? '#' : '.';
	cl(aff,0);
	rp(i,k) {
		ppp[i] = MP((h%72)/8, (h%72)%8);
		stor[ppp[i].F][ppp[i].S] = 'E';
		if (!aff[ppp[i].F][ppp[i].S]) aff[ppp[i].F][ppp[i].S] = 1;
		else if (aff[ppp[i].F][ppp[i].S]) aff[ppp[i].F][ppp[i].S] = -1, stor[ppp[i].F][ppp[i].S] = 'X';
		if (g[ppp[i].F][ppp[i].S] == '#') aff[ppp[i].F][ppp[i].S] = -1, stor[ppp[i].F][ppp[i].S] = '#';
		h/=72;
	}
	int i = (h%72)/8;
	int j = (h%72)%8;
	if (stor[i][j] == '.') stor[i][j] = 'S';
	rp(i,9) {
		rp(j,8) printf("%c", stor[i][j]);
		puts("");
	}
	puts("");
}

int bfs(ull hash) {
	ull h;
	fila[0] = hash;
	M.clear();
	M[hash] = 0;
	//back[hash] = -1;
	for (int ini = 0, fim = 0; ini <= fim; ini++) {
		h = fila[ini];
		//ll hhh = h;
		cl(tmp,0);
		//printf("%d\n", M[h]);
		//print(h);
		int cost = M[h];
		rp(i,k) {
			p[i] = MP((h%72)/8, (h%72)%8);
			if (tmp[p[i].F][p[i].S] == 0) tmp[p[i].F][p[i].S] = 1;
			else if (tmp[p[i].F][p[i].S]) tmp[p[i].F][p[i].S] = -1;
			if (g[p[i].F][p[i].S] == '#') tmp[p[i].F][p[i].S] = -1;
			h/=72;
		}
		int i = (h%72)/8;
		int j = (h%72)%8;
		if (tmp[i][j] != 0) continue;
		if (cost >= 10) continue;
		tmp[i][j] = 2;

		bool end = 1;
		rp(e,k) if (tmp[p[e].F][p[e].S] != -1) end = 0;
		if (end) {
			return cost;
		}
		rp(d,8) {
			int ni = i+di[d];
			int nj = j+dj[d];
			if (valid(ni,nj) && g[ni][nj] != '#' && tmp[ni][nj] == 0) {
				hash = ni*8+nj;
				rp(e,k) {
					if (tmp[p[e].F][p[e].S] != -1) {
						pii np = getCloser(p[e].F,p[e].S,ni,nj);
						hash = (hash*72)+np.F*8+np.S;
					} else {
						hash = (hash*72)+p[e].F*8+p[e].S;
					}
				}
				if (M.count(hash) == 0) {
					M[hash] = cost+1;
					//back[hash] = hhh;
					fila[++fim] = hash;
				}
			}
		}
	}
	return 0;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		ull hash = 0;
		rp(i,9) {
			scanf("%s", g[i]);
			rp(j,8) if (g[i][j] == 'S') hash = i*8+j;
		}
		k = 0;
		rp(i,9) {
			rp(j,8) if (g[i][j] == 'E') hash = (hash*72)+i*8+j, k++;
		}
		if (bfs(hash)) puts("I'm the king of the Seven Seas!");
		else puts("Oh no! I'm a dead man!");

	}
	return 0;
}
