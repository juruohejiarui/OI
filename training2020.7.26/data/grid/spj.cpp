#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	registerLemonChecker(argc, argv);
	int n = inf.readInt(), m = inf.readInt();
	vector<vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) a[i][j] = inf.readInt();
	int yours = ouf.readInt(), standard = ans.readInt();
	ensure((yours == -1) == (standard == -1));
	for (int t = 1; t <= yours; ++t) {
		int op = ouf.readInt(1, 2);
		if (op == 1) {
			int row = ouf.readInt(0, n - 1);
			int dis = ouf.readInt(0, m);
			vector<int> g(m);
			for (int i = 0; i < m; ++i) g[(i + dis) % m] = a[row][i];
			for (int i = 0; i < m; ++i) a[row][i] = g[i];
		} else {
			int col = ouf.readInt(0, m - 1);
			int dis = ouf.readInt(0, n);
			vector<int> g(n);
			for (int i = 0; i < n; ++i) g[(i + dis) % n] = a[i][col];
			for (int i = 0; i < n; ++i) a[i][col] = g[i];
		}
	}
	if (standard != -1) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (a[i][j] != i * m + j) quitf(_wa, "wrong answer");
	}
	quitf(_ok, "accepted");
}
