
#include <bits/stdc++.h>

using namespace std;

int besthub(int N, int L, int arr[], long long K) {
    int l = 1, r = 100000;
    long long pre[N+1];
    pre[0] = 0;
    for(int i = 1; i<=N; i++){
        pre[i] = pre[i-1] + arr[i-1];
    }
    int ans = 0;
    while(l <= r){
        int mid = (l+r)/2;
        bool b = 0;
        for(int i = mid; i<=N; i++){
            int midmid = i-mid/2-1;
//            cout << pre[i] << " " << arr[midmid] << " " << pre[i-mid] << " " << mid << " " << midmid << endl;
//            cout << pre[i] - pre[midmid+1] - 1L*arr[midmid]*(mid/2)
//               + 1L*arr[midmid]*(mid-mid/2) - pre[midmid+1] + pre[i-mid] << endl;
            if(pre[i] - pre[midmid+1] - 1L*arr[midmid]*(mid/2)
               + 1L*arr[midmid]*(mid-mid/2) - pre[midmid+1] + pre[i-mid] <= K){
               b = true;
               break;
            }
        }
        if(b){
            ans = mid;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

int main(){
    int arr[] = {1,2,10,12,14};
    cout << besthub(5, 20, arr, 6) << endl;
}
