#include <iostream>
#include <vector>

using namespace std;


struct disjointSet{
    vector<int> rank, parent;
    disjointSet(int n): rank(n, 1), parent(n) {
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u_, int v_){
        int u = find(u_), v = find(v_);
        if(u == v) return;
        if(rank[u] < rank[v])
            swap(u, v); // rank[u] >= rank[v]
        parent[v] = u;
        if(rank[u] == rank[v]){
            ++rank[u];
        }
    }

};

#define MAX_N 200
bool adj[MAX_N][MAX_N];


int main(){
    int n, m;
    int tmp;
    scanf("%d\n%d", &n, &m);
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &tmp);
            adj[i][j] = (bool)tmp;
        }
    }
    vector<int> plan(m);
    for(int i = 0; i < m; ++i){
        scanf("%d", &tmp);
        plan[i] = tmp - 1;
    }
    disjointSet ds(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(adj[i][j]){
                ds.merge(i, j);
            }
        }
    }
    int dSet = ds.find(plan[0]);
    bool possible = true;
    for(int i = 1; i < m; ++i){
        if(ds.find(plan[i]) != dSet) possible = false;
    }
    printf(possible?"YES":"NO");
    return 0;
}