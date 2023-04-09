#include <bits/stdc++.h>
using namespace std;
struct point { int x, y; };
struct segment { point a, b; } st[1010];

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int cases = 10;
    for (int cs = 1; cs <= cases; cs++) {
        int n = rand() % 1000 + 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            START:
            int X1 = rand() % 1001, Y1 = rand() % 1001;
            int X2 = rand() % 1001, Y2 = rand() % 1001;
            while (X1 == X2 && Y1 == Y2)
                X2 = rand() % 1001, Y2 = rand() % 1001;
            if (X1 > X2) swap(X1, X2), swap(Y1, Y2);
            int flag = 0;
            for (int j = 0; j < i; j++)
                if (st[j].a.x == X1 && st[j].a.y == Y1 && st[j].b.x == X2 && st[j].b.y == Y2)
                {
                    flag = 1;
                    break;
                }
            if (flag) goto START;
            st[i].a = point{X1, Y1};
            st[i].b = point{X2, Y2};
            cout << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << '\n';
        }
    }
    cout << 0 << '\n';
}
