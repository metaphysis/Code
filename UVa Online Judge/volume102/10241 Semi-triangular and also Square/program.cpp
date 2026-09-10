#include <bits/stdc++.h>
using namespace std;

class BigInteger {
private:
    static const unsigned long long base = 1000000000ULL;
    vector<unsigned long long> digits;

    void removeLeadingZeros() {
        while (!digits.empty() && digits.back() == 0) digits.pop_back();
    }

public:
    BigInteger(unsigned long long value = 0) {
        while (value > 0) {
            digits.push_back(value % base);
            value /= base;
        }
    }

    bool isZero() const {
        return digits.empty();
    }

    bool operator < (const BigInteger& other) const {
        if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i)
            if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
        return false;
    }

    bool operator == (const BigInteger& other) const {
        return digits == other.digits;
    }

    BigInteger operator + (const BigInteger& other) const {
        BigInteger result;
        unsigned long long carry = 0;
        size_t maxSize = max(digits.size(), other.digits.size());
        result.digits.resize(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            unsigned long long current = carry;
            if (i < digits.size()) current += digits[i];
            if (i < other.digits.size()) current += other.digits[i];
            result.digits[i] = current % base;
            carry = current / base;
        }

        if (carry > 0) result.digits.push_back(carry);
        return result;
    }

    BigInteger operator * (unsigned long long multiplier) const {
        BigInteger result;
        if (multiplier == 0 || isZero()) return result;

        result.digits.resize(digits.size());
        unsigned long long carry = 0;

        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned long long current = digits[i] * multiplier + carry;
            result.digits[i] = current % base;
            carry = current / base;
        }

        while (carry > 0) {
            result.digits.push_back(carry % base);
            carry /= base;
        }

        return result;
    }

    BigInteger square() const {
        BigInteger result;
        if (isZero()) return result;

        result.digits.assign(digits.size() * 2, 0);

        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned long long carry = 0;

            for (size_t j = 0; j < digits.size(); ++j) {
                unsigned long long current = result.digits[i + j] + digits[i] * digits[j] + carry;
                result.digits[i + j] = current % base;
                carry = current / base;
            }

            size_t position = i + digits.size();
            while (carry > 0) {
                if (position == result.digits.size()) result.digits.push_back(0);

                unsigned long long current = result.digits[position] + carry;
                result.digits[position] = current % base;
                carry = current / base;
                ++position;
            }
        }

        result.removeLeadingZeros();
        return result;
    }

    string toString() const {
        if (isZero()) return "0";

        string result = to_string(digits.back());

        for (int i = static_cast<int>(digits.size()) - 2; i >= 0; --i) {
            string part = to_string(digits[i]);
            result += string(9 - part.length(), '0') + part;
        }

        return result;
    }
};

struct PellData {
    int squareFreePart;
    int scaleFactor;
    unsigned long long fundamentalX;
    unsigned long long fundamentalY;
};

int main() {
    BigInteger limit(16);

    for (int i = 0; i < 34; ++i) limit = limit * 10;

    vector<PellData> pellData = {
        {1, 1, 3, 1},
        {3, 1, 5, 1},
        {5, 1, 19, 3},
        {7, 1, 15, 2},
        {11, 1, 197, 21},
        {13, 1, 51, 5},
        {15, 1, 11, 1},
        {1, 3, 3, 1}
    };

    vector<BigInteger> answers;

    for (const PellData& data : pellData) {
        unsigned long long coefficient = 8ULL * data.squareFreePart * data.fundamentalY;
        BigInteger currentX(1);
        BigInteger currentY(0);

        while (true) {
            BigInteger nextX = currentX * data.fundamentalX + currentY * coefficient;
            BigInteger nextY = currentX * data.fundamentalY + currentY * data.fundamentalX;

            unsigned long long scale = static_cast<unsigned long long>(data.squareFreePart) * data.scaleFactor;
            BigInteger squareRoot = nextY * scale;
            BigInteger answer = squareRoot.square();

            if (!(answer < limit)) break;

            answers.push_back(answer);
            currentX = nextX;
            currentY = nextY;
        }
    }

    sort(answers.begin(), answers.end());
    answers.erase(unique(answers.begin(), answers.end()), answers.end());

    for (const BigInteger& answer : answers)
        cout << answer.toString() << '\n';

    return 0;
}
