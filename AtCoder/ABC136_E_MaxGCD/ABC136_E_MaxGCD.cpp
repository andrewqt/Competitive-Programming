#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[505], brr[505];

long long solve(long long k){
    for(int i = 1; i<=N; i++){
        brr[i] = arr[i]%k;
    }
    sort(brr+1, brr+1+N);
    int tot = 0;
    for(int l = 1, r = N; l<=r;){
        int opt1 = brr[l], opt2 = k-brr[r];
        if(opt1 == opt2){
            tot += opt1;
            l++, r--;
        }
        else if(opt1 < opt2){
            tot += opt1;
            brr[r] += brr[l];
            l++;
        }
        else{
            tot += opt2;
            brr[l] -= k-brr[r];
            r--;
        }
    }
    return tot;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    long long s = 0;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        s += arr[i];
    }
    long long ans = 1;
    for(long long k = 1; k<=sqrt(s); k++){
        if(s%k == 0){
            if(solve(k) <= K){
                ans = max(ans, k);
            }
            if(solve(s/k) <= K){
                ans = max(ans, s/k);
            }
        }
    }
    cout << ans << endl;
}
