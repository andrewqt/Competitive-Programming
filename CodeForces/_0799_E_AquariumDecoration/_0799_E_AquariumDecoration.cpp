#include <bits/stdc++.h>

using namespace std;

int N, M, K, A;
int arr[200005];
int msk[200005];
priority_queue<int> pq01, pq10, pq11;

int main(){

    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    if(M < K){
        cout << -1 << endl;
        return 0;
    }
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    for(int k = 1; k<=2; k++){
        cin >> A;
        if(A < K){
            cout << -1 << endl;
            return 0;
        }
        for(int a = 1; a<=A; a++){
            int n;
            cin >> n;
            msk[n] |= k;
        }
    }
    long long ans = LLONG_MAX;
    long long crnt = 0;
    int L = M;
    for(int i =1 ; i<=N; i++){
        if(msk[i] == 3){
            pq11.push(arr[i]);
            crnt += arr[i];
            L--;
        }
        if(msk[i] == 2){
            pq10.push(-arr[i]);
        }
        if(msk[i] == 1){
            pq01.push(-arr[i]);
        }
        if(msk[i] == 0){
            pq00.push(arr[i]);
            crnt += arr[i];
        }
    }
    while(pq11.size() < K && pq10.size() && pq01.size()){
        pq11.push(pq10.top()+pq01.top());
        crnt += pq10.top() + pq01.top();
        pq10.pop(), pq01.pop();
        L-=2;
    }
    while(pq11.size() > K){
        pq00.push(pq11.top());
        pq11.pop();
        L++;
    }

}
