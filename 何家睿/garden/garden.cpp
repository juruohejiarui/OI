#include <bits/stdc++.h>

using namespace std;

const int maxn = 150005, maxlogn = 18;
struct Query {
	int t, id;
	friend bool operator < (Query a, Query b) {
		return a.t < b.t;
	}
} q[maxn]; 
struct Edge {
	int v, w, nex;
	Edge(int v = 0, int w = 0, int nex = 0) : v(v), w(w), nex(nex) {}
} E[maxn << 1];

int hd[maxn], tote;
void addedge(int u, int v, int w) {
	E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
	E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
}

int mx_to[maxn], mx[maxn], smx_to[maxn], smx[maxn];
int ans[maxn], logn, f[maxlogn][maxn][2][2];
void update_to(int fr, int to, int w) {
	if (mx[fr] < w) {
		smx[fr] = mx[fr], smx_to[fr] = mx_to[fr];
		mx[fr] = w, mx_to[fr] = to;
	} else if (smx[fr] < w) {
		smx[fr] = w, smx_to[fr] = to;
	}
}

int walk(int u, int step) {
	int pos = u, k1 = 0, len = 0;
	for (int i = logn; i >= 0; i--) {
		if (len + (1 << i) > step) continue;
		len += (1 << i);
		if (f[i][pos][k1][0]) pos = f[i][pos][k1][0], k1 = 0;
		else pos = f[i][pos][k1][1], k1 = 1;
	}
	return pos;
} 
int main() {
	freopen("garden.in", "r", stdin);
	freopen("garden.out", "w", stdout);
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p), p++;
	for (int i = m; i >= 1; i--) {
		int u, v; scanf("%d%d", &u, &v), u++, v++;
		addedge(u, v, i);
		update_to(u, v, i), update_to(v, u, i);
	}
	for (int i = 1; i <= n; i++) if (!smx[i]) smx_to[i] = mx_to[i]; 
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= n; i++) scanf("%d", &q[i].t), q[i].id = i;
	sort(q + 1, q + 1 + T);
	for (int i = 1; i <= n; i++) {
		f[0][i][0][mx_to[mx_to[i]] == i] = mx_to[i];
		f[0][i][1][mx_to[smx_to[i]] == i] = smx_to[i];
	}
	logn = log2(q[T].t);
	for (int i = 0; i < logn; i++) {
		for (int u = 1; u <= n; u++)
			for (int k1 = 0; k1 <= 1; k1++)
				for (int k2 = 0; k2 <= 1; k2++) {
					if (!f[i][u][k1][k2]) continue;
					int t = f[i][u][k1][k2];
					f[i+1][u][k1][0] = f[i][f[i][u][k1][k2]][k2][0];
					f[i+1][u][k1][1] = f[i][f[i][u][k1][k2]][k2][1];
				}
	}
//	for (int i = 0; i <= logn; i++) {
//		for (int u = 1; u <= n; u++) {
//			printf("(%d %d %d %d) ", f[i][u][0][0], f[i][u][0][1], f[i][u][1][0], f[i][u][1][1]);
//		}
//		putchar('\n');
//	}
	for (int a = 1; a <= T; a++) {
		for (int i = 1; i <= n; i++) ans[q[a].id] += (walk(i, q[a].t) == p);
	}
	for (int i = 1; i <= T; i++) printf("%d ", ans[i]);
	return 0;
}
