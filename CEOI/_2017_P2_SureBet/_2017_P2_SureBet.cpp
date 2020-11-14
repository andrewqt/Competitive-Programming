#include <bits/stdc++.h>

using namespace std;

int N;
long long arr[100005], brr[100005];

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        double x, y;
        cin >> x >> y;
        x += 0.00005, y+=0.00005;
        arr[i] = x*10000, brr[i] = y*10000;
        //cout << arr[i] << " " << brr[i] << endl;
    }
    sort(arr+1, arr+1+N, greater<long long>());
    sort(brr+1, brr+1+N, greater<long long>());
    int idx1 = 1, idx2 = 1;
    long long ans = 0;
    long long tot1 = 0, tot2 = 0;
    for(long long k = 1; k<=2*N; k++){
        if(min(tot1+arr[idx1],tot2) >= min(tot1, tot2+brr[idx2]) && idx1 <= N){
            tot1 += arr[idx1];
            idx1++;
        }
        else{
            tot2 += brr[idx2];
            idx2++;
        }
        ans = max(ans, min(tot1, tot2)-k*10000);
        assert(idx1 <= N+1 && idx2 <= N+1);
        //cout << tot1-k << " " << tot2-k << endl;
    }
    string s = to_string(ans%10000);
    while(s.size() < 4){
        s = "0" + s;
    }
    cout << ans/10000 << "." << s << endl;
}
