// SOAP Response
// UVa ID: 11928
// Verdict: Accepted
// Submission Date: 2026-07-29
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

void parseOpeningTag(const string &line, string &tagName, map<string, string> &properties) {
    string content = line.substr(1, line.size() - 2);
    stringstream stringStream(content);
    stringStream >> tagName;
    string propertyToken;
    while (stringStream >> propertyToken) {
        size_t equalPosition = propertyToken.find('=');
        string propertyName = propertyToken.substr(0, equalPosition);
        string propertyValue = propertyToken.substr(equalPosition + 2, propertyToken.size() - equalPosition - 3);
        properties[propertyName] = propertyValue;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCaseCount;
    cin >> testCaseCount;
    for (int testCaseIndex = 1; testCaseIndex <= testCaseCount; ++testCaseIndex) {
        int tagCount;
        cin >> tagCount;
        map<string, map<string, string>> tagProperties;
        vector<string> tagStack;
        string line;
        getline(cin, line);
        for (int tagIndex = 0; tagIndex < tagCount; ++tagIndex) {
            getline(cin, line);
            if (line[1] == '/') {
                tagStack.pop_back();
                continue;
            }
            string tagName;
            map<string, string> properties;
            parseOpeningTag(line, tagName, properties);
            string currentPath = tagStack.empty() ? tagName : tagStack.back() + "." + tagName;
            tagProperties[currentPath] = properties;
            tagStack.push_back(currentPath);
        }
        int queryCount;
        cin >> queryCount;
        cout << "Case " << testCaseIndex << ":\n";
        for (int queryIndex = 0; queryIndex < queryCount; ++queryIndex) {
            string query;
            cin >> query;
            size_t propertyStart = query.find("[\"");
            size_t propertyEnd = query.find("\"]");
            string tagPath = query.substr(0, propertyStart);
            string propertyName = query.substr(propertyStart + 2, propertyEnd - propertyStart - 2);
            auto tagIterator = tagProperties.find(tagPath);
            if (tagIterator == tagProperties.end()) {
                cout << "Undefined\n";
                continue;
            }
            auto propertyIterator = tagIterator->second.find(propertyName);
            if (propertyIterator == tagIterator->second.end()) cout << "Undefined\n";
            else cout << propertyIterator->second << '\n';
        }
    }
    return 0;
}
