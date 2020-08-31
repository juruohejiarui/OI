#include "paint.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5, INF = 1e8;
int n, m, k, f[maxn], tr[maxn << 2];

#define selfmin(a, b) ((a) < (b) ? (a) : (b))
#define LS(o) o << 1
#define RS(o) o << 1 | 1
void ST_init(int o, int l, int r) {
  tr[o] = INF;
  if (l == r) return ;
  int mid = (l + r) >> 1;
  ST_init(LS(o), l, mid), ST_init(RS(o), mid+1, r);
}
void ST_update(int o, int l, int r, int p, int val) {
  if (l == r) {
    tr[o] = selfmin(tr[o], val);
    return ;
  }
  int mid = (l + r) >> 1;
  if (p <= mid) ST_update(LS(o), l, mid, p, val);
  else ST_update(RS(o), mid + 1, r, p, val);
  tr[o] = selfmin(tr[LS(o)], tr[RS(o)]);
}
int ST_query(int o, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) return tr[o];
  int mid = (l + r) >> 1;
  if (qr <= mid) return ST_query(LS(o), l, mid, ql, qr);
  else if (ql > mid) return ST_query(RS(o), mid+1, r, ql, qr);
  else return selfmin(ST_query(LS(o), l, mid, ql, qr), ST_query(RS(o), mid+1, r, ql, qr));
}

vector<int> id[maxn];
vector<int> c, a;
vector< vector<int> > b;

int count_val(int id, int val) {
	int l = 1, r = a[id];
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (b[id][mid - 1] == val) return 1;
		if (b[id][mid - 1] < val) l = mid + 1;
		else r = mid - 1;
	}
	return 0;
}

bool isok(int pos, int col) {
	bool ret = false;
	for (int i = 0; i < id[col].size(); i++) {
		int x = id[col][i]; bool succ = true;
		for (int j = 1; j <= m; j++) {
			if (!count_val((j + x) % m, (c[pos + j - 1]))) {
				succ = false;
				break;
			}
		}
		if (succ) { ret = true; break; }
	}
	return ret;
}
int minimumInstructions(
    int N, int M, int K, std::vector<int> C,
    std::vector<int> A, std::vector< std::vector<int> > B) {
  n = N, m = M, k = K, c = C, a = A, b = B;

  for (int i = 0; i < M; i++) {
	for (int j = 0; j < a[i]; j++) {
		id[b[i][j]].push_back(i);
	}
	sort(b[i].begin(), b[i].end());
  }
  ST_init(1, 1, N + 1);
  ST_update(1, 1, N + 1, 1, 0);
  for (int i = 1; i <= N; i++) f[i] = INF;
  for (int i = M; i <= N; i++) {
    if (!isok(i - M, c[i - 1])) continue;
    f[i] = ST_query(1, 1, N + 1, i - M + 1, i) + 1;
    if (f[i] >= INF) f[i] = INF;
    ST_update(1, 1, N + 1, i + 1, f[i]);
  }
  int ans = 0;
  if (f[n] >= INF) ans = -1;
  else ans = f[n];
  return ans;
}