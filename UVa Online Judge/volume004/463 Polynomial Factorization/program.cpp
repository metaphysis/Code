// Polynomial Factorization
// UVa ID: 463
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Polynomial {
    vector<int> coeffs;
    Polynomial() {}
    Polynomial(const vector<int>& c) : coeffs(c) {}

    int degree() const {
        for (int i = 0; i < coeffs.size(); i++) {
            if (coeffs[i] != 0) return coeffs.size() - 1 - i;
        }
        return -1;
    }

    int eval(int x) const {
        int result = 0;
        int power = 1;
        for (int i = coeffs.size() - 1; i >= 0; i--) {
            result += coeffs[i] * power;
            power *= x;
        }
        return result;
    }

    bool is_zero() const {
        for (int coef : coeffs) {
            if (coef != 0) return false;
        }
        return true;
    }

    void normalize() {
        int start = 0;
        while (start < coeffs.size() && coeffs[start] == 0) start++;
        if (start > 0) {
            vector<int> new_coeffs(coeffs.begin() + start, coeffs.end());
            coeffs = new_coeffs;
        }
        if (coeffs.empty()) coeffs.push_back(0);
    }
};

vector<int> get_factors(int n) {
    vector<int> factors;
    if (n == 0) {
        for (int i = 1; i <= 100; i++) {
            factors.push_back(i);
            factors.push_back(-i);
        }
        return factors;
    }
    n = abs(n);
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            factors.push_back(-i);
        }
    }
    return factors;
}

pair<Polynomial, Polynomial> poly_divide(const Polynomial& dividend, const Polynomial& divisor) {
    if (divisor.is_zero()) return make_pair(Polynomial(), Polynomial());

    vector<int> rem = dividend.coeffs;
    vector<int> quot;
    int deg_dividend = dividend.degree();
    int deg_divisor = divisor.degree();

    if (deg_dividend < deg_divisor) return make_pair(Polynomial(vector<int>(1, 0)), dividend);

    quot.resize(deg_dividend - deg_divisor + 1, 0);

    for (int i = 0; i <= deg_dividend - deg_divisor; i++) {
        if (rem[i] % divisor.coeffs[0] != 0) return make_pair(Polynomial(), Polynomial());
        int factor = rem[i] / divisor.coeffs[0];
        quot[i] = factor;
        for (int j = 0; j <= deg_divisor; j++) rem[i + j] -= factor * divisor.coeffs[j];
    }

    bool all_zero = true;
    for (int coef : rem) {
        if (coef != 0) {
            all_zero = false;
            break;
        }
    }
    
    if (all_zero) {
        Polynomial quotient(quot);
        quotient.normalize();
        return make_pair(quotient, Polynomial(vector<int>(1, 0)));
    }
    
    return make_pair(Polynomial(), Polynomial());
}

bool find_linear_factor(const Polynomial& poly, Polynomial& factor) {
    if (poly.degree() < 1) return false;
    vector<int> p_factors = get_factors(poly.coeffs[0]);
    vector<int> q_factors = get_factors(poly.coeffs.back());
    
    for (int p : p_factors) {
        if (p == 0) continue;
        for (int q : q_factors) {
            if (poly.eval(-q) * p == poly.eval(0) * (-q)) {
                Polynomial test_factor(vector<int>{p, q});
                pair<Polynomial, Polynomial> result = poly_divide(poly, test_factor);
                if (!result.first.coeffs.empty() && result.second.is_zero()) {
                    factor = test_factor;
                    return true;
                }
            }
        }
    }
    return false;
}

bool find_quadratic_factor_optimized(const Polynomial& poly, Polynomial& factor) {
    if (poly.degree() < 2) return false;
    int a = poly.coeffs[0], b = poly.coeffs[1], c_val = poly.coeffs[2], d = poly.coeffs[3], e = poly.coeffs[4];
    vector<int> a_values = get_factors(a), c_values = get_factors(e);
    for (int a1 : a_values) {
        if (a1 == 0) continue;
        for (int c1 : c_values) {
            if (a % a1 != 0) continue;
            int d1 = a / a1;
            if (c1 == 0 || e % c1 != 0) continue;
            int f1 = e / c1;
            for (int b1_val = -200; b1_val <= 200; b1_val++) {
                if ((b - b1_val * d1) % a1 != 0) continue;
                int e1_val = (b - b1_val * d1) / a1;
                if (b1_val * f1 + c1 * e1_val == d && a1 * f1 + b1_val * e1_val + c1 * d1 == c_val) {
                    Polynomial test_factor(vector<int>{a1, b1_val, c1});
                    pair<Polynomial, Polynomial> result = poly_divide(poly, test_factor);
                    if (!result.first.coeffs.empty() && result.second.is_zero()) {
                        factor = test_factor;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

vector<Polynomial> factor_polynomial_final(Polynomial poly) {
    vector<Polynomial> factors;
    poly.normalize();
    if (poly.is_zero() || poly.degree() == -1) {
        factors.push_back(Polynomial(vector<int>(1, 0)));
        return factors;
    }
    while (poly.degree() > 0) {
        bool found = false;
        Polynomial linear_factor;
        if (find_linear_factor(poly, linear_factor)) {
            factors.push_back(linear_factor);
            poly = poly_divide(poly, linear_factor).first;
            poly.normalize();
            found = true;
            continue;
        }
        if (poly.degree() >= 3) {
            Polynomial quadratic_factor;
            if (find_quadratic_factor_optimized(poly, quadratic_factor)) {
                factors.push_back(quadratic_factor);
                poly = poly_divide(poly, quadratic_factor).first;
                poly.normalize();
                found = true;
                continue;
            }
        }
        if (!found) break;
    }
    if (!poly.is_zero() && poly.degree() >= 0) factors.push_back(poly);
    return factors;
}

bool compare_polynomials(const Polynomial& a, const Polynomial& b) {
    int deg_a = a.degree(), deg_b = b.degree();
    if (deg_a != deg_b) return deg_a < deg_b;
    for (int i = 0; i < a.coeffs.size() && i < b.coeffs.size(); i++) {
        if (a.coeffs[i] != b.coeffs[i]) return a.coeffs[i] > b.coeffs[i];
    }
    return a.coeffs.size() < b.coeffs.size();
}

void adjust_coefficients(vector<Polynomial>& factors) {
    for (int i = 0; i < factors.size(); i++) {
        if (factors[i].coeffs[0] < 0 && i != factors.size() - 1) {
            for (int j = 0; j < factors[i].coeffs.size(); j++) factors[i].coeffs[j] = -factors[i].coeffs[j];
        }
    }
}

int main(int argc, char* argv[]) {
    int a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e) {
        Polynomial poly(vector<int>{a, b, c, d, e});
        vector<Polynomial> factors = factor_polynomial_final(poly);
        sort(factors.begin(), factors.end(), compare_polynomials);
        adjust_coefficients(factors);
        for (const auto& factor : factors) {
            for (int i = 0; i < factor.coeffs.size(); i++) {
                if (i > 0) cout << " ";
                cout << factor.coeffs[i];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
