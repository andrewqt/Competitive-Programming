#include <bits/stdc++.h>

using namespace std;

int N, K;
long long pre[100005];
long long dp[100005][25];
int par[100005][25];
deque<int>dq;
vector<int> v;

double f(int idx1, int idx2, int lvl){
    return 1.0*(dp[idx1][lvl]-dp[idx2][lvl]-pre[idx1]*pre[idx1]+pre[idx2]*pre[idx2])/(pre[idx2]-pre[idx1]);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        cin >> pre[i];
        if(pre[i]){
            v.push_back(i);
        }
        pre[i] += pre[i-1];
    }
    for(int k = 1; k<=K; k++){
        dq.push_back(k);
        for(int i = k+1; i<=N; i++){
            while(dq.size() >= 2){
                if(f(dq[0], dq[1], k-1) < pre[i]){
                    dq.pop_front();
                }
                else{
                    break;
                }
            }
            dp[i][k] = dp[dq.front()][k-1] + pre[dq.front()]*(pre[i]-pre[dq.front()]);
            par[i][k] = dq.front();
            //cout << i << " " << k << " " << dp[i][k] << " " << par[i][k] << endl;
            while(dq.size() >= 2){
                if(f(dq[dq.size()-2], dq.back(), k-1) > f(dq.back(), i, k-1)){
                    dq.pop_back();
                }
                else{
                    break;
                }
            }
            dq.push_back(i);
        }
        dq.clear();
    }
    cout << dp[N][K] << "\n";
    vector<int> v;
    int crnt = N;
    for(int k = K; k>=1; k--){
        v.push_back(par[crnt][k]);
        crnt = par[crnt][k];
    }
    sort(v.begin(), v.end());
    for(int n : v){
        cout << n << " ";
    }
    cout << "\n";
}
