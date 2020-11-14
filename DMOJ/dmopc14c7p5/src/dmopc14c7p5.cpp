#include <bits/stdc++.h>

using namespace std;

int N, M;
long long A, B, C;
long long pre[100005];

int main(){
    cin >> N >> M;
    cin >> A >> B >> C;
    for(int i = 1; i<=N; i++){
        cin >> pre[i];
        pre[i]--;
    }
    sort(pre+1, pre+1+N);
    for(int i = 1; i<=N; i++){
        pre[i] += pre[i-1];
    }
    long long ans = LLONG_MAX;
    for(int i = 0; i<=N; i++){
        ans = min(ans, A*(pre[N]-pre[N-i]) + B*(pre[N-i]) + C*(i)*(i-1)/2);
    }
    cout << ans << endl;
}
