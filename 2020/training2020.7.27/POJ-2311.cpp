#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 205;

int sg[maxn][maxn], fl[maxn * maxn], mxfl;
inline void insert_fl(int flag) {
    fl[flag] = true, mxfl = max(mxfl, flag); 
}
int mex() {
    int ret = 0;
    for (int i = 0; i <= mxfl + 1; i++) {
        if (!fl[i]) { ret = i; break; }
        fl[i] = false;
    }
    for (int i = ret + 1; i <= mxfl; i++)
        fl[i] = false;
    mxfl = 0;
    return ret;
}

void init_sg() {
    for (int i = 2; i < maxn; i++) {
        for (int j = 2; j < maxn; j++) {
            for (int k = 2; k < i-1; k++)
                insert_fl(sg[k][j] ^ sg[i - k][j]);
            for (int k = 2; k < j-1; k++)
                insert_fl(sg[i][k] ^ sg[i][j - k]);
            sg[i][j] = mex();
            // printf("%d ", sg[i][j]);
        }
        // printf("\n");
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    init_sg();
    int n, m; 
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n < m) swap(n, m);
        if (!sg[n][m]) printf("LOSE\n");
        else printf("WIN\n");
    }
    return 0;
}