#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[200005];
map<int, int> mp;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        arr[i] += K-1;
        arr[i] %= K;
        arr[i] += arr[i-1];
        arr[i] %= K;
    }
    long long ans = 0;
    for(int r = 0, l = r-K+1; r<=N; r++, l++){
        ans += mp[arr[r]];
        mp[arr[r]]++;
        if(l >= 0){
            mp[arr[l]]--;
        }
        //cout << ans << " " << r << endl;
    }
    cout << ans << endl;
}
