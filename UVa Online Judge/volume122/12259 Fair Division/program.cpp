// Fair Division
// UVa ID: 12259
// Verdict: Accepted
// Submission Date: 2026-01-26
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct Person {
    int id;        // 原始顺序
    int maxPay;    // 最大支付能力
    int curPay;    // 当前支付
    
    Person(int i, int m) : id(i), maxPay(m), curPay(0) {}
};

// 检查是否存在方案使得最大差距不超过maxDiff
bool canAchieveDiff(int maxDiff, int p, int n, const vector<Person>& people, 
                   long long& minSum, long long& maxSum) {
    minSum = 0, maxSum = 0;
    double avg = (double)p / n;
    
    for (const auto& person : people) {
        // 理论支付区间 [avg - maxDiff, avg + maxDiff]
        int lower = (int)ceil(avg - maxDiff);
        int upper = (int)floor(avg + maxDiff);
        
        // 与能力限制取交集
        lower = max(lower, 0);
        upper = min(upper, person.maxPay);
        
        if (lower > upper) return false;
        
        minSum += lower;
        maxSum += upper;
    }
    
    return minSum <= p && p <= maxSum;
}

void solve() {
    int p, n;
    cin >> p >> n;
    
    vector<Person> people;
    long long totalMax = 0;
    for (int i = 0; i < n; i++) {
        int maxPay;
        cin >> maxPay;
        people.emplace_back(i, maxPay);
        totalMax += maxPay;
    }
    
    if (totalMax < p) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    
    // 按规则要求的顺序排序：支付能力降序，id升序
    // 这样在分配时会优先分配能力高的人
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        if (a.maxPay != b.maxPay) return a.maxPay > b.maxPay;
        return a.id < b.id;
    });
    
    // 二分搜索最小的最大差距
    int left = 0, right = p;
    int bestDiff = p;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        long long minSum, maxSum;
        
        if (canAchieveDiff(mid, p, n, people, minSum, maxSum)) {
            bestDiff = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    // 现在 bestDiff 是最小的最大差距
    // 我们需要构造字典序最小的方案
    
    // 先分配下限
    double avg = (double)p / n;
    vector<int> lower(n), upper(n);
    long long sumL = 0;
    
    for (int i = 0; i < n; i++) {
        lower[i] = max((int)ceil(avg - bestDiff), 0);
        lower[i] = min(lower[i], people[i].maxPay);
        
        upper[i] = min((int)floor(avg + bestDiff), people[i].maxPay);
        upper[i] = max(upper[i], 0);
        
        people[i].curPay = lower[i];
        sumL += lower[i];
    }
    
    // 还需要分配的金额
    int remain = p - sumL;
    
    // 按规则分配剩余金额：在允许范围内，让支付尽量均匀
    // 优先给能增加且增加后仍不超过上限的人
    while (remain > 0) {
        bool assigned = false;
        
        // 尝试让每个人的支付增加，但保持最大差距不变
        for (int i = 0; i < n && remain > 0; i++) {
            if (people[i].curPay < upper[i] && people[i].curPay < people[i].maxPay) {
                // 计算如果增加1，新的差距是否超过bestDiff
                int newPay = people[i].curPay + 1;
                double newDiff = abs(newPay - avg);
                
                if (newDiff <= bestDiff + 1e-9) {  // 考虑浮点误差
                    people[i].curPay++;
                    remain--;
                    assigned = true;
                }
            }
        }
        
        // 如果一轮分配后还有剩余，放宽条件
        if (!assigned && remain > 0) {
            // 给支付最少且有能力的人增加
            sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
                if (a.curPay != b.curPay) return a.curPay < b.curPay;
                if (a.maxPay != b.maxPay) return a.maxPay > b.maxPay;
                return a.id < b.id;
            });
            
            for (auto& person : people) {
                if (person.curPay < person.maxPay && remain > 0) {
                    person.curPay++;
                    remain--;
                    break;
                }
            }
        }
    }
    
    // 按原始id排序输出
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.id < b.id;
    });
    
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << people[i].curPay;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
