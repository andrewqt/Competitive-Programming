#include <bits/stdc++.h>

using namespace std;

const int maxN = 1000005;
int arr[maxN], fre[maxN];
int N, K, cnt;
long long ans;
int main(){
    cin >> N >> K;
    for(int i =1; i<=N; i++){
        cin >> arr[i];
    }
    for(int l = 0, r = 1; r<=N; r++){
        fre[arr[r]]++;
        if(fre[arr[r]] == 1){
            cnt++;
        }
        while(cnt >= K){
            l++;
            fre[arr[l]]--;
            if(fre[arr[l]] == 0){
                cnt--;
            }
        }
        ans += l;
    }
    cout << ans << endl;
}
