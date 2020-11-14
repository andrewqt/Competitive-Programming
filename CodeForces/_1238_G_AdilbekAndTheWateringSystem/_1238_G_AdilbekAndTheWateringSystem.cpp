#include <bits/stdc++.h>

using namespace std;

struct event{
    long long lim, pos, cst;
    bool operator < (event e) const{
        return e.cst < cst;
    }
};

int Q, N, M, C, I;
priority_queue<event> pq;
vector<pair<int, event>> v;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> Q;
    while(Q--){
        cin >> N >> M >> C >> I;
        for(int i = 1; i<=N; i++){
            int t, a, b;
            cin >> t >> a >> b;
            v.push_back({t, {a, t, b}});
        }
        v.push_back({M, {0, 0, 0}});
        sort(v.begin(), v.end());
        int crnt = 0;
        pq.push({I, I-C, 0});
        long long ans = 0;
        for(auto p : v){
            int pos = p.first;
            while(pq.size() && crnt < pos){
                auto e = pq.top();
                pq.pop();
                if(e.pos+C <= crnt){ //might be wrong
                    continue;
                }
                int ed = min(e.pos+C-crnt, e.lim);
                if(ed+crnt > pos){
                    ed = pos-crnt;
                }
                crnt += ed;
                ans += 1LL*ed*e.cst;
                e.lim -= ed;
                if(e.lim && e.pos+C > crnt){
                    pq.push(e);
                }
            }
            pq.push(p.second);
            if(crnt < pos){
                ans = -1;
                break;
            }
        }
        cout << ans << "\n";
        v.clear();
        while(pq.size()){
            pq.pop();
        }
    }
}
