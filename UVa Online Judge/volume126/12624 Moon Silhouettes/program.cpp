#include <bits/stdc++.h>
using namespace std;

string formatTruncated(long double value, int digits) {
    unsigned long long scale = 1;
    for (int i = 0; i < digits; i++) scale *= 10;
    unsigned long long scaledValue = static_cast<unsigned long long>(floorl(value * scale + 1e-12L));
    unsigned long long integerPart = scaledValue / scale, fractionalPart = scaledValue % scale;
    if (fractionalPart == 0) return to_string(integerPart);
    string fractionalText = to_string(fractionalPart);
    if (fractionalText.size() < static_cast<size_t>(digits)) fractionalText = string(digits - fractionalText.size(), '0') + fractionalText;
    while (fractionalText.back() == '0') fractionalText.pop_back();
    return to_string(integerPart) + "." + fractionalText;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    const long double moonDistance = 384000.0L, moonDiameter = 3476.0L, personHeight = 0.0018L;
    const long double pi = acosl(-1.0L);
    while (testCount--) {
        int imageWidth, imageHeight, moonPixels, personPixels;
        cin >> imageWidth >> imageHeight >> moonPixels >> personPixels;
        long double focalLength = moonPixels * moonDistance / moonDiameter;
        long double personDistance = focalLength * personHeight / personPixels;
        long double fieldOfView = 2.0L * atanl(imageHeight / (2.0L * focalLength)) * 180.0L / pi;
        cout << formatTruncated(personDistance, 2) << " " << formatTruncated(fieldOfView, 3) << '\n';
    }
    return 0;
}
