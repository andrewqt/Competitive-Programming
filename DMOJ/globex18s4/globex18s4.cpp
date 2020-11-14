#include <bits/stdc++.h>

using namespace std;

struct state{
    int s, v, msk;
};

int N, M, A, B, V;
vector<int> graph[20];
int dp[20][1<<19];
deque<state> ll;

int main(){
    cin >> N >> M >> A >> B >> V;
    int best = 100;
    for(int i = 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dp[0][1<<A] = 1<<A;
    ll.push_back({A, 0, 1<<A});
    while(!ll.empty()){
        state s = ll.front();
        ll.pop_front();
        if(s.s == B){
            best = abs(best-V) > abs(s.v-V) || (abs(best-V) == abs(s.v-V) && s.v < best)
                ? s.v : best;
        }
        for(auto e : graph[s.s]){
            if(!((1<<e) & s.msk) && !(dp[s.v+1][(1<<e)|s.msk] & (1<<e))){
                dp[s.v+1][(1<<e)|s.msk] |= (1<<e);
                ll.push_back({e, s.v+1, s.msk|(1<<e)});
            }
        }
    }
    cout << best << endl;
}
