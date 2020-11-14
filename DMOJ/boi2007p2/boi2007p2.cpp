#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[1005];
int dp[1005][1005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr+1, arr+1+N);
    memset(dp, INT_MAX, sizeof(dp));

}
