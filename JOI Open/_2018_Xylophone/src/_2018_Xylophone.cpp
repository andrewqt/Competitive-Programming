#include <bits/stdc++.h>
#include <xylophone.h>

using namespace std;

int arr[5005];
int dif[5005];

void solve(int N){
    for(int i= 2; i<=N; i++){
        dif[i] = query(i-1, i);
    }
    for(int i = 3; i<=N; i++){
        int k = query(i-2, i);
        if(dif[i-1] < 0){
            dif[i] *= -1;
        }
        if(abs(dif[i-1]+dif[i]) != k){
            dif[i] *= -1;
        }
    }
    partial_sum(dif+1, dif+1+N, arr+1);
    int mxidx = max_element(arr+1, arr+1+N)-arr;
    int mnidx = min_element(arr+1, arr+1+N)-arr;
    if(mxidx < mnidx){
        for(int i = 2; i<=N; i++){
            dif[i] *= -1;
        }
        partial_sum(dif+1, dif+1+N, arr+1);
    }
    int mn = *min_element(arr+1, arr+1+N);
    for(int i = 1; i<=N; i++){
        answer(i, arr[i]-mn+1);
    }
}
