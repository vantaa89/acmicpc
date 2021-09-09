#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 300000;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    vector<pair<int, int> > gems(n);
    vector<int> bags(k);
    priority_queue<int> pq;

    for(int i = 0; i < n; ++i){
        scanf("%d %d", &gems[i].first, &gems[i].second);
    }
    for(int i = 0; i < k; ++i){
        scanf("%d", &bags[i]);
    }
    sort(bags.begin(), bags.end());
    sort(gems.begin(), gems.end());
    long long result = 0;
    int j = 0;
    for(int i = 0; i < k; ++i){
        for(; j < n && gems[j].first <= bags[i]; ++j){
            pq.push(gems[j].second);
        }
        if(!pq.empty()){
            result += pq.top();
            pq.pop();
        }
    }
    printf("%lld\n", result);
    return 0;
}
