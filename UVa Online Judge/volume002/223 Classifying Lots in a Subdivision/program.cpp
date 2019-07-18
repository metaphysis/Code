#include <bits/stdc++.h>

using namespace std;

#define FOREACH(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct Point
{
	int x, y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
	bool operator<(const Point &p) const
	{
		return x != p.x ? (x < p.x) : (y < p.y);
	}
};

Point operator-(const Point &a, const Point &b)
{
	return Point(a.x - b.x, a.y - b.y);
}

Point V[500];
int N;
map<Point, int> Vmap;
map<int, int> answer;

int read()
{
	scanf("%d %d", &V[N].x, &V[N].y);
	if (Vmap.count(V[N]) == 0)
	{
		Vmap[V[N]] = N;
		return N++;
	}
	return Vmap[V[N]];
}

struct Segment
{
	int a, b, index, face;
	Segment *rev;

	void print()
	{
		printf("(%d,%d)-(%d,%d)\n", V[a].x, V[a].y, V[b].x, V[b].y);
	}
} seg[500];
int M;
vector<Segment *> adj[500];

struct Cmp
{
	bool operator()(Segment *S1, Segment *S2) const
	{
		Point a = V[S1->b] - V[S1->a];
		Point b = V[S2->b] - V[S1->a];
		return atan2(a.y, a.x) < atan2(b.y, b.x);
	}
};

int main()
{
	for (int cs = 1; scanf("%d", &M) == 1 && M > 0; cs++)
	{
		N = 0;
		Vmap.clear();
		for (int i = 0; i < 2 * M; i += 2)
		{
			seg[i].a = read();
			seg[i].b = read();
			seg[i + 1] = seg[i];
			swap(seg[i + 1].a, seg[i + 1].b);
			seg[i].rev = &seg[i + 1];
			seg[i + 1].rev = &seg[i];
		}
		for (int i = 0; i < N; i++)
		{
			adj[i].clear();
		}
		for (int i = 0; i < 2 * M; i++)
		{
			adj[seg[i].a].push_back(&seg[i]);
		}
		for (int a = 0; a < N; a++)
		{
			sort(adj[a].begin(), adj[a].end(), Cmp());
			for (int i = 0; i < (int)adj[a].size(); i++)
			{
				Segment *s = adj[a][i];
				s->index = i;
			}
		}
		answer.clear();
		for (int i = 0; i < 2 * M; i++)
		{
			seg[i].face = -1;
		}
		int numfaces = 0;
		for (int s1 = 0; s1 < 2 * M; s1++)
		{
			if (seg[s1].face != -1)
			{
				continue;
			}
			numfaces++;
			seg[s1].face = numfaces;
			vector<Segment *> face;
			face.push_back(&seg[s1]);
			while (true)
			{
				Segment *s = face.back();
				int m = adj[s->b].size();
				Segment *t = adj[s->b][(s->rev->index + m - 1) % m];
				if (t == face[0])
				{
					break;
				}
				assert(t->face == -1);
				t->face = numfaces;
				face.push_back(t);
			}
			long long area = 0;
			FOREACH(it, face)
			{
				Segment *s = *it;
				area += V[s->a].x * V[s->b].y - V[s->a].y * V[s->b].x;
			}
			if (area >= 0)
			{
				++answer[face.size()];
			}
		}
		if (cs != 1)
		{
			printf("\n");
		}
		printf("Case %d\n", cs);
		int total = 0;
		FOREACH(it, answer)
		{
			printf("Number of lots with perimeter consisting of %d surveyor's lines = %d\n",
						 it->first, it->second);
			total += it->second;
		}
		printf("Total number of lots = %d\n", total);
	}
}
