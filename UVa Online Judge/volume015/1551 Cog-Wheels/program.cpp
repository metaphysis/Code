#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const vector<int> primeList = {2, 3, 5, 7, 11, 13, 17, 19};

int factorValue(int value, int sign, vector<ll>& exponent) {
    for (int i = 0; i < (int)primeList.size(); i++) {
        while (value % primeList[i] == 0) {
            exponent[i] += sign;
            value /= primeList[i];
        }
    }
    return value;
}

int diagonalize(vector<vector<ll>>& matrix, vector<ll>& rhs, vector<vector<ll>>& transform) {
    int rowCount = matrix.size(), columnCount = transform.size(), rank = 0;
    while (rank < rowCount && rank < columnCount) {
        int pivotRow = -1, pivotColumn = -1;
        for (int i = rank; i < rowCount && pivotRow == -1; i++) {
            for (int j = rank; j < columnCount; j++) {
                if (matrix[i][j] != 0) {
                    pivotRow = i;
                    pivotColumn = j;
                    break;
                }
            }
        }
        if (pivotRow == -1) break;
        swap(matrix[rank], matrix[pivotRow]);
        swap(rhs[rank], rhs[pivotRow]);
        for (int i = 0; i < rowCount; i++) swap(matrix[i][rank], matrix[i][pivotColumn]);
        for (int i = 0; i < columnCount; i++) swap(transform[i][rank], transform[i][pivotColumn]);
        while (true) {
            bool changed = false;
            for (int i = rank + 1; i < rowCount; i++) {
                if (matrix[i][rank] != 0) {
                    ll quotient = matrix[i][rank] / matrix[rank][rank];
                    for (int j = rank; j < columnCount; j++) matrix[i][j] -= quotient * matrix[rank][j];
                    rhs[i] -= quotient * rhs[rank];
                    if (matrix[i][rank] != 0) {
                        swap(matrix[i], matrix[rank]);
                        swap(rhs[i], rhs[rank]);
                    }
                    changed = true;
                    break;
                }
            }
            if (changed) continue;
            for (int j = rank + 1; j < columnCount; j++) {
                if (matrix[rank][j] != 0) {
                    ll quotient = matrix[rank][j] / matrix[rank][rank];
                    for (int i = 0; i < rowCount; i++) matrix[i][j] -= quotient * matrix[i][rank];
                    for (int i = 0; i < columnCount; i++) transform[i][j] -= quotient * transform[i][rank];
                    if (matrix[rank][j] != 0) {
                        for (int i = 0; i < rowCount; i++) swap(matrix[i][j], matrix[i][rank]);
                        for (int i = 0; i < columnCount; i++) swap(transform[i][j], transform[i][rank]);
                    }
                    changed = true;
                    break;
                }
            }
            if (!changed) break;
        }
        rank++;
    }
    return rank;
}

ll floorDivide(ll dividend, ll divisor) {
    ll quotient = dividend / divisor, remainder = dividend % divisor;
    if (remainder != 0 && ((remainder > 0) != (divisor > 0))) quotient--;
    return quotient;
}

ll coefficientCost(const vector<ll>& coefficient) {
    ll cost = 0;
    for (ll value : coefficient) cost += llabs(value);
    return cost;
}

void reduceCoefficients(vector<ll>& coefficient, const vector<vector<ll>>& transform, int rank) {
    int size = coefficient.size();
    bool improved = true;
    while (improved) {
        improved = false;
        for (int column = rank; column < size; column++) {
            vector<ll> candidate = {0};
            for (int row = 0; row < size; row++) {
                if (transform[row][column] != 0) {
                    ll value = floorDivide(-coefficient[row], transform[row][column]);
                    candidate.push_back(value);
                    candidate.push_back(value + 1);
                }
            }
            ll bestStep = 0, bestCost = coefficientCost(coefficient);
            for (ll step : candidate) {
                ll currentCost = 0;
                for (int row = 0; row < size; row++) currentCost += llabs(coefficient[row] + step * transform[row][column]);
                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    bestStep = step;
                }
            }
            if (bestStep != 0) {
                for (int row = 0; row < size; row++) coefficient[row] += bestStep * transform[row][column];
                improved = true;
            }
        }
    }
}

bool findCoefficients(const vector<int>& normalized, const vector<ll>& target, vector<ll>& coefficient) {
    int rowCount = primeList.size(), columnCount = normalized.size();
    vector<vector<ll>> matrix(rowCount, vector<ll>(columnCount, 0));
    for (int column = 0; column < columnCount; column++) {
        int value = normalized[column];
        for (int row = 0; row < rowCount; row++) {
            while (value % primeList[row] == 0) {
                matrix[row][column]++;
                value /= primeList[row];
            }
        }
    }
    vector<vector<ll>> transform(columnCount, vector<ll>(columnCount, 0));
    for (int i = 0; i < columnCount; i++) transform[i][i] = 1;
    vector<ll> rhs = target;
    int rank = diagonalize(matrix, rhs, transform);
    for (int i = 0; i < rank; i++)
        if (rhs[i] % matrix[i][i] != 0) return false;
    for (int i = rank; i < rowCount; i++)
        if (rhs[i] != 0) return false;
    vector<ll> changedVariable(columnCount, 0);
    for (int i = 0; i < rank; i++) changedVariable[i] = rhs[i] / matrix[i][i];
    coefficient.assign(columnCount, 0);
    for (int i = 0; i < columnCount; i++)
        for (int j = 0; j < columnCount; j++)
            coefficient[i] += transform[i][j] * changedVariable[j];
    reduceCoefficients(coefficient, transform, rank);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int sizeCount, setNumber = 0;
    while (cin >> sizeCount && sizeCount != 0) {
        vector<int> wheel(sizeCount);
        for (int& value : wheel) cin >> value;
        int minimumWheel = *min_element(wheel.begin(), wheel.end());
        set<int> normalizedSet;
        for (int value : wheel)
            if (value / minimumWheel > 1) normalizedSet.insert(value / minimumWheel);
        vector<int> normalized(normalizedSet.begin(), normalizedSet.end());
        cout << "Set #" << ++setNumber << '\n';
        int numerator, denominator;
        while (cin >> numerator >> denominator && (numerator != 0 || denominator != 0)) {
            cout << "Ratio " << numerator << ':' << denominator << ':';
            int divisor = __gcd(numerator, denominator);
            int reducedNumerator = numerator / divisor, reducedDenominator = denominator / divisor;
            vector<ll> target(primeList.size(), 0), coefficient;
            int remainingNumerator = factorValue(reducedNumerator, 1, target);
            int remainingDenominator = factorValue(reducedDenominator, -1, target);
            bool possible = remainingNumerator == 1 && remainingDenominator == 1;
            if (possible) possible = findCoefficients(normalized, target, coefficient);
            if (!possible) {
                cout << " Impossible\n";
                continue;
            }
            for (int i = 0; i < (int)normalized.size(); i++) {
                int currentWheel = normalized[i] * minimumWheel;
                if (coefficient[i] > 0) {
                    for (ll count = 0; count < coefficient[i]; count++) cout << ' ' << currentWheel << ':' << minimumWheel;
                } else {
                    for (ll count = 0; count < -coefficient[i]; count++) cout << ' ' << minimumWheel << ':' << currentWheel;
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
