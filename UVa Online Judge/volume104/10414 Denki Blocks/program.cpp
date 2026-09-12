#include <bits/stdc++.h>  
using namespace std;  
  
struct block {  
    int r, c;  
} source[32], target[32];  
  
int main() {  
    int T;  
    cin >> T;  
    for (int cs = 1; cs <= T; cs++) {  
        int n;  
        cin >> n;  
        for (int i = 0; i < n; i++) cin >> source[i].r >> source[i].c;  
        for (int i = 0; i < n; i++) {  
            cin >> target[i].r >> target[i].c;  
            target[i].r -= 20, target[i].c -= 20;  
        }  
        string path;  
        int r = source[0].r, c = source[0].c + 1;  
        if (c) path += string(abs(c), c > 0 ? 'L' : 'R');  
        if (r) path += string(abs(r), r > 0 ? 'U' : 'D');  
        for (int i = 0; i < n; i++) {  
            int sr = source[i].r, sc = source[i].c;  
            int tr = target[i].r, tc = target[i].c;  
            path += string(abs(tc - sc), 'R') + "UR" + string(abs(tr - sr), 'D');  
            if (i + 1 < n) {  
                int nr = source[i + 1].r, nc = source[i + 1].c + 1;  
                path += string(nc - tc, 'L') + string(nr - (tr + 1), 'U');  
            }  
        }  
        cout << path.size() << '\n' << path << '\n';  
    }  
    return 0;  
}
