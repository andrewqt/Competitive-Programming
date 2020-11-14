#include <bits/stdc++.h>

using namespace std;

int N, M;
int par[100005];
int mxx[100005], mnx[100005], mxy[100005], mny[100005];

int getrt(int n){
    return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    if(fopen("fenceplan.in", "r")){
        freopen("fenceplan.in", "r", stdin);
        freopen("fenceplan.out", "w", stdout);
    }
    cin >> N >> M;
    for(int i = 1; i<=N; i++){
        int x, y;
        cin >> x >> y;
        par[i] = i;
        mxx[i] = mnx[i] = x;
        mxy[i] = mny[i] = y;
    }
    while(M--){
        int a, b;
        cin >> a >> b;
        a = getrt(a), b = getrt(b);
        if(a != b){
            par[a] = b;
            mxx[b] = max(mxx[a], mxx[b]);
            mxy[b] = max(mxy[a], mxy[b]);
            mnx[b] = min(mnx[a], mnx[b]);
            mny[b] = min(mny[a], mny[b]);
        }
    }
    long long ans = LLONG_MAX;
    for(int i =1 ; i<=N; i++){
        if(getrt(i) == i){
            ans = min(ans, 2LL*(mxx[i]-mnx[i]+mxy[i]-mny[i]));
        }
    }
    cout << ans << endl;
}
