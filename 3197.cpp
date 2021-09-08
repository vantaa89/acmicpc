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

bool tick(disjointSet & ds){ // returns if the board is changed.
    bool changes[MAX_SIZE][MAX_SIZE] = {false, };
    bool ret = false;
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if(board[i][j] == 'X')
                continue;
            for(int d = 0; d < 4; ++d){
                int nx = i + dx[d], ny = j + dy[d];
                if(0 <= nx && nx < r && 0 <= ny && ny < c && board[nx][ny] == 'X'){
                    changes[nx][ny] = true;
                    ret = true;
                    ds.merge(ptoi(nx, ny), ptoi(i, j));
                }
            }
        }
    }
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            board[i][j] = changes[i][j]?'.':board[i][j];
            for(int d = 0; d < 4; ++d){
                int nx = i + dx[d], ny = j + dy[d];
                if(0 <= nx && nx < r && 0 <= ny && ny < c) {
                    if(changes[i][j] && changes[nx][ny]){
                        ds.merge(ptoi(i,j), ptoi(nx, ny));
                    }
                }
            }
        }
    }

    return ret;
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
        }

    }
    bfs(ds);

    bool flag = true;
    int cnt = 0;
    while(flag){
        flag = tick(ds);
        ++cnt;
        if(ds.find(swans[0]) == ds.find(swans[1])){
            break;
        }
    }
    printf("%d", cnt);
    return 0;
}