#include <bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
using namespace std;
using pii = pair<int, int>;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m, c;
	cin >> n;
	vector<int> b(n);
	vector<pii> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
		a[i] = pii(b[i], i);
	}
	sort(a.begin(), a.end());
	vector<vector<int>> res;
	for (m = 0; n >> m; ++m);
	res.resize(m + 1);
	c = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (~c >> j & 1) {
				res[j].pb(a[i].fi);
			}
		}
		if (i + 1 < n && a[i].se > a[i + 1].se) {
			++c;
		}
	}
	for (m = 0; c >> m; ++m);
	cout << m << '\n';
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j) cout << ' ';
			cout << b[j];
		}
		cout << '\n';
		vector<char> vis(n + 1);
		for (int v : res[i]) {
			vis[v] = true;
		}
		vector<int> cur;
		for (int x : b) {
			if (vis[x]) {
				cur.pb(x);
			}
		}
		for (int x : b) {
			if (!vis[x]) {
				cur.pb(x);
			}
		}
		b.swap(cur);
	}
}