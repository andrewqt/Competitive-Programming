#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int arr[100000];

int main(){
    cin >> N >> M >> K;
    for(int i =0;i<N; i++){
        cin >> arr[i];
    }
    sort(arr, arr+N);
    int ans = 0;
    for(int i = K; i<N; i+=K){
        ans = max(ans, arr[i+1] - arr[i]);
    }
    cout << ans << endl;
}
