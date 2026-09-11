#include <bits/stdc++.h>
using namespace std;

const int maxEntry = 200005;
const int maxStudent = 200005;
const int maxCode = 1001;

struct Entry {
    int code, score;
};

struct Candidate {
    int studentId, score;
    long long uniqueId;
};

struct HeapCmp {
    bool operator()(const Candidate &a, const Candidate &b) const {
        if (a.score != b.score) return a.score > b.score;
        return a.uniqueId > b.uniqueId;
    }
};

int programmeCount, studentCount, entryCount;
int programmeCode[maxCode], programmeCapacity[maxCode], capacityByCode[maxCode];
string programmeName[maxCode];
Entry entries[maxEntry];
int entryStart[maxStudent], entryLength[maxStudent], entryNext[maxStudent];
string studentName[maxStudent];
long long studentUniqueId[maxStudent];
priority_queue<Candidate, vector<Candidate>, HeapCmp> programmeHeap[maxCode];
queue<int> waitQueue;
Candidate result[maxStudent];

bool betterCandidate(const Candidate &a, const Candidate &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.uniqueId > b.uniqueId;
}

int parseScore(const string &text) {
    int point = text.find('.');
    if (point == (int)string::npos) return stoi(text) * 100;
    int result = stoi(text.substr(0, point)) * 100;
    string fraction = text.substr(point + 1);
    if (fraction.size() == 1) result += (fraction[0] - '0') * 10;
    else result += (fraction[0] - '0') * 10 + fraction[1] - '0';
    return result;
}

void processStudent(int studentId) {
    while (entryNext[studentId] < entryLength[studentId]) {
        Entry &entry = entries[entryStart[studentId] + entryNext[studentId]];
        entryNext[studentId]++;
        int code = entry.code;
        Candidate current;
        current.studentId = studentId;
        current.score = entry.score;
        current.uniqueId = studentUniqueId[studentId];
        if (capacityByCode[code] == 0) continue;
        if ((int)programmeHeap[code].size() < capacityByCode[code]) {
            programmeHeap[code].push(current);
            break;
        }
        Candidate worst = programmeHeap[code].top();
        if (betterCandidate(current, worst)) {
            programmeHeap[code].pop();
            programmeHeap[code].push(current);
            waitQueue.push(worst.studentId);
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> programmeCount >> studentCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < programmeCount; i++) {
        getline(cin, programmeName[i]);
        cin >> programmeCode[i] >> programmeCapacity[i];
        capacityByCode[programmeCode[i]] = programmeCapacity[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (int i = 0; i < studentCount; i++) {
        int length;
        getline(cin, studentName[i]);
        cin >> length >> studentUniqueId[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        entryStart[i] = entryCount;
        entryLength[i] = length;
        entryNext[i] = 0;
        for (int j = 0; j < length; j++) {
            string scoreText;
            cin >> entries[entryCount].code >> scoreText;
            entries[entryCount].score = parseScore(scoreText);
            entryCount++;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (int i = 0; i < studentCount; i++) waitQueue.push(i);
    while (!waitQueue.empty()) {
        int studentId = waitQueue.front();
        waitQueue.pop();
        processStudent(studentId);
    }
    for (int i = 0; i < programmeCount; i++) {
        int code = programmeCode[i], resultCount = 0;
        while (!programmeHeap[code].empty()) {
            result[resultCount] = programmeHeap[code].top();
            programmeHeap[code].pop();
            resultCount++;
        }
        sort(result, result + resultCount, betterCandidate);
        cout << programmeName[i] << '\n';
        cout << resultCount << '\n';
        for (int j = 0; j < resultCount; j++)
            cout << j + 1 << ". " << studentName[result[j].studentId] << '\n';
    }
    return 0;
}
