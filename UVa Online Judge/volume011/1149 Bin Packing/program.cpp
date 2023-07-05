// Bin Packing
// UVa ID: 1149
// Verdict: Accepted
// Submission Date: 2023-07-05
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int li[100010], n, L, T;
    cin >> T;
	while (T--) {
        cin >> n >> L;
        for (int i = 0; i < n; i++) cin >> li[i];
        sort(li, li + n);
        int r = 0, head = 0, rear = n - 1;
        while (head < rear) {
            if (li[head] + li[rear] <= L) head++, rear--, r++;
            else rear--, r++;
        }
        if (head == rear) r++;
        cout << r << '\n';
        if (T) cout << '\n';
    }
    return 0;
}
