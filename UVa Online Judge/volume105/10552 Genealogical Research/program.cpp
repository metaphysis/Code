// Genealogical Research
// UVa ID: 10552
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Person {
    string name;
    string birthDate;
    string deathDate;
    vector<string> children;
    string mother;
    string father;
    Person() {}
    Person(string n, string b, string m, string f) : name(n), birthDate(b), mother(m), father(f) {}
};

unordered_map<string, Person> people;

string getRidOfSpace(string s) {
    while (!s.empty() && s.front() == ' ') s.erase(s.begin());
    while (!s.empty() && s.back() == ' ') s.pop_back();
    return s;
}

// 解析 BIRTH 命令
void processBirth(const string& line) {
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (getline(ss, token, ':')) tokens.push_back(getRidOfSpace(token));
    if (tokens.size() < 4) return;
    string child = tokens[0].substr(6); // 去掉 "BIRTH "
    string date = tokens[1];
    string mother = tokens[2];
    string father = tokens[3];
    people[child] = Person(child, date, mother, father);
    if (!mother.empty()) {
        if (people.find(mother) == people.end()) {
            people[mother] = Person();
            people[mother].name = mother;
        }
        people[mother].children.push_back(child);
    }
    if (!father.empty()) {
        if (people.find(father) == people.end()) {
            people[father] = Person();
            people[father].name = father;
        }
        people[father].children.push_back(child);
    }
}

// 解析 DEATH 命令
void processDeath(const string& line) {
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (getline(ss, token, ':')) tokens.push_back(getRidOfSpace(token));
    if (tokens.size() < 2) return;
    string person = tokens[0].substr(6); // 去掉 "DEATH "
    string date = tokens[1];
    if (people.find(person) != people.end()) people[person].deathDate = date;
}

// 递归打印祖先（按字母顺序）
void printAncestors(const string& name, int depth) {
    if (people.find(name) == people.end()) return;
    Person p = people[name];
    // 收集父母名字，按字母顺序打印
    vector<string> parents;
    if (!p.father.empty()) parents.push_back(p.father);
    if (!p.mother.empty()) parents.push_back(p.mother);
    sort(parents.begin(), parents.end());
    for (const string& parentName : parents) {
        cout << string(depth * 2, ' ') << parentName;
        // 检查父母是否有出生记录
        if (people.find(parentName) != people.end()) {
            Person parent = people[parentName];
            if (!parent.birthDate.empty()) {
                cout << ' ' << parent.birthDate << " -";
                if (!parent.deathDate.empty()) cout << ' ' << parent.deathDate;
            }
        }
        cout << '\n';
        // 递归打印该父母的祖先
        printAncestors(parentName, depth + 1);
    }
}

// 递归打印后代（按字母顺序）
void printDescendants(const string& name, int depth) {
    if (people.find(name) == people.end()) return;
    Person p = people[name];
    sort(p.children.begin(), p.children.end());
    for (const string& childName : p.children) {
        cout << string(depth * 2, ' ') << childName;
        if (people.find(childName) != people.end()) {
            Person child = people[childName];
            if (!child.birthDate.empty()) {
                cout << ' ' << child.birthDate << " -";
                if (!child.deathDate.empty()) cout << ' ' << child.deathDate;
            }
        }
        cout << '\n';
        printDescendants(childName, depth + 1);
    }
}

int main() {
    string line;
    bool firstOutput = true;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line.find("BIRTH") == 0) processBirth(line);
        else if (line.find("DEATH") == 0) processDeath(line);
        else if (line.find("ANCESTORS") == 0) {
            if (!firstOutput) cout << '\n';
            firstOutput = false;
            string name = getRidOfSpace(line.substr(10));
            cout << "ANCESTORS of " << name << '\n';
            printAncestors(name, 1);
        }
        else if (line.find("DESCENDANTS") == 0) {
            if (!firstOutput) cout << '\n';
            firstOutput = false;
            string name = getRidOfSpace(line.substr(12));
            cout << "DESCENDANTS of " << name << '\n';
            printDescendants(name, 1);
        }
        else if (line == "QUIT") break;
    }
    return 0;
}
