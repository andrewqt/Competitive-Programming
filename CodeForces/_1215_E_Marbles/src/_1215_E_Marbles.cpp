#include <bits/stdc++.h>

using namespace std;

int N;
vector<long long> pos[20], pre[20];
long long num[1<<20], dp[1<<20];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int k = 0; k<20; k++){
        pos[k].push_back(0);
        pre[k].push_back(0);
    }
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        n--;
        int idx = i-pos[n].size()+1;
        pos[n].push_back(idx);
        pre[n].push_back(pre[n].back()+idx);
    }
    for(int m = 1; m<1<<20; m++){
        dp[m] = INT_MAX;
        for(int k = 0; k<20; k++){
            if((1<<k)&m){
                num[m] += pos[k].size()-1;
            }
        }
        for(int k = 0; k<20; k++){
            if((1<<k)&m){
                int t = (1<<k)^m;
                long long c = num[t]+1;
                int l = 1, r = pre[k].size()-1, idx = 0;
                while(l <= r){
                    int mid = l+r>>1;
                    if(pos[k][mid] <= c){
                        idx = mid;
                        l = mid+1;
                    }
                    else{
                        r= mid-1;
                    }
                }
                dp[m] = min(dp[m], dp[t] + pre[k].back() - pre[k][idx] - (pre[k].size()-idx-1)*(c));
                if(__builtin_popcount(m) == 1){
                    cout << dp[m] << endl;
                }
            }
        }
    }
    cout << dp[(1<<20)-1] << endl;
}
