#include <bits/stdc++.h>

using namespace std;

struct obj{
    int n, frm, cst;
    bool operator < (obj o) const{
        if(frm == o.frm){
            return cst < o.cst;
        }
        return frm > o.frm;
    }
};

int N, M;
long long dp[100005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i= 1; i<=N; i++){
        int c, f, p;
        cin >> c >> f >> p;
        item[i] = {c, f, -p};
    }
    cin >> M;
    for(int i = 1; i<=M; i++){
        int c, f, p;
        cin >> c >> f >> p;
        buyer[i] = {c, -f, p};
    }
    sort(item+1, item+1+N);
    sort(buyer+1, buyer+1+M);

}
