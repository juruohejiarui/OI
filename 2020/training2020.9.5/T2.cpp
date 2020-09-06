#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 3e5 + 5;

int n, id[maxn];
string str[maxn], ans[maxn];

bool cmp(int a, int b) {
    string& s1 = str[a], &s2 = str[b];
    // cout << "compare " << s1 << " " << s2 << endl;
    int p1 = 0, p2 = 0, t = 0;
    while (s1[p1] == s2[p2] && t <= 15) 
        p1 = (p1 + 1) % s1.size(), p2 = (p2 + 1) % s2.size(),
        t++;
    // cout << p1 << " " << p2 << endl;
    return s1[p1] < s2[p2];
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) cin >> str[i], id[i] = i;
    sort(id + 1, id + 1 + n, cmp);
    for (int i = 1; i <= n; i++) ans[i] = str[id[i]];
    for (int i = 1; i <= n; i++) cout << ans[i];
    return 0;
}