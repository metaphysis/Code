// Russian Dolls
// UVa ID: 10549
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct Doll {
    int h, d, w;
    int hollow_h, hollow_d;
};

bool compareDolls(const Doll& a, const Doll& b) {
    return a.h > b.h;
}

bool canContain(const Doll& outer, const Doll& inner) {
    return (outer.hollow_h >= inner.h) && (outer.hollow_d >= inner.d);
}

int main() {
    int n;
    bool firstCase = true;
    
    while (cin >> n && n != 0) {
        if (!firstCase) {
            cout << endl;
        }
        firstCase = false;
        
        int total = 2 * n;
        vector<Doll> dolls(total);
        
        for (int i = 0; i < total; i++) {
            cin >> dolls[i].h >> dolls[i].d >> dolls[i].w;
            dolls[i].hollow_h = dolls[i].h - 2 * dolls[i].w;
            dolls[i].hollow_d = dolls[i].d - 2 * dolls[i].w;
        }
        
        sort(dolls.begin(), dolls.end(), compareDolls);
        
        vector<Doll> set1, set2;
        
        function<bool(int)> backtrack = [&](int idx) {
            if (idx == total) {
                return true;
            }
            
            if (set1.size() < n) {
                if (set1.empty() || canContain(set1.back(), dolls[idx])) {
                    set1.push_back(dolls[idx]);
                    if (backtrack(idx + 1)) return true;
                    set1.pop_back();
                }
            }
            
            if (set2.size() < n) {
                if (set2.empty() || canContain(set2.back(), dolls[idx])) {
                    set2.push_back(dolls[idx]);
                    if (backtrack(idx + 1)) return true;
                    set2.pop_back();
                }
            }
            
            return false;
        };
        
        bool success = backtrack(0);
        
        if (!success) {
            set1.clear();
            set2.clear();
            for (int i = 0; i < total; i++) {
                if (i % 2 == 0) {
                    set1.push_back(dolls[i]);
                } else {
                    set2.push_back(dolls[i]);
                }
            }
        }
        
        for (const auto& doll : set1) {
            cout << doll.h << " " << doll.d << " " << doll.w << endl;
        }
        cout << "-" << endl;
        for (const auto& doll : set2) {
            cout << doll.h << " " << doll.d << " " << doll.w << endl;
        }
    }
    
    return 0;
}
