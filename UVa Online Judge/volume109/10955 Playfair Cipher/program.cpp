#include <bits/stdc++.h>
using namespace std;

struct Rule {
	int a, b, c, d;
};

vector<Rule> rules;
int posArr[25], usedArr[25], cellChar[25];

int getId(char ch) {
	if (ch == 'J') ch = 'I';
	if (ch > 'J') return ch - 'A' - 1;
	return ch - 'A';
}

char getChar(int id) {
	if (id >= 9) return static_cast<char>('A' + id + 1);
	return static_cast<char>('A' + id);
}

string normalizeText(const string &text) {
	string result;
	for (char ch : text) {
		if (!isalpha(static_cast<unsigned char>(ch))) continue;
		ch = toupper(static_cast<unsigned char>(ch));
		if (ch == 'J') ch = 'I';
		result += ch;
	}
	return result;
}

vector<pair<int, int>> makePlainPairs(const string &text) {
	vector<pair<int, int>> result;
	string str = normalizeText(text);
	int i = 0;
	while (i < static_cast<int>(str.size())) {
		char first = str[i];
		if (i + 1 == static_cast<int>(str.size())) {
			char second = first == 'X' ? 'Q' : 'X';
			result.push_back({getId(first), getId(second)});
			i++;
		} else if (str[i] == str[i + 1]) {
			char second = first == 'X' ? 'Q' : 'X';
			result.push_back({getId(first), getId(second)});
			i++;
		} else {
			result.push_back({getId(first), getId(str[i + 1])});
			i += 2;
		}
	}
	return result;
}

vector<pair<int, int>> readCode(const vector<string> &lines) {
	vector<pair<int, int>> result;
	for (const string &line : lines) {
		stringstream ss(line);
		string token;
		while (ss >> token)
			result.push_back({getId(token[0]), getId(token[1])});
	}
	return result;
}

void encodeCell(int first, int second, int &third, int &fourth) {
	int firstRow = posArr[first] / 5, firstCol = posArr[first] % 5;
	int secondRow = posArr[second] / 5, secondCol = posArr[second] % 5;
	if (firstRow == secondRow) {
		third = firstRow * 5 + (firstCol + 1) % 5;
		fourth = secondRow * 5 + (secondCol + 1) % 5;
	} else if (firstCol == secondCol) {
		third = ((firstRow + 1) % 5) * 5 + firstCol;
		fourth = ((secondRow + 1) % 5) * 5 + secondCol;
	} else {
		third = firstRow * 5 + secondCol;
		fourth = secondRow * 5 + firstCol;
	}
}

void decodeCell(int first, int second, int &third, int &fourth) {
	int firstRow = posArr[first] / 5, firstCol = posArr[first] % 5;
	int secondRow = posArr[second] / 5, secondCol = posArr[second] % 5;
	if (firstRow == secondRow) {
		third = firstRow * 5 + (firstCol + 4) % 5;
		fourth = secondRow * 5 + (secondCol + 4) % 5;
	} else if (firstCol == secondCol) {
		third = ((firstRow + 4) % 5) * 5 + firstCol;
		fourth = ((secondRow + 4) % 5) * 5 + secondCol;
	} else {
		third = firstRow * 5 + secondCol;
		fourth = secondRow * 5 + firstCol;
	}
}

bool searchKey();

bool applyCandidate(const vector<pair<int, int>> &candidate) {
	vector<int> changed;
	for (const pair<int, int> &item : candidate) {
		int letter = item.first, cell = item.second;
		if (posArr[letter] != -1) {
			if (posArr[letter] != cell) {
				for (int changedLetter : changed) {
					usedArr[posArr[changedLetter]] = 0;
					posArr[changedLetter] = -1;
				}
				return false;
			}
			continue;
		}
		if (usedArr[cell]) {
			for (int changedLetter : changed) {
				usedArr[posArr[changedLetter]] = 0;
				posArr[changedLetter] = -1;
			}
			return false;
		}
		posArr[letter] = cell;
		usedArr[cell] = 1;
		changed.push_back(letter);
	}
	if (searchKey()) return true;
	for (int letter : changed) {
		usedArr[posArr[letter]] = 0;
		posArr[letter] = -1;
	}
	return false;
}

bool searchKey() {
	int bestIndex = -1, bestScore = -1;
	for (int i = 0; i < static_cast<int>(rules.size()); i++) {
		Rule rule = rules[i];
		int plainCount = (posArr[rule.a] != -1) + (posArr[rule.b] != -1);
		int codeCount = (posArr[rule.c] != -1) + (posArr[rule.d] != -1);
		bool useful = false;
		if (plainCount == 2 && codeCount < 2) useful = true;
		if (codeCount == 2 && plainCount < 2) useful = true;
		if (plainCount == 1 || codeCount == 1) useful = true;
		if (!useful) continue;
		int score = plainCount + codeCount;
		if (score > bestScore) {
			bestScore = score;
			bestIndex = i;
		}
	}
	if (bestIndex == -1) {
		for (int letter = 0; letter < 25; letter++) {
			if (posArr[letter] != -1) continue;
			for (int cell = 0; cell < 25; cell++) {
				if (usedArr[cell]) continue;
				if (applyCandidate({{letter, cell}})) return true;
			}
			return false;
		}
		for (const Rule &rule : rules) {
			if (posArr[rule.a] == -1 || posArr[rule.b] == -1 || posArr[rule.c] == -1 || posArr[rule.d] == -1)
				return false;
			int third, fourth;
			encodeCell(rule.a, rule.b, third, fourth);
			if (third != posArr[rule.c] || fourth != posArr[rule.d])
				return false;
		}
		return true;
	}
	Rule rule = rules[bestIndex];
	int plainCount = (posArr[rule.a] != -1) + (posArr[rule.b] != -1);
	int codeCount = (posArr[rule.c] != -1) + (posArr[rule.d] != -1);
	if (plainCount == 2) {
		int third, fourth;
		encodeCell(rule.a, rule.b, third, fourth);
		if (posArr[rule.c] != -1 && posArr[rule.c] != third) return false;
		if (posArr[rule.d] != -1 && posArr[rule.d] != fourth) return false;
		return applyCandidate({{rule.c, third}, {rule.d, fourth}});
	}
	if (codeCount == 2) {
		int third, fourth;
		decodeCell(rule.c, rule.d, third, fourth);
		if (posArr[rule.a] != -1 && posArr[rule.a] != third) return false;
		if (posArr[rule.b] != -1 && posArr[rule.b] != fourth) return false;
		return applyCandidate({{rule.a, third}, {rule.b, fourth}});
	}
	if (posArr[rule.a] != -1 && posArr[rule.b] == -1) {
		for (int cell = 0; cell < 25; cell++) {
			if (usedArr[cell]) continue;
			posArr[rule.b] = cell;
			int third, fourth;
			encodeCell(rule.a, rule.b, third, fourth);
			posArr[rule.b] = -1;
			if (posArr[rule.c] != -1 && posArr[rule.c] != third) continue;
			if (posArr[rule.d] != -1 && posArr[rule.d] != fourth) continue;
			if (applyCandidate({{rule.b, cell}, {rule.c, third}, {rule.d, fourth}}))
			return true;
		}
	}
	if (posArr[rule.b] != -1 && posArr[rule.a] == -1) {
		for (int cell = 0; cell < 25; cell++) {
			if (usedArr[cell]) continue;
			posArr[rule.a] = cell;
			int third, fourth;
			encodeCell(rule.a, rule.b, third, fourth);
			posArr[rule.a] = -1;
			if (posArr[rule.c] != -1 && posArr[rule.c] != third) continue;
			if (posArr[rule.d] != -1 && posArr[rule.d] != fourth) continue;
			if (applyCandidate({{rule.a, cell}, {rule.c, third}, {rule.d, fourth}}))
			return true;
		}
	}
	if (posArr[rule.c] != -1 && posArr[rule.d] == -1) {
		for (int cell = 0; cell < 25; cell++) {
			if (usedArr[cell]) continue;
			posArr[rule.d] = cell;
			int third, fourth;
			decodeCell(rule.c, rule.d, third, fourth);
			posArr[rule.d] = -1;
			if (posArr[rule.a] != -1 && posArr[rule.a] != third) continue;
			if (posArr[rule.b] != -1 && posArr[rule.b] != fourth) continue;
			if (applyCandidate({{rule.d, cell}, {rule.a, third}, {rule.b, fourth}}))
			return true;
		}
	}
	if (posArr[rule.d] != -1 && posArr[rule.c] == -1) {
		for (int cell = 0; cell < 25; cell++) {
			if (usedArr[cell]) continue;
			posArr[rule.c] = cell;
			int third, fourth;
			decodeCell(rule.c, rule.d, third, fourth);
			posArr[rule.c] = -1;
			if (posArr[rule.a] != -1 && posArr[rule.a] != third) continue;
			if (posArr[rule.b] != -1 && posArr[rule.b] != fourth) continue;
			if (applyCandidate({{rule.c, cell}, {rule.a, third}, {rule.b, fourth}}))
			return true;
		}
	}
	return false;
}

bool recoverKey() {
	fill(posArr, posArr + 25, -1);
	fill(usedArr, usedArr + 25, 0);
	Rule first = rules[0];
	for (int firstCell = 0; firstCell < 25; firstCell++) {
		for (int secondCell = 0; secondCell < 25; secondCell++) {
			if (firstCell == secondCell) continue;
			posArr[first.a] = firstCell;
			posArr[first.b] = secondCell;
			usedArr[firstCell] = 1;
			usedArr[secondCell] = 1;
			int third, fourth;
			encodeCell(first.a, first.b, third, fourth);
			posArr[first.a] = -1;
			posArr[first.b] = -1;
			usedArr[firstCell] = 0;
			usedArr[secondCell] = 0;
			if (applyCandidate({{first.a, firstCell}, {first.b, secondCell}, {first.c, third}, {first.d, fourth}}))
			return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testCount;
	cin >> testCount;
	string line;
	getline(cin, line);
	for (int caseId = 1; caseId <= testCount; caseId++) {
		vector<string> plainLines, codeLines, targetLines;
		while (getline(cin, line) && line != "#")
			plainLines.push_back(line);
		while (getline(cin, line) && line != "#")
			codeLines.push_back(line);
		while (getline(cin, line) && line != "#")
			targetLines.push_back(line);
		string plainText;
		for (const string &part : plainLines)
			plainText += part;
		vector<pair<int, int>> plainPairs = makePlainPairs(plainText);
		vector<pair<int, int>> codePairs = readCode(codeLines);
		vector<pair<int, int>> targetPairs = readCode(targetLines);
		rules.clear();
		for (int i = 0; i < static_cast<int>(plainPairs.size()); i++)
			rules.push_back({plainPairs[i].first, plainPairs[i].second, codePairs[i].first, codePairs[i].second});
		recoverKey();
		fill(cellChar, cellChar + 25, -1);
		for (int letter = 0; letter < 25; letter++)
			if (posArr[letter] != -1)
				cellChar[posArr[letter]] = letter;
		cout << "Case " << caseId << ":\n";
		for (int i = 0; i < static_cast<int>(targetPairs.size()); i++) {
			int first, second;
			decodeCell(targetPairs[i].first, targetPairs[i].second, first, second);
			cout << getChar(cellChar[first]) << getChar(cellChar[second]);
			if (i % 20 == 19 || i + 1 == static_cast<int>(targetPairs.size()))
				cout << '\n';
			else
				cout << ' ';
		}
		if (caseId != testCount)
			cout << '\n';
	}
	return 0;
}
