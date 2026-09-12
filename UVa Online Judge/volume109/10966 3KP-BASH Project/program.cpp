#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector<string> VS;

const string errorBadUsage = "bad usage\n";
const string errorNoCommand = "no such command\n";
const string errorDirNotFound = "path not found\n";
const string errorDirFound = "a directory with the same name exists\n";
const string errorDirOrFileFound = "file or directory with the same name exists\n";
const string errorFileNotFound = "file not found\n";
const string errorEmpty = "[empty]\n";

VS split(string s, char delim = ' ') {
    if (delim != ' ')
        for (int i = 0; i < s.length(); i++) if (s[i] == delim) s[i] = ' ';
    stringstream ss(s);
    VS ret;
    string x;
    while (ss >> x) ret.push_back(x);
    return ret;
}

int getInt(string s, LL& v) {
    stringstream ss(s);
    if (ss >> v) return 1;
    return 0;
}

string trim(string s) {
    int l, r;
    for (l = 0; l < s.length(); l++) if (!isspace(s[l])) break;
    for (r = s.length() - 1; r > l; r--) if (!isspace(s[r])) break;
    return s.substr(l, r - l + 1);
}

struct File {
    int parent;
    string name, fullPath;
    LL size;
    bool dir, hidden;
    vector<int> subDir;
    File(int parent = 0, string name = "", LL size = 0, bool dir = true, bool hidden = false) : parent(parent), name(name), size(size), dir(dir), hidden(hidden) {}
};

vector<File> fs;
int curDir;

bool comp(const int& x, const int& y) {
    return fs[x].fullPath < fs[y].fullPath;
}

bool compS(const int& x, const int& y) {
    return fs[x].size < fs[y].size || (fs[x].size == fs[y].size && fs[x].fullPath < fs[y].fullPath);
}

bool compDesc(const int& x, const int& y) {
    return fs[x].size > fs[y].size || (fs[x].size == fs[y].size && fs[x].fullPath < fs[y].fullPath);
}

int findFileInDirectory(int node, string name) {
    VI& subDir = fs[node].subDir;
    for (int i = 0; i < subDir.size(); i++) if (fs[subDir[i]].name == name) return subDir[i];
    return -1;
}

string joinPath(string path, string name) {
    if (path[path.size() - 1] != '/') path += "/";
    return path + name;
}

string getAbsolutePath(int node) {
    if (!node) return "/";
    return joinPath(getAbsolutePath(fs[node].parent), fs[node].name);
}

int createFileInDirectory(int node, string name, LL size, bool dir, bool hidden) {
    fs.push_back(File(node, name, size, dir, hidden));
    int x = fs.size() - 1;
    fs[x].fullPath = joinPath(getAbsolutePath(node), name);
    fs[node].subDir.push_back(x);
    return x;
}

int getDirNode(string path) {
    if (!path.length()) return curDir;
    int node = curDir;
    if (path[0] == '/') node = 0;
    VS dirs = split(path, '/');
    for (int i = 0; i < dirs.size(); i++) {
        if (dirs[i] == ".") continue;
        else if (dirs[i] == "..") {
            if (!node) return -1;
            node = fs[node].parent;
        } else {
            int x = findFileInDirectory(node, dirs[i]);
            if (x == -1 || !fs[x].dir) return -1;
            node = x;
        }
    }
    return node;
}

int isValidFileName(string name) {
    if (name.length() == 0 || name.length() > 255) return 0;
    if (name == "." || name.find("..") != string::npos) return 0;
    for (int i = 0; i < name.length(); i++) if (!isdigit(name[i]) && !isalpha(name[i]) && name[i] != '.') return 0;
    return 1;
}

int splitFileName(string fullPath, string& fileName) {
    int n = fullPath.length(), x = n;
    for (int i = fullPath.length() - 1; i >= 0; i--) {
        if (fullPath[i] == '/') {
            fileName = fullPath.substr(i + 1);
            string dir = fullPath.substr(0, i);
            if (dir == "") return 0;
            return getDirNode(dir);
        }
    }
    fileName = fullPath;
    return curDir;
}

void newSession() {
    fs.clear();
    fs.push_back(File());
    curDir = 0;
}

void findFileEx(VI& out, int node, string fileName, bool recur, bool hidden, bool findFile = true, bool findDir = true) {
    VI& subDir = fs[node].subDir;
    for (int i = 0; i < subDir.size(); i++) {
        int x = subDir[i];
        if (fs[x].dir && recur) findFileEx(out, x, fileName, recur, hidden, findFile, findDir);
        if (fs[x].hidden && !hidden) continue;
        if (fileName == "" || fs[x].name == fileName) {
            if ((fs[x].dir && findDir) || (!fs[x].dir && findFile)) out.push_back(x);
        }
    }
}

string formatFiles(const VI& out) {
    stringstream ss;
    for (int i = 0; i < out.size(); i++) {
        ss << fs[out[i]].fullPath << " " << fs[out[i]].size;
        if (fs[out[i]].hidden) ss << " hidden";
        if (fs[out[i]].dir) ss << " dir";
        ss << "\n";
    }
    return ss.str();
}

bool parseArgs(VS params, VS& args, bool* sw, LL& v) {
    LL v2;
    for (int i = 0; i < params.size(); i++) if (params[i][0] == '-') {
        if (params[i].length() > 1 && isalpha(params[i][1])) sw[params[i][1]] = 1;
        else if (params[i].length() > 1 && getInt(params[i].substr(1), v2)) v = v2;
        else return false;
    } else args.push_back(params[i]);
    return true;
}

string runCommand(const VS& cmd) {
    VS params(cmd.begin() + 1, cmd.end()), args;
    bool sw[256];
    LL v = 0;
    memset(sw, 0, sizeof(sw));
    if (!parseArgs(params, args, sw, v)) return errorBadUsage;
    int node;
    string fileName;
    if (cmd[0] == "cd") {
        if (args.size() != 1) return errorBadUsage;
        if ((node = getDirNode(args[0])) == -1) return errorDirNotFound;
        curDir = node;
        return "";
    } else if (cmd[0] == "touch") {
        if (args.size() != 1) return errorBadUsage;
        if ((node = splitFileName(args[0], fileName)) == -1) return errorDirNotFound;
        if (!isValidFileName(fileName)) return errorBadUsage;
        int x = findFileInDirectory(node, fileName);
        if (x != -1 && fs[x].dir) return errorDirFound;
        if (x == -1) createFileInDirectory(node, fileName, v, false, sw['h']);
        else {
            fs[x].size = v;
            fs[x].hidden = sw['h'];
        }
        return "";
    }
    if (cmd[0] == "mkdir") {
        if (args.size() != 1) return errorBadUsage;
        if ((node = splitFileName(args[0], fileName)) == -1) return errorDirNotFound;
        if (!isValidFileName(fileName)) return errorBadUsage;
        int x = findFileInDirectory(node, fileName);
        if (x != -1) return errorDirOrFileFound;
        createFileInDirectory(node, fileName, 0, true, sw['h']);
        return "";
    }
    if (cmd[0] == "find") {
        if (args.size() != 1) return errorBadUsage;
        if ((node = splitFileName(args[0], fileName)) == -1) return errorDirNotFound;
        VI out;
        findFileEx(out, node, fileName, sw['r'], sw['h']);
        if (out.size() == 0) return errorFileNotFound;
        sort(out.begin(), out.end(), comp);
        return formatFiles(out);
    }
    if (cmd[0] == "ls") {
        if (args.size() > 1) return errorBadUsage;
        node = curDir;
        if (args.size() == 1) if ((node = getDirNode(args[0])) == -1) return errorDirNotFound;
        VI out;
        findFileEx(out, node, "", sw['r'], sw['h'], !sw['d'], !sw['f']);
        if (out.size() == 0) return errorEmpty;
        if (sw['s']) sort(out.begin(), out.end(), compS);
        else if (sw['S']) sort(out.begin(), out.end(), compDesc);
        else sort(out.begin(), out.end(), comp);
        return formatFiles(out);
    }
    if (cmd[0] == "pwd") {
        if (args.size() != 0) return errorBadUsage;
        return getAbsolutePath(curDir) + "\n";
    }
    if (cmd[0] == "exit") {
        if (args.size() != 0) return errorBadUsage;
        newSession();
        return "";
    }
    if (cmd[0] == "grep") return errorBadUsage;
    return errorNoCommand;
}

string runCommandLine(string cmd) {
    int n = cmd.length(), start = 0, inQuote = 0;
    VS commands;
    for (int i = 0; i <= n; i++) if (i == n || (cmd[i] == '|' && !inQuote)) {
        commands.push_back(cmd.substr(start, i - start));
        start = i + 1;
    } else if (cmd[i] == '"') inQuote = !inQuote;
    if (!commands.size()) return "";
    string lastOutput = runCommand(split(commands[0]));
    string line, s, ret;
    for (int i = 1; i < commands.size(); i++) {
        stringstream ss(commands[i]);
        if (!(ss >> s) || s != "grep") return errorBadUsage;
        getline(ss, s);
        s = trim(s);
        if (s.length() < 2 || s[0] != '"' || s[s.length() - 1] != '"') return errorBadUsage;
        s = s.substr(1, s.length() - 2);
        stringstream input(lastOutput);
        ret = "";
        while (getline(input, line)) if (line.find(s) != string::npos) ret += line + "\n";
        lastOutput = ret;
    }
    return lastOutput;
}

int main() {
    string cmd;
    newSession();
    while (getline(cin, cmd)) cout << runCommandLine(cmd);
    return 0;
}
