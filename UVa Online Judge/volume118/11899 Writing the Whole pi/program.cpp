#include <bits/stdc++.h>
using namespace std;

struct Candidate {
    string text;
    long double error;
};

long long powerTen[11];

int getDigitCount(long long number) {
    int digitCount = 0;
    do {
        digitCount++;
        number /= 10;
    } while (number > 0);
    return digitCount;
}

string makeDecimal(long long numerator, long long denominator) {
    if (denominator == 1)
        return to_string(numerator);
    long long integerPart = numerator / denominator, fractionPart = numerator % denominator;
    int fractionWidth = getDigitCount(denominator) - 1;
    string fractionText = to_string(fractionPart);
    while ((int)fractionText.size() < fractionWidth)
        fractionText = "0" + fractionText;
    while (!fractionText.empty() && fractionText.back() == '0')
        fractionText.pop_back();
    if (fractionText.empty())
        return to_string(integerPart);
    return to_string(integerPart) + "." + fractionText;
}

void updateDecimalCandidate(vector<Candidate> &candidates, long long numerator, long long denominator, long double root, int maxSymbols) {
    string text = makeDecimal(numerator, denominator);
    if ((int)text.size() > maxSymbols)
        return;
    long double value = (long double)numerator / (long double)denominator;
    long double error = fabsl(value - root);
    candidates.push_back({text, error});
}

void updateFractionCandidate(vector<Candidate> &candidates, long long numerator, long long denominator, long double root, int maxSymbols) {
    if (numerator <= 0 || denominator <= 0)
        return;
    string text = to_string(numerator) + "/" + to_string(denominator);
    if ((int)text.size() > maxSymbols)
        return;
    long double value = (long double)numerator / (long double)denominator;
    long double error = fabsl(value - root);
    candidates.push_back({text, error});
}

void generateDecimalCandidates(vector<Candidate> &candidates, long double root, int maxSymbols) {
    for (int decimalPlaces = 0; decimalPlaces <= maxSymbols; decimalPlaces++) {
        long long scale = powerTen[decimalPlaces];
        long long baseNumerator = (long long)floorl(root * (long double)scale);
        for (int offset = 0; offset <= 1; offset++)
            updateDecimalCandidate(candidates, baseNumerator + offset, scale, root, maxSymbols);
    }
}

void generateFractionCandidates(vector<Candidate> &candidates, long double root, long long maxNumerator, long long maxDenominator, int maxSymbols) {
    long long usefulDenominator = (long long)floorl((long double)maxNumerator / root);
    usefulDenominator = min(usefulDenominator, maxDenominator);
    if (usefulDenominator >= 1) {
        long long previousNumerator = 0, currentNumerator = 1;
        long long previousDenominator = 1, currentDenominator = 0;
        long double value = root;
        while (true) {
            long long coefficient = (long long)floorl(value);
            long long nextNumerator = coefficient * currentNumerator + previousNumerator;
            long long nextDenominator = coefficient * currentDenominator + previousDenominator;
            if (nextDenominator > usefulDenominator) {
                if (currentDenominator > 0) {
                    long long count = (usefulDenominator - previousDenominator) / currentDenominator;
                    if (count >= 1) {
                        long long numerator = previousNumerator + count * currentNumerator;
                        long long denominator = previousDenominator + count * currentDenominator;
                        if (numerator <= maxNumerator && denominator <= maxDenominator)
                            updateFractionCandidate(candidates, numerator, denominator, root, maxSymbols);
                    }
                }
                break;
            }
            if (nextNumerator <= maxNumerator)
                updateFractionCandidate(candidates, nextNumerator, nextDenominator, root, maxSymbols);
            long double remainder = value - (long double)coefficient;
            if (fabsl(remainder) < 1e-18L)
                break;
            previousNumerator = currentNumerator;
            currentNumerator = nextNumerator;
            previousDenominator = currentDenominator;
            currentDenominator = nextDenominator;
            value = 1.0L / remainder;
        }
    }
    long long borderDenominator = (long long)floorl((long double)maxNumerator / root);
    if (borderDenominator >= 1 && borderDenominator <= maxDenominator)
        updateFractionCandidate(candidates, maxNumerator, borderDenominator, root, maxSymbols);
    if (borderDenominator + 1 <= maxDenominator)
        updateFractionCandidate(candidates, maxNumerator, borderDenominator + 1, root, maxSymbols);
}

bool isBetter(const Candidate &current, const Candidate &best) {
    const long double epsilon = 1e-18L;
    if (current.error < best.error - epsilon)
        return true;
    if (fabsl(current.error - best.error) > epsilon)
        return false;
    if (current.text.size() != best.text.size())
        return current.text.size() < best.text.size();
    return current.text < best.text;
}

int solve() {
    int testCases;
    cin >> testCases;
    for (int caseNumber = 1; caseNumber <= testCases; caseNumber++) {
        int rootDegree, valueN, maxSymbols;
        cin >> rootDegree >> valueN >> maxSymbols;
        long double root = powl((long double)valueN, 1.0L / (long double)rootDegree);
        vector<Candidate> candidates;
        generateDecimalCandidates(candidates, root, maxSymbols);
        for (int numeratorDigits = 1; numeratorDigits <= maxSymbols - 2; numeratorDigits++) {
            for (int denominatorDigits = 1; numeratorDigits + denominatorDigits + 1 <= maxSymbols; denominatorDigits++) {
                long long maxNumerator = powerTen[numeratorDigits] - 1;
                long long maxDenominator = powerTen[denominatorDigits] - 1;
                generateFractionCandidates(candidates, root, maxNumerator, maxDenominator, maxSymbols);
            }
        }
        Candidate bestCandidate = candidates[0];
        for (const Candidate &candidate : candidates)
            if (isBetter(candidate, bestCandidate))
                bestCandidate = candidate;
        cout << "Case " << caseNumber << ": " << bestCandidate.text << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    powerTen[0] = 1;
    for (int i = 1; i <= 10; i++)
        powerTen[i] = powerTen[i - 1] * 10;
    return solve();
}
