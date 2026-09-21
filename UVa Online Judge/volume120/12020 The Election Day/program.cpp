#include <bits/stdc++.h>
using namespace std;

struct Party {
    string name;
    long long votes;
    int seats;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int partyCount;
        cin >> partyCount;
        string blankName, invalidName;
        long long blankVotes, invalidVotes;
        cin >> blankName >> blankVotes;
        cin >> invalidName >> invalidVotes;
        vector<Party> parties(partyCount);
        for (int i = 0; i < partyCount; i++) {
            cin >> parties[i].name >> parties[i].votes;
            parties[i].seats = 0;
        }
        for (int seat = 0; seat < 100; seat++) {
            int bestIndex = 0;
            for (int i = 1; i < partyCount; i++) {
                long long leftValue = parties[i].votes * (parties[bestIndex].seats + 1);
                long long rightValue = parties[bestIndex].votes * (parties[i].seats + 1);
                if (leftValue > rightValue || (leftValue == rightValue && parties[i].name < parties[bestIndex].name))
                    bestIndex = i;
            }
            parties[bestIndex].seats++;
        }
        for (int i = 0; i < partyCount; i++)
            cout << parties[i].name << " " << parties[i].seats << '\n';
    }
    return 0;
}
