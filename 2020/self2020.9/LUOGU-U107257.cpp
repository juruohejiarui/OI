#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int maxn = 5e3 + 5;
const LL MOD = 998244353;

LL NTT_g, NTT_inv_g, f[maxn], tmp[maxn][maxn];
LL f1[maxn][maxn], f2[maxn][maxn], a[maxn][maxn], b[maxn][maxn];
int len, n, m, lsp[maxn];

LL qpow(LL a, LL b) {
	LL ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD, b >>= 1;  
	}
	return ret;
}

void fft_init() {
	m = n * 2, len = 1, NTT_g = 3, NTT_inv_g = qpow(NTT_g, MOD - 2);
	while (len <= m) len <<= 1;
	for (int i = 1; i < len; i++) lsp[i] = (lsp[i >> 1] >> 1) | ((i & 1) ? (len >> 1) : 0); 
}

void fft_calc(LL* f, int n, int flag) {
	for (int i = 0; i < n; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);
	for (int l = 2; l <= n; l <<= 1) {
		int lsl = (l >> 1);
		LL w1 = qpow((flag ? NTT_g : NTT_inv_g), (MOD - 1) / l);
		for (int st = 0; st < n; st += l) {
			LL buf = 1;
			for (int k = st; k < st + lsl; k++) {
				LL tmp = buf * f[k + lsl] % MOD;
				f[k + lsl] = (f[k] - tmp + MOD) % MOD;
				f[k] = (f[k] + tmp) % MOD;
				buf = buf * w1 % MOD; 
			}
		}
	}
	if (!flag) {
		LL inv_n = qpow(n, MOD - 2);
		for (int i = 0; i < n; i++) f[i] = f[i] * inv_n % MOD;
	}
//	for (int i = 0; i <= n; i++) printf("%lld ", f[i]);
//	putchar('\n'); 
}

int main() {
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) 
		for (int j = 0; j <= n; j++) 
			scanf("%lld", &a[i][j]);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++) 
			scanf("%lld", &b[i][j]);
	fft_init();
	
	for (int i = 0; i <= n; i++) fft_calc(a[i], len, 1), fft_calc(b[i], len, 1);
	for (int i = 0; i <= len; i++) 
		for (int j = 0; j <= len; j++) f1[j][i] = a[i][j], f2[j][i] = b[i][j];
	for (int i = 0; i <= len; i++) fft_calc(f1[i], len, 1), fft_calc(f2[i], len, 1);
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= len; j++) f1[i][j] = f1[i][j] * f2[i][j] % MOD;
		fft_calc(f1[i], len, 0);
		for (int j = 0; j <= len; j++) a[j][i] = f1[i][j]; 
	}
	for (int i = 0; i < len; i++) fft_calc(a[i], len, 0);
	
	for (int i = 0; i <= m; i++) {
		LL res = 0;
		for (int j = 0; j <= m; j++) res = res ^ a[i][j];
		printf("%lld ", res);
	}
	putchar('\n');
	for (int i = 0; i <= m; i++) {
		LL res = 0;
		for (int j = 0; j <= m; j++) res = res ^ a[j][i];
		printf("%lld ", res);
	}
	putchar('\n');
	return 0;
}
