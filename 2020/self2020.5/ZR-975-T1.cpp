#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <set>
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

using namespace std;

const int maxn = 5e5 + 5;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    friend bool operator < (Point a, Point b) {
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }
    friend bool operator == (Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator > (Point a, Point b) {
        return (a.x == b.x ? a.y > b.y : a.x > b.x);
    }
};
struct Edge {
    Point a, b;
    Edge() {}
    Edge(Point _a, Point _b) { 
        a = _a, b = _b;
        if (a > b) swap(a, b);
    }
    friend bool operator < (Edge a, Edge b) {
        return (a.a == b.a ? a.b < b.b : a.a < b.a);
    }
    friend bool operator == (Edge a, Edge b) {
        return a.a == b.a && a.b == b.b;
    }
};

int n, pos_cnt;
char oper[maxn];
set<Point> point_set;
set<Edge> edge_set;

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%s", oper + 1);
    n = strlen(oper + 1);
    Point p = Point(0,0);
    point_set.insert(p);
    for (int i = 1; i <= n; i++) {
        Point new_p = p;
        if (oper[i] == 'U') new_p.x++;
        else if (oper[i] == 'D') new_p.x--;
        else if (oper[i] == 'L') new_p.y--;
        else if (oper[i] == 'R') new_p.y++;
        Edge e = Edge(new_p, p);
        if (!point_set.count(new_p)) point_set.insert(new_p);
        if (!edge_set.count(e)) edge_set.insert(e);
        p = new_p;
        // printf("%d %d\n", p.x, p.y);
    }
    // printf("%lu %lu\n", point_set.size(), edge_set.size());
    printf("%lu\n", edge_set.size() - point_set.size() + 2);
    return 0;
}