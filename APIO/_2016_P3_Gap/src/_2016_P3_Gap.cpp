#include <bits/stdc++.h>
#include "gap.h"

using namespace std;

long long arr[100005];

long long findGap(int T, int N){
    if(T == 1){
        int l = 1, r = N;
        long long lstl = -1, lstr = 1000000000000000001LL;
        while(l <= r){
            MinMax(lstl+1, lstr-1, &lstl, &lstr);
            arr[l++] = lstl, arr[r--] = lstr;
        }
        long long ans = 0;
        for(int i = 2; i<=N; i++){
            ans = max(ans, arr[i]-arr[i-1]);
        }
        return ans;
    }
    fill(arr+1, arr+1+N, -1);
    long long s, e;
    MinMax(0, 1000000000000000000LL, &s, &e);
    long long d = (e-s-2+N)/(N-1);
    arr[1] = s, arr[N] = e;
    long long lst = s;
    long long n = s;
    long long ans = 0;
    while(n < e){
        long long t;
        MinMax(n+1, min(e-1, n+d), &s, &t);
        ans = max(ans, s-lst);
        if(t+1){
            lst = t;
        }
        n += d;
    }
    ans = max(ans, e-lst);
    return ans;
}
