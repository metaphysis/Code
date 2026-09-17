#include <bits/stdc++.h>
using namespace std;

struct Fact {
    string subject, verb, object;
    bool positive;
};

bool isGeneric(const string &subject) {
    return subject == "everybody" || subject == "nobody";
}

bool isFirstPerson(const string &subject) {
    return subject == "I" || subject == "you";
}

string changeSubject(const string &subject) {
    if (subject == "I") return "you";
    if (subject == "you") return "I";
    return subject;
}

string readObject(istringstream &input) {
    string object;
    getline(input, object);
    if (!object.empty()) object.erase(0, 1);
    return object;
}

Fact parseFact(const string &line) {
    istringstream input(line.substr(0, line.size() - 1));
    Fact fact;
    string word;
    input >> fact.subject >> word;
    fact.positive = true;
    if (word == "don't" || word == "doesn't") {
        fact.positive = false;
        input >> fact.verb;
    } else {
        fact.verb = word;
        if (!isFirstPerson(fact.subject)) fact.verb.pop_back();
    }
    if (fact.subject == "nobody") fact.positive = false;
    fact.object = readObject(input);
    return fact;
}

bool sameActivity(const Fact &first, const Fact &second) {
    return first.verb == second.verb && first.object == second.object;
}

bool contradicts(const Fact &first, const Fact &second) {
    if (!sameActivity(first, second) || first.positive == second.positive) return false;
    return first.subject == second.subject || isGeneric(first.subject) || isGeneric(second.subject);
}

string makeActivity(const string &subject, const string &verb, const string &object, bool positive, bool plural = false) {
    string result;
    if (positive) {
        result = verb;
        if (!plural && !isFirstPerson(subject)) result += "s";
    } else {
        result = isFirstPerson(subject) || plural ? "don't " : "doesn't ";
        result += verb;
    }
    if (!object.empty()) result += " " + object;
    return result;
}

string joinParts(const vector<string> &parts, const string &lastSeparator) {
    string result;
    for (int i = 0; i < static_cast<int>(parts.size()); ++i) {
        if (i > 0) result += i + 1 == static_cast<int>(parts.size()) ? lastSeparator : ", ";
        result += parts[i];
    }
    return result;
}

string answerYesNo(istringstream &input, const vector<Fact> &facts) {
    string subject, verb, object;
    input >> subject >> verb;
    object = readObject(input);
    for (const Fact &fact : facts) {
        if (fact.verb != verb || fact.object != object) continue;
        if (fact.subject != subject && !isGeneric(fact.subject)) continue;
        string replySubject = changeSubject(subject);
        string prefix = fact.positive ? "yes, " : "no, ";
        return prefix + replySubject + " " + makeActivity(replySubject, verb, object, fact.positive) + ".";
    }
    return "maybe.";
}

string answerWho(istringstream &input, const vector<Fact> &facts) {
    string verb, object;
    input >> verb;
    verb.pop_back();
    object = readObject(input);
    vector<string> subjects;
    set<string> seen;
    for (const Fact &fact : facts) {
        if (fact.verb != verb || fact.object != object) continue;
        if (fact.subject == "everybody") return "everybody " + makeActivity("everybody", verb, object, true) + ".";
        if (fact.subject == "nobody") return "nobody " + makeActivity("nobody", verb, object, true) + ".";
        if (!fact.positive || !seen.insert(fact.subject).second) continue;
        subjects.push_back(changeSubject(fact.subject));
    }
    if (subjects.empty()) return "I don't know.";
    bool plural = subjects.size() > 1;
    return joinParts(subjects, " and ") + " " + makeActivity(subjects[0], verb, object, true, plural) + ".";
}

string answerWhat(istringstream &input, const vector<Fact> &facts) {
    string auxiliary, subject;
    input >> auxiliary >> subject;
    string replySubject = changeSubject(subject);
    vector<string> activities;
    set<pair<string, string>> seen;
    for (const Fact &fact : facts) {
        if (fact.subject != subject && !isGeneric(fact.subject)) continue;
        if (!seen.insert(make_pair(fact.verb, fact.object)).second) continue;
        activities.push_back(makeActivity(replySubject, fact.verb, fact.object, fact.positive));
    }
    if (activities.empty()) return "I don't know.";
    return replySubject + " " + joinParts(activities, ", and ") + ".";
}

string answerQuestion(const string &line, const vector<Fact> &facts, bool conflict) {
    if (conflict) return "I am abroad.";
    istringstream input(line.substr(0, line.size() - 1));
    string firstWord;
    input >> firstWord;
    if (firstWord == "who") return answerWho(input, facts);
    if (firstWord == "what") return answerWhat(input, facts);
    return answerYesNo(input, facts);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dialogueCount;
    cin >> dialogueCount;
    string line;
    getline(cin, line);
    for (int dialogueId = 1; dialogueId <= dialogueCount; ++dialogueId) {
        vector<Fact> facts;
        bool conflict = false;
        cout << "Dialogue #" << dialogueId << ":\n";
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            if (line.back() == '!') {
                cout << line << "\n\n";
                break;
            } else if (line.back() == '?') {
                cout << line << '\n' << answerQuestion(line, facts, conflict) << "\n\n";
            } else {
                Fact fact = parseFact(line);
                for (const Fact &previous : facts) if (contradicts(previous, fact)) conflict = true;
                facts.push_back(fact);
            }
        }
    }
    return 0;
}
