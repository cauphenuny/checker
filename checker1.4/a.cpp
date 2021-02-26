#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")



#include<bits/stdc++.h>
#define int long long
long long a[100010], m, maxa;
long long base[100010], sum[100010];
int n;

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long max(long long a, long long b) {
    return a > b? a : b;
}
inline int read(){
	int x=0;
	char c=getchar();
	while (!isdigit(c))c=getchar();
	while (isdigit(c))x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}

signed main() {
	n=read();
	for (int i = 1; i <= n; i++) {
		a[i]=read();
		maxa = max(maxa, a[i]);
	}
	int maxpa = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 63; j++) {
			base[j] += ((a[i] >> j) & 1) ? 0:1;
		}
	}
	while (maxa) {maxpa++, maxa /= 2;}
	sum[1] = min(base[0], n - base[0]);
	for (int i = 1; i <= 63; i++) {
		sum[i + 1] = sum[i] + min(base[i], n - base[i]) * (1 << i);
		if (sum[i + 1] < 0) {
			sum[i + 1] = 0;
			break;
		}
	}
//	maxpa++;
	//for (int j = 0; j <= maxpa; j++) {
	//	printf("base[%d]=%d\n", j, base[j]);
	//}
	int q;
	q=read();
	for (int i = 1; i <= q; i++) {
		m=read();
		long long now = 0, ans = 0, t = m;
		int maxp = 0;
		while (t) {maxp++, t /= 2;}maxp = max(maxp, maxpa);
		for (int j = maxp; j >= 0; j--) {
		//	cout << maxp << maxp << endl;
//			if (base[j] > (1ll << (62 - j))) {continue;}
			if ((now + base[j] * (1ll << j) + sum[j]) < 0) continue;
			if ((now + base[j] * (1ll << j) + sum[j]) <= m) {
				now += base[j] * (1ll << j);
				ans += (1ll << j);
				//cout << j << endl;
			} else {
				now += (n - base[j]) * (1ll << j);
			}
			if (now > m) {
				ans = -1;
				break;
			}
		}
		printf("%lld\n", ans);;
	}
	return 0;
}
