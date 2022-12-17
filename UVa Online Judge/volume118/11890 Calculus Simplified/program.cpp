// Calculus Simplified
// UVa ID: 11890
// Verdict: Accepted
// Submission Date: 2022-11-23
// UVa Run Time: 0.190s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string E;
int T, N, a[100010], symbols[100010], cnt = 0;
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> T;
	while (T--) {
		cin >> E >> N;
		for (int i = 0; i < N; i++)
			cin >> a[i];
		sort(a, a + N);
		int lp = 0, rp = N - 1;
		int sign = 1, answer = 0;
		for (int i = 0; i < E.length(); i++) {
			if (E[i] == '(') {
				symbols[cnt] = i ? (E[i - 1] == '-' ? -1 : 1) : 1;
				sign *= symbols[cnt++];
			} else if (E[i] == ')') {
				sign /= symbols[--cnt];
			} else if (E[i] == 'x') {
				int plus = sign;
				if (i && (E[i - 1] == '+' || E[i - 1] == '-'))
					plus *= (E[i - 1] == '+' ? 1 : -1);
				if (plus == 1)
					answer += a[rp--];
				else
					answer -= a[lp++];
			}
		}
		cout << answer << '\n';
	}
	return 0;
}
