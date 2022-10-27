#include <bits/stdc++.h>
using namespace std;
int n,m,p[105][10],d[105],res;
bool a[105];
vector <int> e[105];
int LCA(int u, int v){
    for (int i=log2(n); i>=0; i--){
        if (d[p[u][i]]>=d[v]){
            u=p[u][i];
        }
    }
    for (int i=log2(n); i>=0; i--){
        if (d[p[v][i]]>=d[u]){
            v=p[v][i];
        }
    }
    for (int i=log2(n); i>=0; i--){
        if (p[u][i]!=p[v][i]){
            u=p[u][i]; v=p[v][i];
        }
    }
    while(u!=v){
        u=p[u][0];
        v=p[v][0];
    }
    return u;
}
void DFS(int u, int pa){
    for (int i=0; i<e[u].size(); i++){
        int v=e[u][i];
        if (v!=pa){
            d[v]=d[u]+1;
            p[v][0]=u;
            DFS(v,u);
        }
    }
}
int dist(int u, int v){
    int k=LCA(u,v);
    return d[u]+d[v]-2*d[k];
}
int main(){
    /*freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);*/
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m; res=n;
    for (int i=1; i<=n; i++) cin>>a[i];
    int u,v;
    for (int i=1; i<n; i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    if (m==1){
        cout<<0; return 0;
    }
    p[1][0]=1; d[1]=0;
    DFS(1,-1);
    for (int j=1; j<=log2(n); j++){
        for (int i=1; i<=n; i++){
            p[i][j]=p[p[i][j-1]][j-1];
        }
    }
    for (int i=1; i<n; i++){
        if (a[i]==0) continue;
        for (int j=i+1; j<=n; j++){
            if (a[j]==0) continue;
            int kc=dist(i,j);
            int cnt=0;
            for (int k=1; k<=n; k++){
                if (a[k]==0) continue;
                int kc2=max(dist(k,i),dist(k,j));
                if (kc2<=kc) cnt++;
            }
            if (cnt>=m){
                res=min(res,kc);
            }
        }
    }
    cout<<res;
}
