#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5;
const LL INF = 1e18;

int n; LL a[maxn], ANS = 0;

struct TreeNode {
	int ls, rs;
	LL val, cnt, sum;
} nd[maxn << 2];
#define LS(o) (nd[o].ls)
#define RS(o) (nd[o].rs)

LL bsval[maxn], bscnt[maxn], bs[maxn];
int bs_cnt, nd_cnt, TROOT;

void init(int& o, int l, int r) {
	if (l > r) { o = 0; return ; }
	o = ++nd_cnt;
	int mid = (l + r) >> 1;
	init(nd[o].ls, l, mid - 1), init(nd[o].rs, mid + 1, r);
	nd[o].val = bsval[mid], nd[o].cnt = bscnt[mid];
	nd[o].sum = nd[LS(o)].sum + nd[RS(o)].sum + nd[o].cnt;
}

void clear(int o) {
	if (!o) return ;
	clear(LS(o)), clear(RS(o));
	LS(o) = RS(o) = 0;
}

void change(LL p, LL val) {
	int u = TROOT;
	while (u) {
		nd[u].sum += val;
		if (nd[u].val == p) {
			nd[u].cnt += val;
			break;
		}
		if (nd[u].val < p) u = RS(u);
		else u = LS(u); 
	}
}

LL query(LL p) {
	LL ret = 0, u = TROOT;
	while (u) {
		if (nd[u].val >= p) ret += nd[u].cnt + nd[RS(u)].sum, u = LS(u);
		else u = RS(u); 
	}
	return ret;
} 

void self_unique() {
	sort(bs + 1, bs + 1 + bs_cnt);
	int len = 0;
	for (int i = 1; i <= bs_cnt; i++) {
		int pos = i + 1;
		while (pos <= bs_cnt && bs[i] == bs[pos]) pos++;
		bsval[++len] = bs[i], bscnt[len] = pos - i;
		i = pos - 1;
	}
	bs_cnt = len;
}

struct Edge {
	int v, nex; LL w;
	Edge(int v = 0, LL w = 0, int nex = 0) 
		: v(v), w(w), nex(nex) {}
} E[maxn << 1];

int hd[maxn], tote;
void addedge(int u, int v, LL w) {
	E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
	E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
}  

int SST_ROOT, MAX_SST_SIZE, ST_SIZE, ST_ROOT, vis[maxn], sz[maxn];

void get_SST_ROOT(int u, int fa) {
	int max_sst_size = ST_SIZE - sz[u];
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (v == fa || vis[v]) continue;
		get_SST_ROOT(v, u);
		max_sst_size = max(max_sst_size, sz[v]);
	}
	if (SST_ROOT == -1 || MAX_SST_SIZE > max_sst_size) 
		SST_ROOT = u, MAX_SST_SIZE = max_sst_size;
} 

void calc_bs(int u, int fa, LL mn, LL dis, LL sa) {
	sa += a[u];
	mn = min(mn, dis - sa);
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (v == fa || vis[v]) continue;
		calc_bs(v, u, mn, dis + E[i].w, sa);
		if (a[v] >= E[i].w && a[v] + sa - E[i].w - dis + mn >= 0)
			bs[++bs_cnt] = a[v] + sa - E[i].w - dis;
	}
}

void change_sst(int u, int fa, LL mn, LL dis, LL sa, LL fl) {
	sa += a[u];
	mn = min(mn, dis - sa);
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (v == fa || vis[v]) continue;
		change_sst(v, u, mn, dis + E[i].w, sa, fl);
		if (a[v] >= E[i].v && a[v] + sa - E[i].w - dis + mn >= 0)
			change(a[v] + sa - E[i].w - dis, fl); 
	}
}

void calc_ans(int u, int fa, LL mx, LL dis, LL sa) {
	mx = max(mx, dis - sa), sa += a[u], sz[u] = 1;
	ANS += query(mx - a[ST_ROOT]);
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (v == fa || vis[v]) continue;
		calc_ans(v, u, mx, dis + E[i].w, sa), sz[u] += sz[v];
	}
}

void divide(int u) {
	bs[bs_cnt = 1] = 0, nd_cnt = 0, vis[u] = 1;
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (vis[v]) continue;
		calc_bs(v, u, 0, E[i].w, 0);
		if (E[i].w <= a[v]) bs[++bs_cnt] = a[v] - E[i].w; 
	}
	ANS += bs_cnt - 1;
	self_unique();
	init(TROOT, 1, bs_cnt);
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (vis[v]) continue;
		change_sst(v, u, 0, E[i].w, 0, -1);
		if (E[i].w <= a[v]) change(a[v] - E[i].w, -1);
		calc_ans(v, u, E[i].w, E[i].w, 0);
		change_sst(v, u, 0, E[i].w, 0, 1);
		if (E[i].w <= a[v]) change(a[v] - E[i].w, 1);
	}
	clear(TROOT);
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (vis[v]) continue;
		ST_SIZE = sz[v], SST_ROOT = -1;
		get_SST_ROOT(v, -1);
		ST_ROOT = SST_ROOT;
		divide(ST_ROOT);
	}
}

void calc_sz(int u, int fa) {
	sz[u] = 1;
	for (int i = hd[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (v == fa) continue;
		calc_sz(v, u), sz[u] += sz[v];
	}
}

int main() {
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i < n; i++) {
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		addedge(u, v, w);
	}
	ST_SIZE = n, SST_ROOT = -1;
	calc_sz(1, 0), get_SST_ROOT(1, 0);
	divide(SST_ROOT);
	cout << ANS << endl;
	return 0;
}