#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_SIZE 1500

int r, c;
char board[MAX_SIZE][MAX_SIZE];
char tmp;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
queue<pair<int, int> > water;

inline int ptoi(int x, int y){ // converts pair to an index
    return x * c + y;
}
inline pair<int, int> itop(int p){
    return make_pair(p/c, p%c);
}

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

void bfs(disjointSet & ds){
    queue<pair<int, int> > q;
    bool visited[MAX_SIZE][MAX_SIZE] = {false,};

    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if(visited[i][j] || board[i][j] == 'X')
                continue;
            q.push(make_pair(i, j));
            visited[i][j] = true;
            while(!q.empty()){
                int cx = q.front().first;
                int cy = q.front().second;
                q.pop();
                for(int d = 0; d < 4; ++d){
                    int nx = cx + dx[d], ny = cy + dy[d];
                    if(0 <= nx && nx < r && 0 <= ny && ny < c && !visited[nx][ny] && board[nx][ny] != 'X'){
                        visited[nx][ny] = true;
                        ds.merge(ptoi(cx, cy), ptoi(nx, ny));
                        q.push(make_pair(nx, ny));
                    }
                }
            }
        }
    }
}

void tick(disjointSet &ds) { // returns if the board is changed.
    queue<pair<int, int> > newWater;
    while(!water.empty()){
        int i = water.front().first, j = water.front().second;
        water.pop();
        for(int d = 0; d < 4; ++d) {
            int nx = i + dx[d], ny = j + dy[d];
            if (0 <= nx && nx < r && 0 <= ny && ny < c && board[nx][ny] == 'X') {
                newWater.push(make_pair(nx, ny));
                board[nx][ny] = '.';
                ds.merge(ptoi(nx, ny), ptoi(i, j));

                for(int d2 = 0; d2 < 4; ++d2){
                    int mx = nx + dx[d2], my = ny + dy[d2];
                    if (0 <= mx && mx < r && 0 <= my && my < c && board[mx][my] != 'X'){
                        ds.merge(ptoi(nx, ny), ptoi(mx, my));
                    }
                }
            }
        }
    }


    water = newWater;
}

int main(){
    scanf("%d %d", &r, &c);
    disjointSet ds(r*c);
    vector<int> swans;
    for(int i = 0; i < r; ++i){
        scanf("\n");
        for(int j = 0; j < c; ++j){
            scanf("%c", &board[i][j]);
            if(board[i][j] == 'L'){
                swans.push_back(ptoi(i, j));
            }
            if(board[i][j] != 'X'){
                water.push(make_pair(i, j));
            }
        }
    }
    bfs(ds);

    bool flag = true;
    int cnt = 0;

    while(flag){
        tick(ds);
        ++cnt;
        if(ds.find(swans[0]) == ds.find(swans[1])){
            break;
        }
    }
    printf("%d", cnt);
    return 0;
}