#include <bits/stdc++.h>
#define LL long long 

using namespace std;

const int maxn = 1e6 + 6, maxlogn = 20;
const LL MOD = 998244353;
int logn, n, m, to[maxlogn][maxn];
LL f1[maxlogn][maxn], f2[maxlogn][maxn], a[maxn];

struct STNode {
	int lz, val;
} nd[maxn << 2]; 

#define LS(o) o << 1
#define RS(o) o << 1 | 1
void ST_pushdown(int o) {
	if (!nd[o].lz) return ;
	nd[LS(o)].lz = nd[RS(o)].lz = nd[o].lz;
	nd[LS(o)].val = nd[RS(o)].val = nd[o].lz;
	nd[o].lz = 0;
}
int ST_query(int o, int l, int r, int p) {
	if (l == r) return nd[o].val;
	ST_pushdown(o);
	int mid = (l + r) >> 1;
	if (p <= mid) return ST_query(LS(o), l, mid, p);
	else return ST_query(RS(o), mid + 1, r, p);
}
void ST_update(int o, int l, int r, int ql, int qr, int val) {
	if (ql > r || qr < l) return ;
	if (ql <= l && r <= qr) {
		nd[o].val = nd[o].lz = val;
		return ;
	}
	ST_pushdown(o);
	int mid = (l + r) >> 1;
	ST_update(LS(o), l, mid, ql, qr, val), ST_update(RS(o), mid+1, r, ql, qr, val);
}
inline LL ls_sum(int l, int r) {
	return (r - l + 1) * (l + r) / 2;
}
int solve(int l, int r) {
	LL sum1 = 0, sum2 = 0;
	int pos = l;
	for (int i = logn; i >= 0; i--) {
		if (to[i][pos] > r || !to[i][pos]) continue;
		sum1 += f1[i][pos], sum2 += f2[i][pos];
		pos = to[i][pos];
	}
	return (sum2 + a[pos] * ls_sum(pos, r)) - (sum1 + a[pos] * (r - pos + 1)) * (l - 1);  
}

int baoli_solve(int l, int r) {
	LL sum = 0, maxa = 0;
	for (int R = l; R <= r; R++) {
		maxa = max(maxa, a[R]);
		sum += maxa * (R - l + 1);
	}
	return sum;
}
int main() {
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
//	printf("%.6lf\n", (double)(sizeof(a)sizeof(nd) + sizeof(f1) + sizeof(f2)  + sizeof(to)) / 1024 / 1024);
	LL seed1, seed2, d, p, a_sz = 0;
	scanf("%d%d%I64d%I64d%I64d%I64d", &n, &m, &seed1, &seed2, &d, &p);
	for (int i = 1; i <= n; i++) scanf("%I64d", &a[i]), a_sz = max(a_sz, a[i]);
	for (int i = n; i >= 1; i--) {
		int val = ST_query(1, 1, a_sz, a[i]);
		to[0][i] = (val ? val : n + 1);
		f1[0][i] = a[i] * (to[0][i] - i);
		if (to[0][i])
			f2[0][i] = a[i] * ls_sum(i, to[0][i] - 1);
		else f2[0][i] = a[i] * ls_sum(i, n);
		ST_update(1, 1, a_sz, 1, a[i], i);
	}
	logn = log2(n);
	for (int i = 1; i <= logn; i++) {
		for (int j = 1; j <= n; j++) {
			int t = to[i-1][j];
			to[i][j] = to[i-1][to[i-1][j]];
			f1[i][j] = f1[i-1][j] + f1[i-1][t];
			f2[i][j] = f2[i-1][j] + f2[i-1][t];
		}
	}
//	for (int i = 0; i <= logn; i++) {
//		for (int j = 1; j <= n; j++)
//			printf("%d %lld %lld\t", to[i][j], f1[i][j], f2[i][j]);
//		putchar('\n');
//	}
	LL ans = 0, lastans = 0;
	for (int i = 1; i <= m; i++) {
		int l = min((seed1 % MOD + p * lastans) % n + 1, (seed2 % MOD + p * lastans) % n + 1);
		int r = max((seed1 % MOD + p * lastans) % n + 1, (seed2 % MOD + p * lastans) % n + 1);
		lastans = solve(l, r);
//		printf("(%d,%d)->%lld %lld\n", l, r, lastans, baoli_solve(l, r));
		ans ^= lastans, seed1 = seed1 * d % MOD, seed2 = seed2 * d % MOD;
	}
	printf("%lld\n", ans);
	return 0;
} 
