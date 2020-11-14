#include <bits/stdc++.h>

using namespace std;

int N;
long long T;
long long arr[1000000];

int main(){
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
    scanf("%d %lld", &N, &T);
    int idx = 0;
    arr[0] = -2000000000000000000;
    for(int i = 1; i<=N; i++){
        long long l, r;
        scanf("%lld %lld", &l, &r);
        r = -(T*r+l);
        if(upper_bound(arr, arr+idx+1, r) != arr+idx+1){
            *upper_bound(arr, arr+idx+1, r) = r;
        }
        else{
            idx++;
            arr[idx] = r;
        }
    }
    cout << idx << endl;
}
