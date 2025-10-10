// Trial of the Millennium
// UVa ID: 431
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> evidenceList;
int memo[200][300];
bool selected[200][300];

int knapsack(int index, int remainingTime) {
    if (index == evidenceList.size() || remainingTime == 0) return 0;
    if (~memo[index][remainingTime]) return memo[index][remainingTime];
    int takeScore = 0, skipScore = 0;
    if (evidenceList[index].second <= remainingTime) 
        takeScore = knapsack(index + 1, remainingTime - evidenceList[index].second) + evidenceList[index].first;
    skipScore = knapsack(index + 1, remainingTime);
    selected[index][remainingTime] = takeScore > skipScore;
    return memo[index][remainingTime] = max(takeScore, skipScore);
}

struct Evidence {
    string description;
    int timeRequired, scoreValue;
    bool friend operator<(const Evidence &a, const Evidence &b) {
        return a.timeRequired < b.timeRequired;
    }
} tempEvidence;

int main() {
    ios::sync_with_stdio(false);
    int testCases, totalTime, scoreValue, timeRequired;
    string inputLine, description;
    stringstream stringParser;
    vector<string> descriptions;
    cin >> testCases;
    getline(cin, inputLine);
    getline(cin, inputLine);
    while (testCases--) {
        descriptions.clear();
        evidenceList.clear();
        memset(memo, -1, sizeof memo);
        memset(selected, 0, sizeof selected);
        cin >> totalTime;
        getline(cin, inputLine);
        while (getline(cin, inputLine) && inputLine != "") {
            stringParser.clear(), stringParser.str(inputLine);
            stringParser >> scoreValue >> timeRequired;
            getline(stringParser, description);
            description.erase(description.begin());
            evidenceList.push_back(make_pair(scoreValue, timeRequired));
            descriptions.push_back(description);
        }
        int totalScore = knapsack(0, totalTime), totalTimeUsed = 0;
        int currentIndex = 0;
        if (totalScore == 0) {
            cout << "There is not enough time to present any evidence. Drop the charges.\n";
            if (testCases) cout << '\n';
            continue;
        }
        vector<Evidence> selectedEvidence;
        while (currentIndex < evidenceList.size()) {
            if (selected[currentIndex][totalTime]) {
                tempEvidence.description = descriptions[currentIndex];
                tempEvidence.scoreValue = evidenceList[currentIndex].first;
                tempEvidence.timeRequired = evidenceList[currentIndex].second;
                totalTimeUsed += tempEvidence.timeRequired;
                totalTime -= tempEvidence.timeRequired;
                selectedEvidence.push_back(tempEvidence);
            }
            currentIndex++;
        }
        sort(selectedEvidence.begin(), selectedEvidence.end());
        cout << "Score  Time  Description\n";
        cout << "-----  ----  -----------\n";
        for (int i = 0; i < selectedEvidence.size(); i++) {
            cout << setw(3) << selectedEvidence[i].scoreValue << "    " << setw(3) << selectedEvidence[i].timeRequired << "   " << selectedEvidence[i].description << '\n';
        }
        cout << '\n';
        cout << "Total score: " << totalScore << " points\n";
        cout << " Total time: " << totalTimeUsed << " hours\n";
        if (testCases) cout << '\n';
    }
    return 0;
}
