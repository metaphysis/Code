// Crane
// UVa ID: 1611
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.260s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> arr;
vector<pair<int, int>> moves;
vector<int> posMap;

void makeMove(int l, int r) {
    int len = r - l + 1;
    int half = len / 2;
    
    for (int i = 0; i < half; i++) {
        swap(arr[l - 1 + i], arr[l - 1 + half + i]);
    }
    moves.push_back({l, r});
    
    for (int i = l; i <= r; i++) {
        posMap[arr[i - 1]] = i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        arr.resize(n);
        posMap.resize(n + 1);
        
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            posMap[arr[i]] = i + 1;
        }
        moves.clear();
        
        for (int num = n; num >= 1; num--) {
            int pos = posMap[num];
            
            while (pos != num) {
                int dist = num - pos;
                
                if (dist % 2 == 1) {
                    makeMove(pos, pos + 1);
                    pos = pos + 1;
                } else {
                    makeMove(pos, pos + dist - 1);
                    pos = pos + dist / 2;
                }
            }
        }
        
        cout << moves.size() << "\n";
        for (auto& p : moves) {
            cout << p.first << " " << p.second << "\n";
        }
    }
    return 0;
}
