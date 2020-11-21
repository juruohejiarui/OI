#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5;
struct Edge {
    int v, w, nex;
    Edge(int v=0, int w=0, int nex=0) : v(v), w(w), nex(nex) {}
};
struct Graph {
    int hd[maxn], chkt[maxn], tote, ti;
    Edge E[maxn << 1];
    void destroy() { tote = 0, ti++; }
    void addedge(int u, int v, int w=0) {
        E[++tote] = Edge(v, w, hd[u]);
        E[++tote] = Edge(u, w, hd[v]);
    }
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    return 0;
}