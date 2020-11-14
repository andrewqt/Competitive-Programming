#include <bits/stdc++.h>

using namespace std;

pair<int, int> arr[200005];

int find_subset(int lb, int ub, int* w, int N, int* ans){
    for(int i = 0; i<N; i++){
        arr[i+1] = {w[i], i};
    }
    int cnt = 0;
    sort(arr+1, arr+1+N);
    long long sum = 0;
    for(int l = 1, r = 1; r<=N; r++){
        sum += arr[r].first;
        while(sum > ub){
            sum -= arr[l++].first;
        }
        if(sum >= lb && sum <= ub){
            cnt = r-l+1;
            for(int i = l; i<=r; i++){
                ans[i-l] = arr[i].second;
            }
            break;
        }
    }
    return cnt;
}

int main(){

}
