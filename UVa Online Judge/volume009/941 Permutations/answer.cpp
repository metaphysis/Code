#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

char buf[22];
long long factorial[22];
void cantor_expansion(long long n, int m)
{
	for (int i = m-1; i >= 0; -- i) {
		long long index = n/factorial[i], count = 0;
		for (int j = 0; j < m; ++ j) {
			if (buf[j]) {
				if (count == index) {
					printf("%c",buf[j]);
					buf[j] = 0;
					break;
				}else {
					count ++;
				}
			}
		}
		n %= factorial[i];
	}
	puts("");
}

int main()
{
	factorial[0] = 1LL;
	for (int i = 1; i < 21; ++ i)
		factorial[i] = factorial[i-1]*i;
	
	long long n, m;
	while (~scanf("%lld",&m))
	while (m --) {
		scanf("%s%lld",buf,&n);
		sort(buf, buf+strlen(buf));
		cantor_expansion(n, strlen(buf));
	}
    return 0;
}

