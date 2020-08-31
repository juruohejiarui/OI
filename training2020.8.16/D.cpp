#include <bits/stdc++.h>
#define LL long long
#define NoSOL return printf("-1\n"), 0 

using namespace std;

LL readll() {
	LL t = 1, m = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') t = -1;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9') 
		m = (m << 3) + (m << 1) + ch - '0',
		ch = getchar();
	return t*m;
}
const int maxn = 1e5 + 5;
int n, m;
LL atk[maxn], a[maxn], p[maxn], st[maxn], pri[maxn];
multiset<LL> sword; 

LL smul(LL a, LL b, LL mod) {
	LL ret = 0;
	b %= mod, b = (b > 0 ? b : b + mod);
	while (b) {
		if (b & 1) ret = (a + ret) % mod;
		a = (a+a) % mod, b >>= 1;
	}
	return ret;
}
LL gcd(LL a, LL b) {
	return !b ? a : gcd(b, a % b);
}
void exgcd(LL a, LL b, LL& x, LL& y) {
	if (!b) {
		x = 1, y = 0;
		return ;
	}
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

LL inv(LL a, LL mod) {
	LL x, y;
	a %= mod, exgcd(a, mod, x, y);
	return x < 0 ? x + mod : x;
}


void special1() {
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		LL t = p[i] / gcd(p[i], atk[i]);
		ans = ans / gcd(t, ans) * atk[i];
	}
	printf("%lld\n", ans);
}

void special2() {
	LL ans = 0;
	for (int i = 1; i <= n; i++) 
		ans = max(ans, (a[i]+atk[i]-1) / atk[i]);
	printf("%lld\n", ans);
}

int solve() {
	multiset<LL>::iterator it;
	sword.clear();
	for (int i = 1; i <= m; i++) sword.insert(st[i]);
	//calc atk[] 
	for (int i = 1; i <= n; i++) {
		if (a[i] < *sword.begin()) atk[i] = *(it = sword.begin());
		else atk[i] = *(it = --sword.upper_bound(a[i]));
		sword.erase(it), sword.insert(pri[i]);
	}
	LL fl = true;
	for (int i = 1; i <= n; i++)
		if (a[i] != p[i]) fl = false;
	if (fl) return special1(), 0;
	fl = true;
	for (int i = 1; i <= n; i++) 
		if (p[i] != 1) fl = false;
	if (fl) return special2(), 0;
	//calc x
	LL x = 0;
	for (int i = 1; i <= n; i++) atk[i] %= p[i];
	for (int i = 1; i <= n; i++) if (!atk[i]) {
		if (a[i] == p[i]) atk[i] = p[i] = 1, a[i] = 0;
		else NoSOL;
	}
	for (int i = 1; i <= n; i++) {
		LL spx, spy, g = gcd(atk[i], p[i]);
		if (a[i] % g != 0) NoSOL;
		exgcd(atk[i], p[i], spx, spy);
		p[i] /= g, 
		spx = (spx%p[i]+p[i])%p[i], 
		a[i] = smul(spx, a[i]/g, p[i]);
	}
	for (int i = 1; i < n; i++) {
		LL g = gcd(p[i], p[i+1]);
		if ((a[i+1] - a[i]) % g != 0) NoSOL;
		LL v = inv(p[i] / g, p[i+1] / g);
		LL 	new_a = smul(v, (a[i+1] - a[i]) / g, p[i+1] / g),
			new_p = p[i] / g * p[i+1];
		new_a = smul(new_a, p[i], new_p);
		p[i+1] = new_p, a[i+1] = (new_a+a[i]) % new_p;
	}
	printf("%lld\n", a[n]);
	return 0;
}

int main() {
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) a[i] = readll();
		for (int i = 1; i <= n; i++) p[i] = readll();
		for (int i = 1; i <= n; i++) pri[i] = readll();
		for (int i = 1; i <= m; i++) st[i] = readll();
		solve();
	}
	return 0;
}