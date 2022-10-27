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
 
vector<pair<int, int>> S;
pair<int, int> p[200006];
int ans[200006];
int n, m, l;
 
void UITShuriken() {
    cin >> n >> m >> l;
 
    for(int i = 1; i <= n; ++i) {
        int x, y; cin >> x >> y;
        if (l < y) continue;
        S.push_back(make_pair(x - (l - y), x + (l - y)));
    }
 
    sort(S.begin(), S.end());
    for(int i = 0; i < m; ++i) {
        cin >> p[i].first;
        p[i].second = i;
    }
 
    sort(p, p + m);
 
    priority_queue<int, vector<int>, greater<int>> PQ;
 
    for(int i = 0, curr = 0; i < m; ++i) {
        while (curr < (int) S.size() && p[i].first >= S[curr].first)
        PQ.push(S[curr++].second);
 
        while (!PQ.empty() && PQ.top() < p[i].first) PQ.pop();
 
        ans[p[i].second] = PQ.size();
    }
 
    for(int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
 
    init();
 
    int tests = 1; /// cin >> tests;
    while (tests--) UITShuriken();
 
    return 0;
}
