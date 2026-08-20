#include <bits/stdc++.h>
using namespace std;

string findSmallestMultiple(int n, const vector<int>& digits) {
    if (n == 0) return "0";
    vector<int> sortedDigits = digits;
    sort(sortedDigits.begin(), sortedDigits.end());
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> parentDigit(n, -1);
    queue<int> remainderQueue;
    int targetRemainder = -1;
    for (int digit : sortedDigits) {
        if (digit == 0) continue;
        int remainder = digit % n;
        if (visited[remainder]) continue;
        visited[remainder] = true;
        parent[remainder] = -2;
        parentDigit[remainder] = digit;
        remainderQueue.push(remainder);
        if (remainder == 0) {
            targetRemainder = 0;
            break;
        }
    }
    while (!remainderQueue.empty() && targetRemainder == -1) {
        int currentRemainder = remainderQueue.front();
        remainderQueue.pop();
        for (int digit : sortedDigits) {
            int nextRemainder = (currentRemainder * 10 + digit) % n;
            if (visited[nextRemainder]) continue;
            visited[nextRemainder] = true;
            parent[nextRemainder] = currentRemainder;
            parentDigit[nextRemainder] = digit;
            remainderQueue.push(nextRemainder);
            if (nextRemainder == 0) {
                targetRemainder = 0;
                break;
            }
        }
    }
    if (targetRemainder == -1) return "0";
    string answer;
    int currentRemainder = targetRemainder;
    while (parent[currentRemainder] != -2) {
        answer.push_back(char('0' + parentDigit[currentRemainder]));
        currentRemainder = parent[currentRemainder];
    }
    answer.push_back(char('0' + parentDigit[currentRemainder]));
    reverse(answer.begin(), answer.end());
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        int m;
        cin >> m;
        vector<int> digits(m);
        for (int i = 0; i < m; i++) cin >> digits[i];
        cout << findSmallestMultiple(n, digits) << '\n';
    }
    return 0;
}
