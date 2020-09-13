#include <bits/stdc++.h>
#define LL long long
#define FOR(i,j,k) for (int i = (j); i <= (k); i++)
#define ADDM(a, b) ((a) = ((a) + (b)) % MOD)

using namespace std;

const int maxn = 535;
const LL MOD = 1e9 + 7;

int n;
LL k, inv[maxn], fac[maxn], ifac[maxn], f[maxn][maxn], pow1[maxn], pow2[maxn]; 

void init(int n) {
	fac[0] = ifac[0] = inv[1] = pow1[0] = pow2[0] = 1;
	FOR (i, 1, n) fac[i] = fac[i - 1] * i % MOD;
	FOR (i, 2, n) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	FOR (i, 1, n) ifac[i] = ifac[i - 1] * inv[i] % MOD;
	FOR (i, 1, n) pow1[i] = pow1[i - 1] * k % MOD, pow2[i] = pow2[i - 1] * (k - 1) % MOD;
}
LL qpow(LL a, LL b) {
	LL ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD, b >>= 1; 
	}
	return ret;
}
inline LL C(LL a, LL b) { 
	return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}

int main() {
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	scanf("%d%lld", &n, &k);
	init(n + 6);
	f[0][0] = 1;
	FOR (i, 1, n) FOR (j, 1, n) {
		FOR (j0, 0, j-1) {
			LL tmp = f[i-1][j0] * C(n-j0, j-j0) % MOD;
			tmp = tmp * pow2[n - j] % MOD * pow1[j0] % MOD;
			ADDM(f[i][j], tmp);
		}	
		ADDM(f[i][j], (pow1[j] - pow2[j] + MOD) % MOD * pow2[n-j] % MOD * f[i-1][j] % MOD);
	}
	printf("%lld\n", f[n][n]);
	return 0;
}
