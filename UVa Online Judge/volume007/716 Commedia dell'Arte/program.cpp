// Commedia dell'Arte
// UVa ID: 716
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 使用归并排序计算逆序数（排除0）
long long mergeCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    long long count = 0;
    
    count += mergeCount(arr, temp, left, mid);
    count += mergeCount(arr, temp, mid + 1, right);
    
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            count += mid - i + 1;
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
    
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int m;
        cin >> m;
        
        // 读取数据并构建排除0的序列
        vector<int> sequence;
        int blankX, blankY, blankZ;
        bool foundZero = false;
        
        for (int z = 0; z < m; z++) {
            for (int y = 0; y < m; y++) {
                for (int x = 0; x < m; x++) {
                    int num;
                    cin >> num;
                    if (num == 0) {
                        blankX = x;
                        blankY = y; 
                        blankZ = z;
                        foundZero = true;
                    } else {
                        sequence.push_back(num);
                    }
                }
            }
        }
        
        // 计算逆序数
        long long inversions = 0;
        if (!sequence.empty()) {
            vector<int> temp(sequence.size());
            inversions = mergeCount(sequence, temp, 0, sequence.size() - 1);
        }
        
        bool solvable;
        
        if (m % 2 == 1) {
            // M为奇数：逆序数必须为偶数
            solvable = (inversions % 2 == 0);
        } else {
            // M为偶数：y步数+z步数与逆序数奇偶性不同时不可解
            int ySteps = (m - 1 - blankY);
            int zSteps = (m - 1 - blankZ);
            int stepsParity = (ySteps + zSteps) % 2;
            int inversionParity = inversions % 2;
            // 如果异或结果为1（奇偶性不同），则不可解
            solvable = !((stepsParity ^ inversionParity) & 1);
        }
        
        if (solvable) cout << "Puzzle can be solved." << endl;
        else cout << "Puzzle is unsolvable." << endl;
    }
    
    return 0;
}
