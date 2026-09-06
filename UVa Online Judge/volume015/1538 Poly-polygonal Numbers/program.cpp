#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long value, index;
    int type;
};

struct NodeCompare {
    bool operator()(const Node &a, const Node &b) const {
        return a.value > b.value;
    }
};

long long polygonal(long long k, long long index) {
    long long first = index, second = (k - 2) * index - (k - 4);
    if (first % 2 == 0) first /= 2;
    else second /= 2;
    return first * second;
}

long long findStart(long long k, long long start) {
    long long left = 1, right = 1;
    while (polygonal(k, right) < start) right *= 2;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (polygonal(k, mid) >= start) right = mid;
        else left = mid + 1;
    }
    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool firstCase = true;
    while (cin >> n && n != 0) {
        vector<long long> kinds(n);
        for (int i = 0; i < n; ++i) cin >> kinds[i];
        long long start;
        cin >> start;
        if (!firstCase) cout << '\n';
        firstCase = false;
        priority_queue<Node, vector<Node>, NodeCompare> heap;
        for (int i = 0; i < n; ++i) {
            long long index = findStart(kinds[i], start);
            heap.push({polygonal(kinds[i], index), index, i});
        }
        int answerCount = 0;
        while (answerCount < 5) {
            long long value = heap.top().value;
            vector<int> matchTypes;
            while (!heap.empty() && heap.top().value == value) {
                Node current = heap.top();
                heap.pop();
                matchTypes.push_back(current.type);
                ++current.index;
                current.value = polygonal(kinds[current.type], current.index);
                heap.push(current);
            }
            if (matchTypes.size() >= 2) {
                sort(matchTypes.begin(), matchTypes.end());
                cout << value << ":";
                for (int i = 0; i < matchTypes.size(); ++i) {
                    if (i != 0) cout << " ";
                    cout << kinds[matchTypes[i]];
                }
                cout << '\n';
                ++answerCount;
            }
        }
    }
    return 0;
}
