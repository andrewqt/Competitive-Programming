#include <bits/stdc++.h>

using namespace std;

long long delivery(int N, int K, int L, int arr[]){
    long long ans = LLONG_MAX;
    for(int k = 0; k<K; k++){
        long long cnt = 0;
        bool b = 0;
        for(int i = k; i-K+1 < N; i+=K){
            if(arr[(i < N ? i : N-1)]*2 >= L){
                b = 1;
            }
            if(arr[(i-K+1 > 0 ? i-K+1 : 0)]*2 <= L && arr[(i < N ? i : N-1)]*2 >= L){
                cnt += L;
            }
            else if(b){
                cnt += (L-arr[(i-K+1 > 0 ? i-K+1 : 0)])*2;
            }
            else{
                cnt += arr[(i < N ? i : N-1)]*2;
            }
        }
        ans = (cnt < ans ? cnt : ans);
    }
    return ans;
}

/*
int main(){
    int arr[3] = {1, 2, 5};
    cout << delivery(3, 2, 8, arr) << endl;
}
*/
