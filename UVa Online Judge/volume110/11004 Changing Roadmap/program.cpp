// Changing Roadmap
// UVa ID: 11004
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

struct Road {
    int a, b, c;
    Road(int a, int b, int c) : a(a), b(b), c(c) {}
};

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int roadmapCount = 0;
    int N;
    while (cin >> N && N != 0) {
        roadmapCount++;
        vector<Road> roads;
        for (int i = 0; i < N; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            roads.emplace_back(a, b, c);
        }

        int PP;
        cin >> PP;
        vector<Point> importantPlaces;
        for (int i = 0; i < PP; i++) {
            int x, y;
            cin >> x >> y;
            importantPlaces.emplace_back(x, y);
        }

        // 使用bitset进一步优化
        vector<bitset<100>> signBits(N);
        for (int i = 0; i < N; i++) {
            for (int p = 0; p < PP; p++) {
                long long value = (long long)roads[i].a * importantPlaces[p].x + 
                                 (long long)roads[i].b * importantPlaces[p].y + 
                                 roads[i].c;
                signBits[i][p] = (value > 0);
            }
        }

        long long negativeCount = 0;

        // 对于每对道路，使用位运算批量计算
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                // 同号的情况：两个bitset相同的位置
                bitset<100> sameSign = (signBits[i] & signBits[j]) | (~signBits[i] & ~signBits[j]);
                negativeCount += sameSign.count();
            }
        }

        cout << "Roadmap " << roadmapCount << ":\n";
        cout << "Negative Builders Ltd. will build " << negativeCount << " New Roads.\n";
    }

    return 0;
}
