/// hhoangcpascal
 
#pragma GCC target("avx,avx2,fma,popcnt")
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <deque>
#include <tuple>
#include <queue>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <assert.h>
#include <complex>
#include <random>
#include <chrono>
#include <functional>
#define sint short int
#define usint unsigned short int
#define uint unsigned int
#define llong long long
#define ullong unsigned long long
#define ldouble long double
 
using namespace std;
using namespace chrono;
 
void init() {
    ///
}
 
struct Data_update {
    int id, x, y, u, v;
} D[100006];
 
vector<int> nodes[2][300006];
vector<int> bit[2][300006];
int sz[2], sorted[2][300006];
 
void fake_update(int id, int x, int y) {
    for(; x <= sz[id]; x += (x & (-x))) nodes[id][x].push_back(y);
}
 
void fake_query(int id, int x, int y) {
    for(; x > 0; x -= (x & (-x))) nodes[id][x].push_back(y);
}
 
void update(int id, int x, int y, int val) {
    for(; x <= sz[id]; x += (x & (-x))) {
        int p = upper_bound(nodes[id][x].begin(), nodes[id][x].end(), y) - nodes[id][x].begin();
        for(; p < (int) nodes[id][x].size(); p += (p & (-p))) bit[id][x][p] += val;
    }
}
 
int query(int id, int x, int y) {
    int tot = 0;
    for(; x > 0; x -= (x & (-x))) {
        int p = upper_bound(nodes[id][x].begin(), nodes[id][x].end(), y) - nodes[id][x].begin();
        for(; p > 0; p -= (p & (-p))) tot += bit[id][x][p];
    }
    return tot;
}
 
void UITShuriken() {
    int n; cin >> n;
 
    for(int i = 1; i <= n; ++i) {
        int t; cin >> t;
 
        if (t == 1) {
            int x, y; cin >> x >> y;
            sorted[0][++sz[0]] = x;
            sorted[1][++sz[1]] = x;
            D[i] = {0, x, y, -1, -1};
        } else {
            int x, y, u, v; cin >> x >> y >> u >> v;
            sorted[0][++sz[0]] = x - 1;
            sorted[0][++sz[0]] = u;
            sorted[1][++sz[1]] = x;
            sorted[1][++sz[1]] = u + 1;
            D[i] = {1, x, y, u, v};
        }
    }
 
    for(int i = 0; i < 2; ++i) {
        sort(sorted[i] + 1, sorted[i] + sz[i] + 1);
        sz[i] = unique(sorted[i] + 1, sorted[i] + sz[i] + 1) - sorted[i] - 1;
    }
 
    for(int i = 1; i <= n; ++i) {
        auto [t, x, y, u, v] = D[i];
 
        if (t == 0) {
            int x1 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, x) - sorted[0];
            fake_update(0, x1, y);
            int x2 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, x) - sorted[1];
            fake_query(1, x2, y);
        } else {
            int x1 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, x - 1) - sorted[0];
            int u1 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, u) - sorted[0];
            fake_query(0, x1, y - 1);
            fake_query(0, x1, v);
            fake_query(0, u1, y - 1);
            fake_query(0, u1, v);
 
            int x2 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, x) - sorted[1];
            int u2 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, u + 1) - sorted[1];
 
            fake_update(1, x2, y);
            fake_update(1, x2, v + 1);
            fake_update(1, u2, y);
            fake_update(1, u2, v + 1);
        }
    }
 
    for(int i = 0; i < 2; ++i) {
        for(int j = 1; j <= sz[i]; ++j) {
            auto &v = nodes[i][j];
            v.push_back((int) 2e9);
 
            sort(v.begin(), v.end());
            v.resize(unique(v.begin(), v.end()) - v.begin());
            bit[i][j].assign(v.size(), 0);
        }
    }
 
    llong ans = 0;
    for(int i = 1; i <= n; ++i) {
        auto [t, x, y, u, v] = D[i];
 
        if (t == 0) {
            int x1 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, x) - sorted[1];
            ans += query(1, x1, y);
            int x2 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, x) - sorted[0];
            update(0, x2, y, 1);
        } else {
            int x1 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, x - 1) - sorted[0];
            int u1 = lower_bound(sorted[0] + 1, sorted[0] + sz[0] + 1, u) - sorted[0];
            ans += query(0, x1, y - 1);
            ans -= query(0, x1, v);
            ans -= query(0, u1, y - 1);
            ans += query(0, u1, v);
 
            int x2 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, x) - sorted[1];
            int u2 = lower_bound(sorted[1] + 1, sorted[1] + sz[1] + 1, u + 1) - sorted[1];
 
            update(1, x2, y, 1);
            update(1, x2, v + 1, -1);
            update(1, u2, y, -1);
            update(1, u2, v + 1, 1);
        }
 
        cout << ans << '\n';
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
 
    init();
 
    int tests = 1; /// cin >> tests;
    while (tests--) UITShuriken();
 
    return 0;
}
