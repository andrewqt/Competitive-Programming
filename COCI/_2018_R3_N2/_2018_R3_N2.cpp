#include <bits/stdc++.h>

using namespace std;

int arr[200000];
int N;

int main(){
    cin >> N;
    int ans = 2000000005;
    for(int i =1 ; i<=N; i++){
        cin >> arr[i];
    }
    for(int i = 2; i<=N; i++){
        ans = min(ans, abs(arr[i]-arr[i-1]));
    }
    cout << ans << endl;
}
