#include "swap.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 5;
struct Edge {
    int v, w, nex;
    Edge(int v = 0, int w = 0, int nex = 0) : v(v), w(w), nex(nex) {}
} E[maxn << 1];
int hd[maxn], tote;
void addedge(int u, int v, int w) {
    E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
}

int mindeg, maxw, deg[maxn], w[maxn], wls[maxn], t1 = 1, t2 = 1;
bool cmp(int a, int b) { return a < b; }
void init(int N, int M,
          std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    for (int i = 1; i <= M; i++) {
        addedge(U[i-1], V[i-1], W[i-1]);
        deg[U[i-1]]++, deg[V[i-1]]++;
        if (deg[U[i-1]] > 2 || deg[V[i-1]] > 2) t1 = 0;
        if (U[i-1] != 0) t2 = 0;
    }
    if (t1) {
        mindeg = 10;
        for (int i = 0; i < N; i++) mindeg = min(mindeg, deg[i]);
        for (int i = 0; i < M; i++) maxw = max(maxw, W[i]);
    }
    if (t2) {
        for (int i = 0; i < M; i++) w[V[i]] = wls[i] = W[i];
        sort(wls, wls + M, cmp);
    }
}

int getMinimumFuelCapacity(int X, int Y) {
    if (t1 == 1) { 
        return mindeg < 2 ? -1 : maxw;
    }
    else if (t2 == 1) {
        if (!X) {
            int ans = w[Y];
            ans = max(ans, wls[1]);
            return ans;
        }
        else {
            int ans = max(w[X], w[Y]);
            ans = max(ans, wls[2]);
            return ans;
        }
    } else return -1;
    return 0;
}
