#include <bits/stdc++.h>

using namespace std;

struct state{
    int x, y, v;
    bool operator < (const state& s) const{
        if(v == s.v && ((x < 0 && s.x > 0) || (x > 0 && s.x < 0))){
            return x<0 && s.x > 0;
        }
        if(v == s.v && x == s.x){
            return ((y < s.y)+1)%2;
        }
        else if(v == s.v){
            return ((x < s.x)+1)%2;
        }
        else{
            return ((v < s.v)+1)%2;
        }
    }
};

int N;
int BIT[600][600];
priority_queue<state> pq;

int query(int x, int y){
    int v = 0;
    for(int i =x; i>0; i-=i&-i){
        for(int j = y; j>0; j-=j&-j){
            v += BIT[i][j];
        }
    }
    return v;
}

void upd(int x, int y){
    for(int i = x; i<=500; i+=i&-i){
        for(int j = y; j<=500; j+=j&-j){
            BIT[i][j]++;
        }
    }
}

int main(){
    cin >> N;
    for(int i =1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            int v;
            cin >> v;
            pq.push({i,j,v});
        }
    }
    long long ans = 0;
    while(!pq.empty()){
        state s = pq.top();
        pq.pop();
        if(s.x > 0){
            int n = query(s.x-1, s.y-1);
            ans += (s.x-1)*(s.y-1)-n;
            pq.push({-s.x, -s.y, (s.x-1)*(s.y-1)-n+s.v});
        }
        else{
            upd(-s.x, -s.y);
        }
    }
    cout << ans << endl;
}
