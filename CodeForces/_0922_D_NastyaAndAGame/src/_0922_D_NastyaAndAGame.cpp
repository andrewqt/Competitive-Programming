#include <bits/stdc++.h>

using namespace std;

int N;
long long K;
long long pre[200005];
long long arr[200005];
vector<int> v;

int main(){
    cin >> N >> K;
    long long ans = 0;
    v.push_back(0);
    for(int i = 1; i<=N; i++){
        cin >> pre[i];
        long long n = pre[i];
        pre[i] += pre[i-1];
        if(n-1){
            v.push_back(i);
        }
        arr[i] = n;
        double loggy = 0;
        long long prod = 1;
        int lst = i;
        if(K==1 && arr[n] == 1){
            ans++;
        }
        for(int j = v.size()-1; j>=0; j--){
            if(prod%K ==0 && prod <= K*pre[i]-K*pre[v[j]] && prod > K*pre[i]-K*pre[lst-1]){
                ans++;
            }
            lst = v[j];
            prod *= arr[v[j]];
            loggy += log2(arr[v[j]]);
            if(loggy > 62){
                break;
            }
            if(!j){
                break;
            }
            if(prod == K*pre[i]-K*pre[v[j]-1]){
                ans++;
            }
        }
    }
    cout << ans << endl;
}
