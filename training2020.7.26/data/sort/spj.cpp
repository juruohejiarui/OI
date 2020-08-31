#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	registerLemonChecker(argc, argv);
	int n = inf.readInt();
	vector<int> a(n), b(n);
	assert(1 <= n && n <= 3000);
	for (int i = 0; i < n; ++i) a[i] = inf.readInt();
	int m = ouf.readInt();
	int e = ans.readInt();
	if (m != e) quitf(_wa, "wrong answer");
	bool failed = false;
	for (int i = 0; i < n; ++i) {
		b[i] = ouf.readInt();
		if (a[i] != b[i]) failed = true;
	}
	for (int i = 1; i <= m; ++i) {
		vector<int> pos(n + 1);
		for (int j = 0; j < n; ++j) b[j] = ouf.readInt(1, n), pos[a[j]] = j;
		a = b;
		for (int j = 0; j < n; ++j) b[j] = pos[b[j]];
		int cnt = 0;
		for (int j = 0; j + 1 < n; ++j) if (b[j] > b[j + 1]) ++cnt;
		if (cnt > 1) failed = true;
		sort(b.begin(), b.end());
		for (int j = 0; j < n; ++j) if (b[j] != j) failed = true;
	}
	if (failed) quitp(2.0, "partial correct");
	else quitf(_ok, "accept");
}
